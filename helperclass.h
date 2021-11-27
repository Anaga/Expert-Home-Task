#ifndef HELPERCLASS_H
#define HELPERCLASS_H

#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QStringList>
#include <QHash>
#include <QSet>
#include <QDebug>



class helperClass
{
private:
    //main data storage
    QHash<QString, QStringList> m_hash;
    QStringList GetAllLettersList(const QString word);

public:
    helperClass();
    int getHashSize();
    QStringList getListByWord(const QString word);
    QStringList printHash();

    static int getCombinationCount(int N);
};





#endif // HELPERCLASS_H
