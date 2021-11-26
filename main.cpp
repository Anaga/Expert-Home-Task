#include "helperclass.h"
#include <gtest/gtest.h>
#include <QtDebug>

int main(int argc, char *argv[])
{
    helperClass helper;

    helper.printHash();

    QStringList qsList;

    qsList = helper.getListByWord("Item");


    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}


