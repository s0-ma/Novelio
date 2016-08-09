﻿//
//  DataAccessObject.h
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//

#ifndef __Novelio__DataAccessObject__
#define __Novelio__DataAccessObject__

#include "../Macros.h"
#include "../extensions/sqlite3.h"
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
    
    struct LoadInformation{
        int saveNo;
        string datetime;
        string screenShot;
        string comment;
    };
    
    //唯一のアクセス手段
    static SqliteDAO* getInstance();
    
    ~SqliteDAO();
    
    //個別セーブデータ
    void writeMemento(int key, Memento* memento);
    void writeLoadIndex(int key, string thumbnailPath, string comment);
    Memento* createMemento(int i);
    
    //グローバルデータ
    void writeGlobalData(int bgm_vol, int se_vol, int text_speed, int recent_save);
    map<string, int> getGlobalData();
    
    //ロード画面用データ
    vector<LoadInformation> getLoadInformation();
    
    void writeAlbumImage(string);
    vector<string> getAlbumImages();
    
    //テキストログ
    void writeLog(int saveNo, std::vector<string> logs);
    vector<string> getLog(int saveNo);
    
    //開発用
    void changeSaveFile(string file);
    
private:
    sqlite3* db = NULL;
    char* errorMessage = NULL;
    
    void init(string file);
    void initializeTables();

};

NS_NV_END

#endif /* defined(__Novelio__DataAccessObject__) */
