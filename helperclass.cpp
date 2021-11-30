#include "helperclass.h"

helperClass::helperClass()
{

}

int helperClass::getHashSize()
{
    return m_hash.size();
}

QStringList helperClass::getWords(QString line)
{
    QStringList qslRet;
    if (line.isEmpty()) return qslRet;

    QRegularExpression re("\\W+");
    QStringList qslWords = line.split(re);

    for(int i=0; i<qslWords.size(); i++){
        if (qslWords.at(i).size() > 3) {
            qslRet.append(qslWords.at(i));
        }
    }
    return qslRet;
}

QStringList helperClass::getAllLetterList(const QString word)
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
        qslRet = getAllLetterList(word);
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
    int const barMaxLength = 50;
    int fillCount = barMaxLength;
    QStringList qslRet;

    if (map.isEmpty()) return qslRet;

    QString format = "%1:%2";
    QString letters;
    t_MMap::const_iterator iter = map.constEnd();
    iter--; // //point the end of the map (max key value)
    double percentMax = (static_cast<double>(iter.key()*100.0))/static_cast<double>(count);
    double percent;
    for (int i=0; i<N; i++){
        percent = (static_cast<double>(iter.key()*100.0))/static_cast<double>(count);
        fillCount = static_cast<int>((percent*barMaxLength)/percentMax);
        letters = iter.value();

        QString strRow = format.arg(letters, 10).arg(' ',fillCount,QChar('#'));
        qslRet.append(strRow);

        if (iter==map.constBegin()){
            break;
        }
        iter--;
    }
    return qslRet;
}

QStringList helperClass::printTopNRows(t_MMap map, int N, int count)
{
    QStringList qslRet;

    if (map.isEmpty()) return qslRet;

    double percent = 0.0;
    QString format = "%1 : %2%    (%3 of %4)";

    t_MMap::const_iterator iter = map.constEnd();
    for (int i=0; i<N; i++){
        iter--; // //point the end of the map (max key value)
        percent = (static_cast<double>(iter.key()*100))/static_cast<double>(count);
        QString strRow = format.arg(iter.value(), 10).arg(percent, 1, 'f', 4).arg(iter.key()).arg(count);
        qslRet.append(strRow);

        if (iter==map.constBegin()){
            break;
        }
    }
    return qslRet;
}
