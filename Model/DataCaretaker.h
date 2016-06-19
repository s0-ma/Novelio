//
//  DataCaretaker.h
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//

#ifndef __Novelio__DataCaretaker__
#define __Novelio__DataCaretaker__

#include "../Macros.h"

#include "Memento.h"
#include "DataAccessObject.h"

NS_NV_BEGIN

class CareTaker{
    //唯一のinstance
    static CareTaker* instance;
    // 生成やコピーを禁止する
    CareTaker();
    CareTaker(const CareTaker& rhs);
    CareTaker& operator=(const CareTaker& rhs);
public:
    //唯一のアクセス手段
    static CareTaker* getInstance();
    ~CareTaker();
    
    vector<SqliteDAO::LoadInformation> getLoadInformation();
    map<string, int> getGlobalData();
    
    void saveGlobalData();
    void loadGlobalData();
    
    void storeMemento(int key);
    bool loadMemento(int key);
};

NS_NV_END

#endif /* defined(__Novelio__DataCaretaker__) */
