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


#### 3. build & run


##### 3.1 build
```
cd $(project_root_dir);
make
```

##### 3.2 run
```
sudo ./build/silentDream [args]
```

##### 3.3 dependencies
```
# for C++ callback debug info
sudo apt-get install libunwind8-dev
```
