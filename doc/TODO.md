## SilentDream TODO


###  V0.1
###### Start time：2018-03-04

* 搭建出最核心的结构：main --> 参数解析 --> client模式或者daemon模式，daemon模式再分化出两个进程，一个是主进程，一个是工作进程；
* 实现信号处理模块，收到致命信号时要能打印出堆栈；
* log模块后续要做成先存到内存里，要开辟一块共享内存供多个进程使用，由一个单独的回写线程保存log文件；
* 实现Epoll模块；
* 实现Socket模块；
* 实现参数解析模块，client模式下能根据参数发送对应命令给主进程，能接收并解析主进程返回的结果;
* 主进程能响应client命令，与worker进程通过unix udp socket通信，能控制worker进程工作；
* 实现一个Looper-Handler框架，开发一个hello模块和hello应用，client进程能控制hello应用正常工作；
* 完善编译系统，做到可以控制模块编译，把框架编译成sdk包供算法开发使用；



