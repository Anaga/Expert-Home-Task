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


// Test helper class function printHash
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

TEST(printTopNRows, ZeroTopRows){
    t_MMap testObjMap;
    testObjMap.insert(3,"Letter");
    testObjMap.insert(2,"Value");
    testObjMap.insert(4,"Test");
    int total = 3+2+4;

    QStringList qsList;
    qsList =  helperClass::printTopNRows(testObjMap, 0, total);
    EXPECT_TRUE(qsList.isEmpty());
}


TEST(printTopNRows, OneRowMap){
    t_MMap testObjMap;
    testObjMap.insert(1,"Test");
    int total = 1;

    QStringList qsList;
    qsList =  helperClass::printTopNRows(testObjMap, 1, total);
    EXPECT_EQ(1, qsList.size());
    EXPECT_TRUE(qsList.contains("      Test : 100.0000%    (1 of 1)"));
}

TEST(printTopNRows, OneRowMapPercent){
    t_MMap testObjMap;
    testObjMap.insert(4,"Test");
    int total = 4;

    QStringList qsList;
    qsList =  helperClass::printTopNRows(testObjMap, 1, total);
    EXPECT_EQ(1, qsList.size());
    EXPECT_TRUE(qsList.contains("      Test : 100.0000%    (4 of 4)"));
}

TEST(printTopNRows, FirstTopRows){
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
    EXPECT_TRUE(qsList.contains("      Test : 40.0000%    (4 of 10)"));
}

TEST(printTopNRows, FirstFourRows){
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

    EXPECT_TRUE(qsList.contains("      Test : 44.4444%    (4 of 9)"));
    EXPECT_TRUE(qsList.contains("      alue : 33.3333%    (3 of 9)"));
    EXPECT_TRUE(qsList.contains("      Valu : 11.1111%    (1 of 9)"));
    EXPECT_TRUE(qsList.contains("     Value : 11.1111%    (1 of 9)"));

    // check order:
    EXPECT_EQ(qsList.at(0), "      Test : 44.4444%    (4 of 9)");
    EXPECT_EQ(qsList.at(1), "      alue : 33.3333%    (3 of 9)");
}

// Test helper class static function printBarRows
TEST(printBarRows, EmptyMap){
    t_MMap testObjMap;
    QStringList qsList;
    qsList =  helperClass::printBarRows(testObjMap, 0, 0);
    EXPECT_TRUE(qsList.isEmpty());
}

TEST(printBarRows, ZeroTopRows){
    t_MMap testObjMap;
    testObjMap.insert(3,"Letter");
    testObjMap.insert(2,"Value");
    testObjMap.insert(4,"Test");
    int total = 3+2+4;

    QStringList qsList;
    qsList =  helperClass::printBarRows(testObjMap, 0, total);
    EXPECT_TRUE(qsList.isEmpty());
}


TEST(printBarRows, OneRowMap){
    t_MMap testObjMap;
    testObjMap.insert(1,"Test");
    int total = 1;

    QStringList qsList;
    qsList =  helperClass::printBarRows(testObjMap, 1, total);
    EXPECT_EQ(1, qsList.size());
    //First row in printBarRows shall always have barMaxLength -1 # (49)
    EXPECT_EQ(qsList.at(0), "      Test:################################################# ");
    EXPECT_EQ(49, qsList.at(0).count('#'));
}

TEST(printBarRows, FirstTopLines){
    t_MMap testObjMap;
    testObjMap.insert(2,"Value");
    testObjMap.insert(2,"alue");
    testObjMap.insert(2,"Valu");
    testObjMap.insert(4,"Test");
    int total = 2+2+2+4;

    QStringList qsList;
    qsList =  helperClass::printBarRows(testObjMap, 1, total);
    EXPECT_FALSE(qsList.isEmpty());
    EXPECT_EQ(1, qsList.size());
    //First row in printBarRows shall always have barMaxLength -1 # (49)
    EXPECT_EQ(qsList.at(0), "      Test:################################################# ");
    EXPECT_EQ(49, qsList.at(0).count('#'));
}

TEST(printBarRows, FirstFourLines){
    t_MMap testObjMap;
    testObjMap.insert(1,"Value");
    testObjMap.insert(3,"alue");
    testObjMap.insert(1,"Valu");
    testObjMap.insert(4,"Test");
    int total = 1+3+1+4;

    QStringList qsList;
    qsList =  helperClass::printBarRows(testObjMap, 4, total);
    EXPECT_FALSE(qsList.isEmpty());
    EXPECT_EQ(4, qsList.size());

    qInfo() << qsList;
    //First row in printBarRows shall always have barMaxLength -1 # (49)
    EXPECT_EQ(qsList.at(0), "      Test:################################################# ");
    EXPECT_EQ(49, qsList.at(0).count('#'));

    //Second row in printBarRows shall have (barMaxLength * count percent) normalise by top row (4). For 3 from 9 it will be ((3/9)*(50*9/4)) = (0.75*50)-1 = 36
    EXPECT_EQ(qsList.at(1), "      alue:#################################### ");
    EXPECT_EQ(36, qsList.at(1).count('#'));

    //Next row - 1 from 9 - it will be (1/4 * 50) = (50/4)-1 = 11
    EXPECT_TRUE(qsList.contains("      Valu:########### "));
    EXPECT_EQ(11, qsList.at(2).count('#'));

    //Next row - the same
    EXPECT_TRUE(qsList.contains("     Value:########### "));
    EXPECT_EQ(11, qsList.at(2).count('#'));
}

// Test helper class static function getWords
TEST(getWords, EmptyInput){
    QStringList qsList;
    qsList =  helperClass::getWords("");
    EXPECT_TRUE(qsList.isEmpty());
}

TEST(getWords, OneWord){
    QStringList qsList;
    qsList =  helperClass::getWords("Word");
    ASSERT_FALSE(qsList.isEmpty());
    EXPECT_EQ(qsList.at(0), "Word");
}

TEST(getWords, OneShortWord){
    QStringList qsList;
    qsList =  helperClass::getWords("Sun");
    EXPECT_TRUE(qsList.isEmpty());
}

TEST(getWords, FourShortWord){
    QStringList qsList;
    qsList =  helperClass::getWords("The Sun is a ");
    EXPECT_TRUE(qsList.isEmpty());
}

TEST(getWords, SentenceWithOneBigWord){
    QStringList qsList;
    qsList =  helperClass::getWords("The Sun is a star");
    ASSERT_FALSE(qsList.isEmpty());
    EXPECT_EQ(qsList.at(0), "star");
}

TEST(getWords, OneLine){
    QStringList qsList;
    QString line = "This documentation describes deployment process for Windows. We refer to the plug & paint example application through out the document to demonstrate the deployment process.";
    qsList =  helperClass::getWords(line);
    ASSERT_FALSE(qsList.isEmpty());
    EXPECT_EQ(qsList.size(), 16);
    EXPECT_TRUE(qsList.contains("documentation"));
    EXPECT_TRUE(qsList.contains("Windows"));
    EXPECT_TRUE(qsList.contains("application"));
    EXPECT_TRUE(qsList.contains("document"));
    EXPECT_TRUE(qsList.contains("demonstrate"));
    EXPECT_TRUE(qsList.contains("deployment"));
}

TEST(getWords, OneLineWithRepeatWords){
    QStringList qsList;
    qsList =  helperClass::getWords("Qt for Windows - Deployment, Qt for Windows - Deployment");
    ASSERT_FALSE(qsList.isEmpty());
    EXPECT_EQ(qsList.size(), 4);
    EXPECT_EQ(qsList.at(0), "Windows");
    EXPECT_EQ(qsList.at(1), "Deployment");
    EXPECT_EQ(qsList.at(2), "Windows");
    EXPECT_EQ(qsList.at(3), "Deployment");
}

TEST(getWords, LineWithNotOnlyLetters){
    QStringList qsList;
    QString line = "Strings can be added to a list using the insert() append(), operator+=() and operator<<() functions.";
    qsList =  helperClass::getWords(line);
    ASSERT_FALSE(qsList.isEmpty());
    EXPECT_EQ(qsList.size(), 9);
    EXPECT_TRUE(qsList.contains("Strings"));
    EXPECT_TRUE(qsList.contains("added"));
    EXPECT_TRUE(qsList.contains("list"));
    EXPECT_TRUE(qsList.contains("using"));
    EXPECT_TRUE(qsList.contains("insert"));
    EXPECT_TRUE(qsList.contains("append"));
    EXPECT_TRUE(qsList.contains("operator"));
    EXPECT_TRUE(qsList.contains("functions"));
}

TEST(getWords, AssemblerLine){
    QStringList qsList;
    QString line = "        xor     %rax, %rax              # rax will hold the current number";
    qsList =  helperClass::getWords(line);
    ASSERT_FALSE(qsList.isEmpty());
    EXPECT_EQ(qsList.size(),4);
    EXPECT_TRUE(qsList.contains("will"));
    EXPECT_TRUE(qsList.contains("hold"));
    EXPECT_TRUE(qsList.contains("current"));
    EXPECT_TRUE(qsList.contains("number"));
}

}  // namespace
