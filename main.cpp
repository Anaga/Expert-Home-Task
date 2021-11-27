#include "helperclass.h"
#include <gtest/gtest.h>
#include <types.h>

#include <QtDebug>
#include <QFile>

#include <QRegularExpression>


QStringList process_line(QString line)
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

void printTopNRow(t_MMap map, int N, int totalCount){
    int rowsToPrint = N;
    t_MMap::const_iterator i = map.constEnd();
    float percent = 0.0;
    while (i != map.constBegin()) {
        --i;
        --rowsToPrint;
        percent = (static_cast<float>(i.key()*100))/static_cast<float>(totalCount);
        qInfo() << i.value() << ":" << percent << "% \t: (" << i.key() << ") of " << totalCount;
        if (0==rowsToPrint){
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    helperClass helper;
    t_HashStrInt unickHash;
    t_MMap multiMap;

    if (argc > 1){
        char *fileName = argv[1];
        qInfo() << "Tray to parse file " << fileName;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qInfo() << "Can't open file";
            return -1;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList qslLineWords = process_line(line);
            for(int i=0; i<qslLineWords.size(); i++){
                QStringList qslAllCombination = helper.getListByWord(qslLineWords.at(i));
                //qInfo() << "word to parse: " << qslLineWords.at(i);
                //qInfo() << "go to: " << qslAllCombination;
                for(int j=0; j<qslAllCombination.size(); j++){
                    QString letters = qslAllCombination.at(j);
                    int count = 1;
                    if (unickHash.contains(letters)) {
                        count += unickHash.value(letters);
                    }
                    unickHash.insert(letters, count);
                }
            }
        }
        qInfo() << "Print out all unic letters with 4+ chars";
        t_HashStrInt::const_iterator i = unickHash.constBegin();
        while (i != unickHash.constEnd()) {
           // qInfo() << "N:" << i.value() << "\t: " << i.key();
            ++i;
        }

        qInfo() << "Now we add all items from unickHash to multiMap, to sort all by counts";

        i = unickHash.constBegin();
        QString letters;
        int counts;
        int total = 0;
        while (i != unickHash.constEnd()) {
            letters = i.key();
            counts = i.value();
            total+=counts;

            multiMap.insert(counts,letters);
            ++i;
        }

        qInfo() << "Now all items are sorted in multiMap";
        printTopNRow(multiMap, 10, total);

        return 0;
    }
    else {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}


