#include "debugutils.h"

#include <QDebug>

void Nodest::assertion(bool judgement, const QString &file, const QString &func, int line, const QString &info)
{
    if (judgement == false){
        qDebug() << "----------------------------------------";
        qDebug() << "[Nodest Assertion Error]";
        qDebug() << "   file:" << file;
        qDebug() << "   func:" << func;
        qDebug() << "   line:" << line;
        qDebug() << "   info:" << info;
        qDebug() << "----------------------------------------" << "\n";
    }
}

