#ifndef LONGSTORY_H
#define LONGSTORY_H
#pragma once

#include "global.h"

enum SouType {
    ZHIHU = 0,
    JUDOU,
    XIOAHONGSHU,
    BOOK,
    CUSTOM
};
enum TextType {
    RAINBOWFART = 0, // 彩虹屁
    EMOTION,         // 情绪
    CHICKENSOUP,     // 鸡汤
    WHISPERSLOVE,    // 情话
    COPYWRITE,        // 文案
    ThreeQuotationsBook
};

typedef struct StuWord{
    SouType enuSouType;
    QString StrCont;
    TextType enuTextType;
    void clear()
    {
        StrCont.clear();
        enuSouType = (SouType)0;
        enuTextType = (TextType)0;
    }
}STU_WORD, *PSTU_WORD;

class LongStory
{
private:
    /*工具函数*/
    SouType GetSouType(_In_ QString str);
    TextType GetTextType(_In_ QString str);
public:
    QStringList openFileToReadData();


public:
    LongStory();

private:
    QVector<STU_WORD> m_StuWord;
};

#endif // LONGSTORY_H
