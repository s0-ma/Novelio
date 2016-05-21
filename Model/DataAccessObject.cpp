//
//  DataAccessObject.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//

#include "DataAccessObject.h"

#include "time.h"

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
    //全体データ
    create_sql += "CREATE TABLE MANAGEMENT ( BGM_VOLUME int(3), SE_VOLUME int(3), TEXT_SPEED int(3), RECENT_SAVE int(3) );";
    //セーブ/ロード画面用
    create_sql += "CREATE TABLE DISPLAY( SAVE_NO int primary key, SAVE_DATETIME text, SCREEN_SHOT text, SAVE_COMMENT text);";
    //個別セーブデータ
    create_sql += "CREATE TABLE SAVE_DATA( SAVE_NO int primary key, SCRIPT_FILE text, PARAGRAPH int, LINE int);";
    create_sql += "CREATE TABLE TEXT_LAYER( SAVE_NO int primary key, NAME text, TEXT text );";
    create_sql += "CREATE TABLE BG_LAYER( SAVE_NO int primary key, BG_PATH text );";
//    create_sql += "CREATE TABLE PORTRAIT_LAYER( SAVE_NO int primary key );";
    create_sql += "CREATE TABLE PORTRAITS( SAVE_NO int, ID text, BASE_PATH text, FACE_ID text, FACE_PATH text, X int, Y int, EMO_ID text, EMO_X int, EMO_Y int);";
    
    auto status = sqlite3_exec(db, create_sql.c_str(), NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ){
        CCLOG("create table failed : %s", errorMessage);
    }
}

void SqliteDAO::writeMemento(int key, Memento *memento){
    string create_sql = "";
    create_sql += "REPLACE INTO SAVE_DATA (SAVE_NO, SCRIPT_FILE, PARAGRAPH, LINE) ";
    create_sql += "VALUES ("+ to_string(key) + ",\"" + memento->getFilename() + "\"," + to_string(memento->getParagraph()) + "," + to_string(memento->getLine()) + ");";

    create_sql += "REPLACE INTO BG_LAYER (SAVE_NO, BG_PATH) ";
    create_sql += "VALUES ("+ to_string(key) + ",\"" + memento->getBackground() + "\");";

    create_sql += "DELETE FROM PORTRAITS WHERE SAVE_NO = " + to_string(key) + ";";
    auto portraits = memento->getPortraits();
    for(int i = 0; i< portraits.size(); i++){
        create_sql += "INSERT INTO PORTRAITS( SAVE_NO, ID, BASE_PATH, FACE_ID, FACE_PATH, X, Y, EMO_ID, EMO_X, EMO_Y) ";
        create_sql += "VALUES ("+ to_string(key) + ","
                                + "\"" + portraits[i].id + "\","
                                + "\"" + portraits[i].basePath + "\","
                                + "\"" + portraits[i].face_id + "\","
                                + "\"" + portraits[i].facePath + "\","
                                + to_string(portraits[i].x) + ","
                                + to_string(portraits[i].y) + ","
                                + "\"" + portraits[i].emoPath + "\","
                                + to_string(portraits[i].emoX) + ","
                                + to_string(portraits[i].emoY) + ");";
    }
    
    auto status = sqlite3_exec(db, create_sql.c_str(), NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) CCLOG("insert/replace failed : %s", errorMessage);
    
    delete memento;
}

void SqliteDAO::writeLoadIndex(int key, string thumbnailPath, string comment){
    time_t timer;
    time(&timer);
    string datetime = ctime(&timer);
    datetime.erase( --datetime.end() );//末尾の改行を削除
    
    string create_sql = "";
    create_sql += "REPLACE INTO DISPLAY (SAVE_NO, SAVE_DATETIME, SCREEN_SHOT, SAVE_COMMENT) ";
    create_sql += "VALUES ("+ to_string(key) + ",\"" + datetime + "\",\"" + thumbnailPath + "\",\"" + comment + "\");";

    auto status = sqlite3_exec(db, create_sql.c_str(), NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) CCLOG("insert/replace failed : %s", errorMessage);
}


void SqliteDAO::writeGlobalData(int bgm_vol, int se_vol, int text_speed, int recent_save){
    string create_sql = "";
    create_sql += "REPLACE INTO SAVE_DATA (BGM_VOLUME, SE_VOLUME, TEXT_SPEED, RECENT_SAVE) ";
    create_sql += "VALUES ("+ to_string(bgm_vol) + "," + to_string(se_vol) + "," + to_string(text_speed) + "," + to_string(recent_save) + ");";
    
    auto status = sqlite3_exec(db, create_sql.c_str(), NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) CCLOG("insert/replace failed : %s", errorMessage);
};

map<string, int> SqliteDAO::getGlobalData(){
    map<string,int> ret;
    
    string query = "";
    query += "SELECT * FROM MANAGEMENT;";
    
    // データの抽出
    // ステートメントの用意
    sqlite3_stmt *pStmt = NULL;
    auto err = sqlite3_prepare_v2(db, query.c_str(), -1, &pStmt, NULL);
    
    if(err != SQLITE_OK){
        /* TODO:エラー処理 */
    }else{
        // データの抽出
        while(SQLITE_ROW == (err = sqlite3_step(pStmt)) ){
            ret["bgm_vol"] = sqlite3_column_int(pStmt, 0);
            ret["se_vol"] = sqlite3_column_int(pStmt, 1);
            ret["text_speed"] = sqlite3_column_int(pStmt, 2);
            ret["recet_save"] = sqlite3_column_int(pStmt, 3);
        }
        if(err != SQLITE_DONE){
            /* TODO: エラー処理 */
        }
    }
    
    // ステートメントの解放
    sqlite3_finalize(pStmt);
    
    return ret;
};

Memento* SqliteDAO::createMemento(int key){
    Memento* ret = new Memento();
    string query = "";
    // ステートメントの用意
    sqlite3_stmt *pStmt = NULL;
    int err;

    query = "SELECT * FROM SAVE_DATA WHERE SAVE_NO = " + to_string(key) + ";";
    err = sqlite3_prepare_v2(db, query.c_str(), -1, &pStmt, NULL);
    if(err != SQLITE_OK){
        /* TODO:エラー処理 */
    }else{
        // データの抽出
        while(SQLITE_ROW == (err = sqlite3_step(pStmt)) ){
            int id = sqlite3_column_int(pStmt, 0);
            ret->setFilename(to_string(sqlite3_column_int(pStmt, 1)));
            ret->setParagraph(sqlite3_column_int(pStmt, 2));
            ret->setLine(sqlite3_column_int(pStmt, 3));
            
            CCLOG("save_id %d opend.", id);
        }
        if(err != SQLITE_DONE){
            /* TODO: エラー処理 */
        }
    }

    query = "SELECT * FROM TEXT_LAYER WHERE SAVE_NO = " + to_string(key) + ";";
    err = sqlite3_prepare_v2(db, query.c_str(), -1, &pStmt, NULL);
    if(err != SQLITE_OK){
        /* TODO:エラー処理 */
    }else{
        // データの抽出
        while(SQLITE_ROW == (err = sqlite3_step(pStmt)) ){
            int id = sqlite3_column_int(pStmt, 0);
            auto name =sqlite3_column_text(pStmt, 1);
            auto text =sqlite3_column_text(pStmt, 2);
            ret->setName(string((char*)name));
            ret->setText(string((char*)text));
            CCLOG("save_id %d (text_layer): %s %s", id, string((char*)name).c_str(), string((char*)text).c_str());
        }
        if(err != SQLITE_DONE){
            /* TODO: エラー処理 */
        }
    }

    
    query = "SELECT * FROM BG_LAYER WHERE SAVE_NO = " + to_string(key) + ";";
    err = sqlite3_prepare_v2(db, query.c_str(), -1, &pStmt, NULL);
    if(err != SQLITE_OK){
        /* TODO:エラー処理 */
    }else{
        // データの抽出
        while(SQLITE_ROW == (err = sqlite3_step(pStmt)) ){
            int id = sqlite3_column_int(pStmt, 0);
            auto bg =sqlite3_column_text(pStmt, 1);
            ret->setBackground(string((char*)bg));
            
            CCLOG("save_id %d (bg_layer): %s", id, string((char*)bg).c_str());
        }
        if(err != SQLITE_DONE){
            /* TODO: エラー処理 */
        }
    }
    
    
    query = "SELECT * FROM PORTRAITS WHERE SAVE_NO = " + to_string(key) + ";";
    err = sqlite3_prepare_v2(db, query.c_str(), -1, &pStmt, NULL);
    if(err != SQLITE_OK){
        /* TODO:エラー処理 */
    }else{
        // データの抽出
        vector<Memento::P> portraits;
        while(SQLITE_ROW == (err = sqlite3_step(pStmt)) ){
            int save_no = sqlite3_column_int(pStmt, 0);
            auto id =sqlite3_column_text(pStmt, 1);
            auto base_path =sqlite3_column_text(pStmt, 2);
            auto face_id =sqlite3_column_text(pStmt, 3);
            auto face_path =sqlite3_column_text(pStmt, 4);
            auto x =sqlite3_column_int(pStmt, 5);
            auto y =sqlite3_column_int(pStmt, 6);
            auto emo_path =sqlite3_column_text(pStmt, 7);
            auto emo_x =sqlite3_column_int(pStmt, 8);
            auto emo_y =sqlite3_column_int(pStmt, 9);
            
            Memento::P tmp;
            tmp.id = string((char*)id);
            tmp.basePath = string((char*)base_path);
            tmp.face_id = string((char*)face_id);
            tmp.facePath = string((char*)face_path);
            tmp.x = x;
            tmp.y = y;
            tmp.emoPath = string((char*)emo_path);
            tmp.emoX = emo_x;
            tmp.emoY = emo_y;
            
            portraits.push_back(tmp);
        }
        ret->setPortraits(portraits);
        
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


vector<SqliteDAO::LoadInformation> SqliteDAO::getLoadInformation(){
    vector<SqliteDAO::LoadInformation> ret;
    
    string query = "";
    query += "SELECT * FROM DISPLAY ORDER BY SAVE_NO;";
    
    // データの抽出
    // ステートメントの用意
    sqlite3_stmt *pStmt = NULL;
    auto err = sqlite3_prepare_v2(db, query.c_str(), -1, &pStmt, NULL);
    
    if(err != SQLITE_OK){
        /* TODO:エラー処理 */
    }else{
        // データの抽出
        int i = 0;
        while(SQLITE_ROW == (err = sqlite3_step(pStmt)) ){
            ret.push_back(SqliteDAO::LoadInformation());
            ret[i].saveNo = sqlite3_column_int(pStmt, 0);
            ret[i].datetime     = reinterpret_cast<char const *>(sqlite3_column_text(pStmt, 1));
            ret[i].screenShot   = reinterpret_cast<char const *>(sqlite3_column_text(pStmt, 2));
            ret[i].comment      = reinterpret_cast<char const *>(sqlite3_column_text(pStmt, 3));
            i++;
        }
        if(err != SQLITE_DONE){
            /* TODO: エラー処理 */
        }
    }
    
    // ステートメントの解放
    sqlite3_finalize(pStmt);
    
    return ret;
};

NS_NV_END