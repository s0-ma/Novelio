//
//  DataAccessObject.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//

#include "DataAccessObject.h"

NS_NV_BEGIN

SqliteDAO* SqliteDAO::instance = 0;

SqliteDAO* SqliteDAO::getInstance() {
    if(instance == 0){
        instance = new SqliteDAO();
    }
    return instance;
};

SqliteDAO::SqliteDAO(){
    this->init();
}
SqliteDAO::~SqliteDAO(){
    //Close
    sqlite3_close(db);
    
}

void SqliteDAO::initializeTables(){
        //テーブル作成
        string create_sql = "";
        create_sql += "CREATE TABLE MANAGEMENT ( BGM_VOLUME int(3), SE_VOLUME int(3), TEXT_SPEED int(3), RECENT_SAVE int(3) );";
        create_sql += "CREATE TABLE DISPLAY( SAVE_NO int primary key, SAVE_DATETIME text, SCREEN_SHOT text, SAVE_COMMENT text);";
        create_sql += "CREATE TABLE SAVE_DATA( SAVE_NO int primary key, SCRIPT_FILE text, PARAGRAPH int, LINE int);";
        create_sql += "CREATE TABLE TEXT_LAYER( SAVE_NO int primary key );";
        create_sql += "CREATE TABLE BG_LAYER( SAVE_NO int primary key );";
        create_sql += "CREATE TABLE PORTRAIT_LAYER( SAVE_NO int primary key );";
        create_sql += "CREATE TABLE PORTRAITS( SAVE_NO int primary key );";
    
        auto status = sqlite3_exec(db, create_sql.c_str(), NULL, NULL, &errorMessage );
        if( status != SQLITE_OK ) CCLOG("create table failed : %s", errorMessage);
}

void SqliteDAO::writeMemento(Memento *memento){
    string create_sql = "";
    create_sql += "INSERT INTO SAVE_DATA (SCRIPT_FILE, PARAGRAPH, LINE) ";
    create_sql += "VALUES (\""+ memento->getFilename() + "\"," + to_string(memento->getParagraph()) + "," + to_string(memento->getLine()) + ");";
    
    auto status = sqlite3_exec(db, create_sql.c_str(), NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) CCLOG("insert failed : %s", errorMessage);
    
    delete memento;
}

void SqliteDAO::init(){
    bool isFirstRun = true;
    
    //DBファイルの保存先のパス
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append(".tenclaps/novelio.db");
    
    //初回起動かどうかの確認
    if(FileUtils::getInstance()->isFileExist(filePath)){
        isFirstRun = false;
    }
    
    //OPEN
    auto status = sqlite3_open(filePath.c_str(), &db);
    if (status != SQLITE_OK){
        CCLOG("opne failed : %s", errorMessage);
    }else{
        CCLOG("open succeeded");
    }

    //初回なら初期化
    if(isFirstRun){
        initializeTables();
    }else{
    }
    
}

NS_NV_END