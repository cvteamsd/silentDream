#include <execinfo.h>

#include <SilentDream/Global.h>
#include <SilentDream/Log.h>
#include "SignalHandler.h"
#include <sstream>


SignalHandler* SignalHandler::self = nullptr;
pthread_once_t once_control;

SignalHandler& SignalHandler::instace()
{
    if (self == nullptr) {
        pthread_once(&once_control, [] {
            self = new SignalHandler();
        });
    }

    return *self;
}


SignalHandler::SignalHandler()
{
    sigemptyset(&mSignalMask);
    sigaddset(&mSignalMask, SIGABRT);
}

SignalHandler::~SignalHandler()
{

}

void SignalHandler::setMonitorSignals(sigset_t signals)
{
    sigorset(&mSignalMask, &mSignalMask, &signals);
}

int SignalHandler::install()
{
    int ret;

    ret = initSignalMonitor();
    assert(ret == 0);

    setHardwareSigHandler();

    return 0;
}
////////////////////////////////////////
int SignalHandler::initSignalMonitor()
{
    int err;
    if ((err = pthread_sigmask(SIG_BLOCK, &mSignalMask, &mOldSignalMask)) != 0) {
        LOGE("pthread_sigmask failed:%s", strerror(err));
        return -1;
    }

    err = pthread_create(&mSignalTid, nullptr, customSignalThreadFn, this);
    if (err != 0) {
        LOGE("create signal thread failed:%s", strerror(err));
        return -1;
    }

    return err;
}

void* SignalHandler::customSignalThreadFn(void *arg)
{
   SignalHandler* s = static_cast<SignalHandler*>(arg);

   pthread_detach(pthread_self());

   int sig;
   if (sig = sigsetjmp(s->mSigJmpBuf, 1)) {
       LOGE("CRASH signal:%s", strsignal(sig));
       s->dumpstack();
       exit(sig);
   }

   int err, signo;
   for (;;) {
       err = sigwait(&s->mSignalMask, &signo);
       if (err != 0) {
           LOGE("sigwait failed:%s", strerror(err));
           break;
       }
   }

   return (void*)0;
}

////////////////////////////////////////
int SignalHandler::setHardwareSigHandler()
{
    int signals[] = {SIGSEGV, SIGILL, SIGFPE, SIGBUS};

    for (int i = 0; i < ARRAY_SIZE(signals); ++i) {
        struct sigaction act;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        act.sa_handler = hardwareSigHander;
        if (sigaction(signals[i], &act, NULL) < 0) {
            LOGE("set %s handler failed:%s", strsignal(signals[i]), strerror(errno));
            return -1;
        }
    }

    return 0;
}

void SignalHandler::hardwareSigHander(int signo)
{
//    siglongjmp(instace().mSigJmpBuf, signo);
    instace().dumpstack();
    _exit(signo);
}

void SignalHandler::dumpstack()
{
#if 0
    char* stack[20] = {0};
    int depth = backtrace(reinterpret_cast<void**>(stack), sizeof(stack)/sizeof(stack[0]));
    if (depth){
        char** symbols = backtrace_symbols(reinterpret_cast<void**>(stack), depth);
        if (symbols){
            for(int i = 0; i < depth; i++){
                LOGE("===[%d]:%s", (i+1), symbols[i]);
            }
        }
        free(symbols);
    }
#elif 1
    unw_cursor_t cursor; unw_context_t uc;
    unw_word_t ip, sp;

    std::stringstream ss;

    ss << "\n";

    char sym[256];
    unw_word_t offset;

    unw_getcontext(&uc);
    unw_init_local(&cursor, &uc);
    while (unw_step(&cursor) > 0) {
        unw_get_reg(&cursor, UNW_REG_IP, &ip);
        unw_get_reg(&cursor, UNW_REG_SP, &sp);

        ss << "    0x" << std::hex << ip;
        if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
            char* nameptr = sym;
            int status;
            char* demangled = abi::__cxa_demangle(sym, nullptr, nullptr, &status);
            if (status == 0) {
              nameptr = demangled;
            }
            ss << " (" << nameptr << "+0x" << offset <<")\n";

            free(demangled);
        }
    }
    LOGE("%s", ss.str().c_str());

#endif
}




