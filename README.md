GiantDB
========
-----

GiantDB是一个单例类 通过instance方法初始化  
>`GiantDB *gdb = GiantDB::instance();`

这样就获取到了一个GiantDB的实例化对象

>`gdb->open("config.db");`

可以打开数据库 如果想查看是否打开成功 可以打开debug来在控制台打印操作日志
>`gdb->debug = true;`

这样在执行每条sql语句的时候 都会有相应的日志输出到控制台

>`gdb->exec(create table test(id integer primary key,content text));`


查询语句会返回一个vector类型的对象 
>`vector<map<string,string> > res;`

具体方法可以查看一下代码:




	#include <iostream>
	#include "GiantDB.h"
	int main() {
	GiantDB *gdb = GiantDB::instance();
	gdb->debug = true;
	gdb->openDB("config.db");
	gdb->exec("create table test(id integer primary key,content text)");
	gdb->exec("insert into test(content) values('中文')");
	vector<map<string,string> > res = gdb->query("select * from test");
	vector<map<string,string> >::iterator records = res.begin();
	while(records!=res.end()){
		map<string,string>::iterator record = records->begin();
		while(record!=records->end()){
			cout << record->first <<":" << record->second << "   ";
			record++;
		}
		cout << endl;
		records++;
	}
    return 0;
	}

----
