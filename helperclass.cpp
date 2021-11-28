#include "helperclass.h"

helperClass::helperClass()
{

}

int helperClass::getHashSize()
{
    return m_hash.size();
}

QStringList helperClass::getAllLettersList(const QString word)
{
    const int lettersCount = 4;
    const int wordLen = word.length();
    QStringList qslRet;

    if (lettersCount > wordLen) {
        return qslRet;
    }

    if (lettersCount == wordLen) {
        qslRet.append(word);
        m_hash.insert(word, qslRet);
        return qslRet;
    }
    int start = 0;
    int finish = 1+wordLen-lettersCount;
    int chopSize = lettersCount;
    QString chop = "";

    do {
        start=0;
        while (start!=finish) {
            chop=word.mid(start, chopSize);

            if (m_hash.contains(chop)) {
                qslRet<<(m_hash.value(chop));
            } else {
                qslRet.append(chop);
            }
            start++;
        }
        m_hash.insert(word, qslRet);
        chopSize++;
        finish--;
    } while (finish>1);

    qslRet.append(word);
    return qslRet;
}


QStringList helperClass::getListByWord(const QString word)
{
    QStringList qslRet;
    if (word.length()<4){
        return qslRet;
    }

    if (m_hash.contains(word)) {
        return m_hash.value(word);
    }
    else {
        qslRet = getAllLettersList(word);
        m_hash.insert(word, qslRet);
    }
    return qslRet;
}

QStringList helperClass::printHash()
{
    QStringList qslRet;
    QString word;
    QString letters;
    QString format = "%1 : [%2]";
    QHash<QString, QStringList>::const_iterator i = m_hash.constBegin();
    while (i != m_hash.constEnd()) {
        word = i.key();
        letters = i.value().join(" ");
        QString strRow = format.arg(word).arg(letters);
        qslRet.append(strRow);
        ++i;
    }
    return qslRet;
}

int helperClass::getCombinationCount(int N)
{
    if (N<4) return 0;
    if (N==4) return 1;
    //Combination Count is [(N-2)*(N-3)/2]
    return (((N-2)*(N-3))>>1);
}

QStringList helperClass::printBarRows(t_MMap map, int N, int count)
{
    QStringList qslRet;
    int rowsToPrint = N;
    t_MMap::const_iterator i = map.constEnd();
    int const barMaxLength = 50;

    --i; //point to end of map (this is max percent) in map
    QString letters;
    double percentMax = (static_cast<double>(i.key()*100))/static_cast<double>(count);
    int fillCount = barMaxLength;

    QString format = "%1:%2";
    while (i != map.constBegin()) {
        letters = i.value();
        double percent = (static_cast<double>(i.key()*100.0))/static_cast<double>(count);
        fillCount = static_cast<int>((percent*barMaxLength)/percentMax);

        QString strRow = format.arg(letters, 10).arg(' ',fillCount,QChar('#'));
        //qInfo() << strRow;
        qslRet.append(strRow);

        --i;
        --rowsToPrint;

        if (0==rowsToPrint){
            break;
        }
    }
    return qslRet;
}

QStringList helperClass::printTopNRows(t_MMap map, int N, int count)
{
    QStringList qslRet;
    double percent = 0.0;
    QString format = "%1 : %2%    (%3 of %4)";

    t_MMap::const_iterator iter = map.constEnd();
    for (int i=0; i<N; i++){
        iter--; // point to last of map element (this is max percent)
        percent = (static_cast<double>(iter.key()*100))/static_cast<double>(count);
        QString strRow = format.arg(iter.value(), 10).arg(percent, 1, 'f', 4).arg(iter.key()).arg(count);
        //qInfo() << strRow;
        qslRet.append(strRow);

        if (iter==map.constBegin()){
            break;
        }
    }
    return qslRet;
}
