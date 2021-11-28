#include "helperclass.h"
#include "gtest/gtest.h"

using namespace testing;

namespace {
// Test helper class function getCombinationCount
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

// Test helper class function getListByWord
TEST(getListByWord, ZeroInput){
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord("");
    EXPECT_EQ(0, qsList.size());
    EXPECT_EQ(0, helper.getHashSize());

    qsList = helper.getListByWord("Sun");
    EXPECT_EQ(0, qsList.size());
    EXPECT_EQ(0, helper.getHashSize());
}

TEST(getListByWord, ShortInput){
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

TEST(getListByWord, FiveLetterWord) {
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord("Value");
    ASSERT_EQ(3, qsList.size());
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_TRUE(qsList.contains("Value"));
    EXPECT_TRUE(qsList.contains("Valu"));
    EXPECT_TRUE(qsList.contains( "alue"));
}

TEST(getListByWord, SevenLetterWord) {
    QString word = "Systems";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
}

TEST(getListByWord, i18N) {
    QString word = "Internationalization";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
}

TEST(getListByWord, i18N_VS_l10N) {
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

TEST(getListByWord, DoubleWord) {
    QString word = "AbcdeBbcde";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
    //qInfo()<< qsList;
}

TEST(getListByWord, TrippleWord) {
    QString word = "AbcdeBbcdeCbcde";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(helper.getCombinationCount(word.length()), qsList.length());
}

TEST(getListByWord, SomeSpace) {
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
}


// Test helper class function getListByWord
TEST(printHash, ZeroInput){
    helperClass helper;
    QStringList qsList;

    qsList = helper.getListByWord("");
    EXPECT_EQ(0, helper.getHashSize());
    qsList = helper.printHash();
    EXPECT_TRUE(qsList.isEmpty());
}

TEST(printHash, FourWords){
    helperClass helper;
    QStringList qsList;

    qsList = helper.getListByWord("Letter");
    EXPECT_EQ(1, helper.getHashSize());
    qsList = helper.printHash();
    EXPECT_TRUE(qsList.contains("Letter : [Lett ette tter Lette etter Letter]"));
    EXPECT_FALSE(qsList.contains("Value : [Valu alue Value]"));
    EXPECT_FALSE(qsList.contains("Test : [Test]"));
    EXPECT_FALSE(qsList.contains("Sun : []"));

    qsList = helper.getListByWord("Value");
    EXPECT_EQ(2, helper.getHashSize());
    qsList = helper.printHash();
    EXPECT_TRUE(qsList.contains("Letter : [Lett ette tter Lette etter Letter]"));
    EXPECT_TRUE(qsList.contains("Value : [Valu alue Value]"));
    EXPECT_FALSE(qsList.contains("Test : [Test]"));
    EXPECT_FALSE(qsList.contains("Sun : []"));

    qsList = helper.getListByWord("Test");
    EXPECT_EQ(3, helper.getHashSize());
    qsList = helper.printHash();
    EXPECT_TRUE(qsList.contains("Letter : [Lett ette tter Lette etter Letter]"));
    EXPECT_TRUE(qsList.contains("Value : [Valu alue Value]"));
    EXPECT_TRUE(qsList.contains("Test : [Test]"));
    EXPECT_FALSE(qsList.contains("Sun : []"));

    qsList = helper.getListByWord("Sun");
    EXPECT_EQ(3, helper.getHashSize());
    qsList = helper.printHash();
    EXPECT_TRUE(qsList.contains("Letter : [Lett ette tter Lette etter Letter]"));
    EXPECT_TRUE(qsList.contains("Value : [Valu alue Value]"));
    EXPECT_TRUE(qsList.contains("Test : [Test]"));
    EXPECT_FALSE(qsList.contains("Sun : []"));
}

// Test helper class static function printTopNRows
TEST(printTopNRows, EmptyMap){
    t_MMap testObjMap;
    QStringList qsList;
    qsList =  helperClass::printTopNRows(testObjMap, 0, 0);
    EXPECT_TRUE(qsList.isEmpty());
}

TEST(printTopNRows, ZeroTopLines){
    t_MMap testObjMap;
    testObjMap.insert(3,"Letter : [Lett ette tter Lette etter Letter]");
    testObjMap.insert(2,"Value : [Valu alue Value]]");
    testObjMap.insert(4,"Test : [Test]");
    int total = 3+2+4;

    QStringList qsList;
    qsList =  helperClass::printTopNRows(testObjMap, 0, total);
    EXPECT_TRUE(qsList.isEmpty());
}

TEST(printTopNRows, FirstTopLines){
    t_MMap testObjMap;
    testObjMap.insert(2,"Value");
    testObjMap.insert(2,"alue");
    testObjMap.insert(2,"Valu");
    testObjMap.insert(4,"Test");
    int total = 2+2+2+4;

    QStringList qsList;
    qsList =  helperClass::printTopNRows(testObjMap, 1, total);
    EXPECT_FALSE(qsList.isEmpty());
    EXPECT_EQ(1, qsList.size());
    //qInfo() << qsList;
    EXPECT_TRUE(qsList.contains("      Test : 40.0000%    (4 of 10)"));
}

TEST(printTopNRows, FirstFourLines){
    t_MMap testObjMap;
    testObjMap.insert(1,"Value");
    testObjMap.insert(3,"alue");
    testObjMap.insert(1,"Valu");
    testObjMap.insert(4,"Test");
    int total = 1+3+1+4;

    QStringList qsList;
    qsList =  helperClass::printTopNRows(testObjMap, 4, total);
    EXPECT_FALSE(qsList.isEmpty());
    EXPECT_EQ(4, qsList.size());
    //qInfo() << qsList;
    EXPECT_TRUE(qsList.contains("      Test : 44.4444%    (4 of 9)"));
    EXPECT_TRUE(qsList.contains("      alue : 33.3333%    (3 of 9)"));
    EXPECT_TRUE(qsList.contains("      Valu : 11.1111%    (1 of 9)"));
    EXPECT_TRUE(qsList.contains("     Value : 11.1111%    (1 of 9)"));

    // check order:
    EXPECT_EQ(qsList.at(0), "      Test : 44.4444%    (4 of 9)");
    EXPECT_EQ(qsList.at(1), "      alue : 33.3333%    (3 of 9)");
}

}  // namespace
