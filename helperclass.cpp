#include "helperclass.h"

helperClass::helperClass()
{

}

int helperClass::getHashSize()
{
    return m_hash.size();
}

QStringList helperClass::GetAllLettersList(const QString word)
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
        qslRet = GetAllLettersList(word);
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

QStringList helperClass::printTopNRows(int N, int count)
{

}
