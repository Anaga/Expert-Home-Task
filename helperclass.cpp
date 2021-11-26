#include "helperclass.h"
#include <QtDebug>

QSet<QString> GetAllLetterSet(const QString word)
{
    const int lettersCount = 4;
    const int wordLen = word.length();
    QSet <QString> qSetRet;

    if (lettersCount == wordLen) {
        qSetRet.insert(word);
        return qSetRet;
    }

    if (lettersCount+1 == wordLen) {
        qSetRet.insert(word);
        qSetRet.insert(word.chopped(1));
        qSetRet.insert(word.right(wordLen-1));
        return qSetRet;
    }

    if (lettersCount+1 < wordLen) {
        qSetRet.insert(word);

        QString const leftPart = word.chopped(1);
        qSetRet.unite(GetAllLetterSet(leftPart));

        QString const rightPart = word.right(wordLen-1);
        qSetRet.unite(GetAllLetterSet(rightPart));
    }
    return qSetRet;
}

int GetCombinationCount(int N)
{
    if (N<4) return 0;

    //Sum is (N-2)*(N-3)/2
    return (((N-2)*(N-3))>>1);
}

helperClass::helperClass()
{
    qDebug() << "helperClass init";
}

int helperClass::getHashSize()
{
    return m_hash.size();
}

QStringList helperClass::GetAllLettersList(const QString word)
{
    if (m_hash.contains(word)) {
        qDebug() << "Word " << word << "already in hash, return from mememory";
        return m_hash.value(word);
    }

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
    QString qsChop = "";


    do {
        start=0;
        qDebug() << "Finish" <<finish << "ChopSize:" << chopSize;
        while (start!=finish) {
            qsChop=word.mid(start, chopSize);

            if (m_hash.contains(qsChop)) {
                qslRet<<(m_hash.value(qsChop));
            } else {
                qslRet.append(qsChop);
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

QStringList helperClass::setToList(QSet<QString> wordSet)
{
    QStringList qslRet = wordSet.toList();
    qslRet.sort();
    return qslRet;
}

QStringList helperClass::getListByWord(QString word)
{
    QStringList qslRet;
    if (word.length()<4){
        return qslRet;
    }

    if (m_hash.contains(word)) {
        qDebug() << "Word " << word << "already in hash, return from mememory";
        return m_hash.value(word);
    }
    else {
        qslRet = GetAllLettersList(word);
        m_hash.insert(word, qslRet);
    }
    return qslRet;
}

void helperClass::printHash()
{
    QHash<QString, QStringList>::const_iterator i = m_hash.constBegin();
    while (i != m_hash.constEnd()) {
        qDebug() << i.key() << ": " << i.value() << endl;
        ++i;
    }
}
