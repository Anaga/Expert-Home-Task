#include "helperclass.h"
#include <gtest/gtest.h>
#include <QtDebug>

int main(int argc, char *argv[])
{
    helperClass helper;

    helper.printHash();

    QStringList qsList;

    qsList = helper.getListByWord("Item");
    qDebug() << qsList;


    qsList = helper.getListByWord("Local");
    qDebug() << qsList;


    qsList = helper.getListByWord("Output");
    qDebug() << qsList;


    qsList = helper.getListByWord("Localisation");
    qDebug() << qsList;

    qDebug() << "Same word!";
    qsList = helper.getListByWord("Localisation");
    qDebug() << qsList;
    helper.printHash();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}


