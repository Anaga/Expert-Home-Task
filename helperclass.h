#ifndef HELPERCLASS_H
#define HELPERCLASS_H

#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <types.h>

#include <QDebug>


class helperClass
{
private:
    //main data storage
    t_HashStrList m_hash;
    QStringList getAllLettersList(const QString word);

public:
    helperClass();
    int getHashSize();
    QStringList getListByWord(const QString word);
    QStringList printHash();

    static int getCombinationCount(int N);
    static QStringList printBarRows(t_MMap map, int N, int count);
    static QStringList printTopNRows(t_MMap map, int N, int count);
};





#endif // HELPERCLASS_H
