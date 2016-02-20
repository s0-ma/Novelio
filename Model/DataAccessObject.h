//
//  DataAccessObject.h
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//

#ifndef __Novelio__DataAccessObject__
#define __Novelio__DataAccessObject__

#include "../Macros.h"
#include "sqlite3.h"
#include "Memento.h"

NS_NV_BEGIN

class SqliteDAO{
    //唯一のinstance
    static SqliteDAO* instance;
    // 生成やコピーを禁止する
    SqliteDAO();
    SqliteDAO(const SqliteDAO& rhs);
    SqliteDAO& operator=(const SqliteDAO& rhs);
public:
    //唯一のアクセス手段
    static SqliteDAO* getInstance();
    
    ~SqliteDAO();
    
    void writeMemento(Memento* memento);
    void createRecord(int i, Memento* memento);
    void updateRecord(int i, Memento* memento);
    
private:
    sqlite3* db = NULL;
    char* errorMessage = NULL;
    
    void init();
    void initializeTables();

};

NS_NV_END

#endif /* defined(__Novelio__DataAccessObject__) */
