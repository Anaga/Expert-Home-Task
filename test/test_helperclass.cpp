#include "helperclass.h"
#include "gtest/gtest.h"

using namespace testing;

namespace {


// Test GetCombinationCount function
TEST(GetCombinationCount, ZeroInput) {
    EXPECT_EQ(0, helperClass::getCombinationCount(0));
}

TEST(GetCombinationCount, NegativeInput) {
    EXPECT_EQ(0, helperClass::getCombinationCount(-5));
}

TEST(GetCombinationCount, ShortWord) {
    EXPECT_EQ(0, helperClass::getCombinationCount(3));
}

TEST(GetCombinationCount, SimpleWord) {
    EXPECT_EQ(1, helperClass::getCombinationCount(4));
}

TEST(GetCombinationCount, FiveLetterWord) {
    EXPECT_EQ(3, helperClass::getCombinationCount(5));
}

TEST(GetCombinationCount, SixLetterWord) {
    EXPECT_EQ(6, helperClass::getCombinationCount(6));
}

TEST(GetCombinationCount, SevenLetterWord) {
    EXPECT_EQ(10, helperClass::getCombinationCount(7));
}

TEST(GetCombinationCount, L12n) {
    EXPECT_EQ(45, helperClass::getCombinationCount(12));
}

TEST(GetCombinationCount, i18n) {
    EXPECT_EQ(120, helperClass::getCombinationCount(18));
}

// Test helper class
TEST(HelperClass, ZeroInput){
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord("");
    EXPECT_EQ(0, qsList.size());
    EXPECT_EQ(0, helper.getHashSize());

    qsList = helper.getListByWord("Sun");
    EXPECT_EQ(0, qsList.size());
    EXPECT_EQ(0, helper.getHashSize());
}

TEST(HelperClass, ShortInput){
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord("Test");
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(1, qsList.size());
    EXPECT_TRUE(qsList.contains("Test"));

    qsList = helper.getListByWord("List");
    EXPECT_EQ(2, helper.getHashSize());
    EXPECT_EQ(1, qsList.size());
    EXPECT_TRUE(qsList.contains("List"));

    qsList = helper.getListByWord("Test");
    EXPECT_EQ(2, helper.getHashSize());
    EXPECT_EQ(1, qsList.size());
    EXPECT_TRUE(qsList.contains("Test"));
}

TEST(HelperClass, FiveLetterWord) {
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord("Value");
    ASSERT_EQ(3, qsList.size());
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_TRUE(qsList.contains("Value"));
    EXPECT_TRUE(qsList.contains("Valu"));
    EXPECT_TRUE(qsList.contains( "alue"));
}

TEST(HelperClass, SevenLetterWord) {
    QString word = "Systems";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
}

TEST(HelperClass, i18N) {
    QString word = "Internationalization";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
}

TEST(HelperClass, i18N_VS_l10N) {
    QString word = "Internationalization";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());

    word = "Localization";
    qsList = helper.getListByWord(word);
    EXPECT_EQ(2, helper.getHashSize());

    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
}

TEST(HelperClass, DoubleWord) {
    QString word = "AbcdeBbcde";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
    //qInfo()<< qsList;
}

TEST(HelperClass, TrippleWord) {
    QString word = "AbcdeBbcdeCbcde";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
    //qInfo()<< qsList.size();
    //qInfo()<< qsList;
}

TEST(HelperClass, SomeSpace) {
    QString word = "Namespace";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
    EXPECT_TRUE(qsList.contains("space"));

    word = "spaceless";
    qsList = helper.getListByWord(word);
    EXPECT_TRUE(qsList.contains("space"));

    word = "Workspace";
    qsList = helper.getListByWord(word);
    EXPECT_TRUE(qsList.contains("space"));

    word = "Dataspace";
    qsList = helper.getListByWord(word);
    EXPECT_TRUE(qsList.contains("space"));
    qsList = helper.printHash();
    qsList.clear();
    for (int i=0; i<qsList.size(); i++) {
        qInfo() << qsList.at(i);
    }
}
}  // namespace
