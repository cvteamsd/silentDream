## SilentDream help

#### 1. Download source code  

##### 1.1 Get repository list:
```
ssh -p 8022 git@silentdream.dynu.net
&nbsp;
if you failed with "Permission denied (publickey).", please check your key.
otherwise, it will show your username and project list.

```

##### 1.2 Framework repository address 
```
git clone ssh://git@silentdream.dynu.net:8022/silentDream.git
```


#### 2. Customize your git 

```
git config  user.name $(username)
git config  user.email $(email_address) 
git config  commit.template $(project_root_dir)/doc/git.template   
git config  core.editor vim
```

Variable name | Explanation
--- | ------
username   | your username  
email_address | your email address  
project_root_dir | your project location  


#### 3. build & clean


##### 3.1 dependencies

* libunwind:  for C++ callback debug info.
```
sudo apt-get install libunwind8-dev
```

##### 3.2 build silentdream
```
cd $(project_root_dir);
make
```

##### 3.3 clean
```
make clean
```

#### 4. install
##### 4.1 install
```
make install

install path: $(HOME)/.silentdream
```

##### 4.2 uninstall
```
make uninstall
```

#### 5. run 
##### 5.1 run
```
silentDream [args]
```


##### 5.2 view running silentdream daemon
```
make ps
```

##### 5.3 kill silentdream daemon
```
make kill
```

#### 6. How to add a plugin
1. create a plugin directory in `apps`, `modules` or some other place.

2. cp Makefile from `src` directory to your plugin directory, modify it.

Variable | Explanation
--------|-------------
MODULE  | your plugin name, default value is current directory name.
SRC_DIR | add your sub directories, your plugin root directory does **NOT** need add.
DEFINE  | macro defines.
INCLUDE | include path, **src/include/** has added already. 
LDFLAGS | link flags. 
LIBS    | link libraries. 
build-target  | executable, plugin, shared_library or static_library.


For example: 
```Makefile
include $(BASE_DIR)/Header.mk

MODULE  := 
SRC_DIR := 
DEFINE  :=
INCLUDE := 
LDFLAGS := 
LIBS    := 

$(call build-target, plugin)

include $(BASE_DIR)/Footer.mk
```

3. run `source setenv.sh` setup environment variables. 
```
cd $(project_root_dir);
source setenv.sh;
```

4. now you can cd to your plugin directory and do something.
* build plugin
    ```
    make
    ```
* clean plugin
    ```
    make clean
    ```
* install plugin (should install silentdream first)
    ```
    make install_plugin
    ```




