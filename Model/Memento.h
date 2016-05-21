//
//  Memento.h
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//

#ifndef __Novelio__Memento__
#define __Novelio__Memento__

#include "../Macros.h"
#include <vector>

NS_NV_BEGIN

class Memento{
public:
    class P{
    public:
        string id;
        string face_id;
        string basePath;
        string facePath;
        string emoPath;
        int x;
        int y;
        int emoX;
        int emoY;
        int scale;
        bool grayout;
    };
    
public:
    Memento();
    ~Memento();
    
private:
    string filename;
    int line;
    int paragraph;
    int sentence;
    string date;
    string thumbnailPath;
    
    string name;
    string text;
    
    string background;
    string bgm;
    string se;
    
    vector<P> portraits;
    
    map<string, string> others;
    
public:
    void setFilename(string filename){this->filename = filename;};
    string getFilename(){return filename;};
    void setLine(int line){this->line = line;};
    int getLine(){return line;};
    void setParagraph(int paragraph){this->paragraph = paragraph;};
    int getParagraph(){return paragraph;};
    void setSentence(int sentence){this->sentence = sentence;};
    int getSentence(){return sentence;};
    void setDate(string date){this->date = date;};
    string getDate(){return date;};
    void setThumbnailPath(string thumbnailPath){this->thumbnailPath = thumbnailPath;};
    string getThumbnailPath(){return thumbnailPath;};
    void setName(string name){this->name = name;};
    string getName(){return name;};
    void setText(string text){this->text = text;};
    string getText(){return text;};
    void setBackground(string background){this->background = background;};
    string getBackground(){return background;};
    void setBGM(string bgm){this->bgm = bgm;};
    string getBGM(){return bgm;};
    void setSE(string se){this->se = se;};
    string getSE(){return se;};
    void setPortraits(vector<P> portraits){this->portraits = portraits;};
    vector<P> getPortraits(){return portraits;};
    void setOthers(map<string, string> others){this->others = others;};
    map<string, string> getOthers(){return others;};
};

NS_NV_END

#endif /* defined(__Novelio__Memento__) */
