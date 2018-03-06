## SilentDream help

1. Repository address  
```
&nbsp;&nbsp;  git clone ssh://git@silentdream.dynu.net:8022/silentDream.git
```

2. Git custom settings  

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


3. build & run


##### build:
```
cd $(project_root_dir);
make
```

##### run:
```
sudo ./build/silentDream [args]
```


