json_config_edit  
=======  
针对json配置文件的编辑、注释和上传下载工具  
![image](https://github.com/yangzigy/json_config_edit/raw/master/pictures/gui0.jpg)  
## 功能  
1. 显示json配置文件，及每个配置的描述  
2. 修改json配置文件  
3. 可保存文件，或通过HTTP的方式上传配置文件  
## 实现方式  
软件使用QT编写，启动时读取软件自身的配置文件cfggui.txt,次配置文件中描述了待处理的json配置文件的内容，包括具体有多少个配置条目，每个配置条目的描述。支持配置条目为列表、对象等具体数据结构。  
json读取部分在dictdis.h中，递归读取json的各个配置条目。  
