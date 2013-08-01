#ifndef _GIANTDB_H_
#define _GIANTDB_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "sqlite3.h"


#define CONSOLE
#define GDB Giant
using namespace std;

class GiantDB {
public:
    sqlite3 *sqlDB;
    int result;
    char *errMsg;
    string sql;
    bool debug;
	vector< map<string,string> > res;
public:
    vector< map<string,string> > query(const char *sql);
    void exec(const char *sql);
    void openDB(const char *dbname);
    static GiantDB *instance();
    ~GiantDB() {
        delete s_pInstance;
    }
private:
	int currentIdx;
    void GiantLog(const char *info);
    static int exec_callback(void *param,int n_column,char **columnValues, char **columnNames);
    GiantDB():debug(false),sqlDB(NULL),errMsg(NULL),currentIdx(0) {
        //禁止实例化
    };
    /* 执行完毕后打印注释 在调试模式下使用 */
    void exec_log(int res,const char *successMsg);
    static GiantDB *s_pInstance;
};


#endif