#include "helperclass.h"
#include <gtest/gtest.h>
#include <types.h>

#include <QtDebug>
#include <QFile>

#include <QRegularExpression>


QStringList getWords(QString line)
{
    QStringList qslRet;
    QRegularExpression re("\\W+");
    QStringList qslWords = line.split(re);

    for(int i=0; i<qslWords.size(); i++){
        if (qslWords.at(i).size() > 3) {
            qslRet.append(qslWords.at(i));
        }
    }
    return qslRet;
}

t_HashStrInt analyseFile(QFile* pFile){
    QTextStream inputFile(pFile);
    helperClass helper;
    t_HashStrInt hashTable;
    while (!inputFile.atEnd()) {
        QStringList qslLineWords = getWords(inputFile.readLine());

        for(int i=0; i<qslLineWords.size(); i++){
            QStringList qslAllCombination = helper.getListByWord(qslLineWords.at(i));
            for(int j=0; j<qslAllCombination.size(); j++){
                QString letters = qslAllCombination.at(j);
                int count = 1;
                if (hashTable.contains(letters)) {
                    count += hashTable.value(letters);
                }
                hashTable.insert(letters, count);
            }
        }
    }
    return hashTable;
}

t_MMap convertHashToMultiMap(t_HashStrInt hash, int* total){
    t_MMap mapRet;

    QString letters;
    int counts;

    t_HashStrInt::const_iterator i = hash.constBegin();
    while (i != hash.constEnd()) {
        letters = i.key();
        counts = i.value();
        *total+=counts;

        mapRet.insert(counts,letters);
        ++i;
    }
    return mapRet;
}

int main(int argc, char *argv[])
{
    int const rowsToPrint = 10;
    if (argc > 1){
        char *fileName = argv[1];
        qInfo() << "Try to parse file " << fileName;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qInfo() << "Can't open file";
            return -1;
        }
        qInfo() << "Start to analyse file" << file.fileName();
        t_HashStrInt unickHash = analyseFile(&file);

        int total = 0;
        qInfo() << "Analyse done, convert hash to multiMap";
        t_MMap multiMap = convertHashToMultiMap(unickHash, &total);
        qInfo() << "Now all items are sorted in multiMap, total count is" << total;

        qInfo() << "Print" << rowsToPrint << "most common letter combinations in percentage:";
        QStringList qslRows;
        qslRows = helperClass::printTopNRows(multiMap, rowsToPrint, total);
        for (int i=0; i<qslRows.size(); i++){
            qInfo() << qslRows.at(i);
        }

        qInfo() << "Print" << rowsToPrint << "most common letter combinations in a bar chart:";
        qslRows = helperClass::printBarRows(multiMap, rowsToPrint, total);
        for (int i=0; i<qslRows.size(); i++){
            qInfo() << qslRows.at(i);
        }

        return 0;
    }
    else {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}


