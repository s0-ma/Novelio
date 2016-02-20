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

void SqliteDAO::writeMemento(int key, Memento *memento){
    string create_sql = "";
    create_sql += "REPLACE INTO SAVE_DATA (SAVE_NO, SCRIPT_FILE, PARAGRAPH, LINE) ";
    create_sql += "VALUES ("+ to_string(key) + ",\"" + memento->getFilename() + "\"," + to_string(memento->getParagraph()) + "," + to_string(memento->getLine()) + ");";
    
    auto status = sqlite3_exec(db, create_sql.c_str(), NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) CCLOG("insert/replace failed : %s", errorMessage);
    
    delete memento;
}

Memento* SqliteDAO::createMemento(int key){
    Memento* ret = new Memento();
    
    string query = "";
    query += "SELECT * FROM SAVE_DATA WHERE SAVE_NO = " + to_string(key) + ";";
    
    // データの抽出
    // ステートメントの用意
    sqlite3_stmt *pStmt = NULL;
    auto err = sqlite3_prepare_v2(db, query.c_str(), -1, &pStmt, NULL);
    
    if(err != SQLITE_OK){
        /* TODO:エラー処理 */
    }else{
        // データの抽出
        while(SQLITE_ROW == (err = sqlite3_step(pStmt)) ){
            int id = sqlite3_column_int(pStmt, 0);
            ret->setFilename(to_string(sqlite3_column_int(pStmt, 1)));
            ret->setParagraph(sqlite3_column_int(pStmt, 2));
            ret->setLine(sqlite3_column_int(pStmt, 3));
            
            CCLOG("save_id %d opend.\n", id);
        }
        
        if(err != SQLITE_DONE){
            /* TODO: エラー処理 */
        }
    }
    
    // ステートメントの解放
    sqlite3_finalize(pStmt);
    
    return ret;
    
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