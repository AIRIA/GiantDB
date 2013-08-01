#include "GiantDB.h"

GiantDB *GiantDB::s_pInstance = NULL;

GiantDB *GiantDB::instance() {
    if(s_pInstance==NULL) {
        s_pInstance = new GiantDB();
    }
    return s_pInstance;
}

void GiantDB::GiantLog(const char *info) {
    if(debug==false) {
        return;
    }
#ifdef CONSOLE
    cout << "[GiantDB] " << info << endl;
#endif
#ifdef CC
    string log = "[GiantDB] ";
    CCLog(log+info);
#endif
}

void GiantDB::exec_log(int result,const char *successMsg) {
    if(result==SQLITE_OK) {
        GiantLog(successMsg);
    } else {
        GiantLog(errMsg);
    }
}
/* 打开数据库 */
void GiantDB::openDB(const char *dbname) {
    exec_log(sqlite3_open(dbname,&sqlDB),"open database success");
}
/* 执行DDL语句 以及更新和删除操作 */
void GiantDB::exec(const char *sql) {
    string str = "excute command success:";
    str = str+sql;
    exec_log(sqlite3_exec(sqlDB,sql,NULL,NULL,&errMsg),str.c_str());
}

vector< map<string,string> > GiantDB::query(const char *sql) {
	res.clear();
    exec_log(sqlite3_exec(sqlDB,sql,GiantDB::exec_callback,NULL,&errMsg),"data query success");
    return res;
}

int GiantDB::exec_callback(void *param,int n_column,char **columnValues,char **columnNames) {
	map<string,string> record;
	for(int i=0; i<n_column; i++) {
		record.insert(make_pair(columnNames[i],columnValues[i]));
    }
	s_pInstance->res.push_back(record);
    return SQLITE_OK;
}