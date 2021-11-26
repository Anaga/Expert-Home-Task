#include "helperclass.h"
#include "gtest/gtest.h"

using namespace testing;

namespace {


// Test GetCombinationCount function
TEST(GetCombinationCount, ZeroInput) {
    EXPECT_EQ(0, GetCombinationCount(0));
}

TEST(GetCombinationCount, NegativeInput) {
    EXPECT_EQ(0, GetCombinationCount(-5));
}

TEST(GetCombinationCount, ShortWord) {
    EXPECT_EQ(0, GetCombinationCount(3));
}

TEST(GetCombinationCount, SimpleWord) {
    EXPECT_EQ(1, GetCombinationCount(4));
}

TEST(GetCombinationCount, FiveLetterWord) {
    EXPECT_EQ(3, GetCombinationCount(5));
}

TEST(GetCombinationCount, SixLetterWord) {
    EXPECT_EQ(6, GetCombinationCount(6));
}

TEST(GetCombinationCount, SevenLetterWord) {
    EXPECT_EQ(10, GetCombinationCount(7));
}

TEST(GetCombinationCount, L12n) {
    EXPECT_EQ(45, GetCombinationCount(12));
}

TEST(GetCombinationCount, i18n) {
    EXPECT_EQ(120, GetCombinationCount(18));
}

// Test GetAllLetterSet function
TEST(GetAllLetterSet, EmptyWord) {
    EXPECT_EQ(0, GetAllLetterSet("").size());
}

TEST(GetAllLetterSet, ShortWord) {
    EXPECT_EQ(0, GetAllLetterSet("Sun").size());
}


TEST(GetAllLetterSet, SimpleWord) {
    QSet<QString> qsWordsSet = GetAllLetterSet("Word");
    ASSERT_EQ(1, qsWordsSet.size());
    EXPECT_TRUE(qsWordsSet.contains("Word"));
}

TEST(GetAllLetterSet, FiveLetterWord) {
    QSet<QString> qsWordsSet = GetAllLetterSet("Issue");
    ASSERT_EQ(3, qsWordsSet.size());
    EXPECT_TRUE(qsWordsSet.contains("Issue"));
    EXPECT_TRUE(qsWordsSet.contains("Issu"));
    EXPECT_TRUE(qsWordsSet.contains( "ssue"));
}

TEST(GetAllLetterSet, SixLetterWord) {
    QSet<QString> qsWordsSet = GetAllLetterSet("Output");
    EXPECT_EQ(6, qsWordsSet.size());
    EXPECT_TRUE(qsWordsSet.contains("Output"));
    EXPECT_TRUE(qsWordsSet.contains("Outpu"));
    EXPECT_TRUE(qsWordsSet.contains("Outp"));

    EXPECT_TRUE(qsWordsSet.contains( "utput"));
    EXPECT_TRUE(qsWordsSet.contains( "utpu"));

    EXPECT_TRUE(qsWordsSet.contains( "tput"));
}

TEST(GetAllLetterSet, SevenLetterWord) {
    QSet<QString> qsWordsSet = GetAllLetterSet("Console");
    EXPECT_EQ(10, qsWordsSet.size());
    EXPECT_TRUE(qsWordsSet.contains("Console"));
    EXPECT_TRUE(qsWordsSet.contains("Consol" ));
    EXPECT_TRUE(qsWordsSet.contains("Conso"  ));
    EXPECT_TRUE(qsWordsSet.contains("Cons"   ));

    EXPECT_TRUE(qsWordsSet.contains( "onsole"));
    EXPECT_TRUE(qsWordsSet.contains( "onsol" ));
    EXPECT_TRUE(qsWordsSet.contains( "onso"  ));

    EXPECT_TRUE(qsWordsSet.contains(  "nsole"));
    EXPECT_TRUE(qsWordsSet.contains(  "nsol" ));

    EXPECT_TRUE(qsWordsSet.contains(   "sole"));
}

TEST(GetAllLetterSet, L12n) {
    QSet<QString> qsWordsSet = GetAllLetterSet("Localization");
    EXPECT_EQ(45, qsWordsSet.size());

    EXPECT_TRUE(qsWordsSet.contains("Localization"));
    EXPECT_TRUE(qsWordsSet.contains("Localizatio" ));
    EXPECT_TRUE(qsWordsSet.contains("Localizati"  ));
    EXPECT_TRUE(qsWordsSet.contains("Localizat"   ));

    EXPECT_TRUE(qsWordsSet.contains("lization"));
    EXPECT_TRUE(qsWordsSet.contains("lizatio" ));
    EXPECT_TRUE(qsWordsSet.contains("lizati"  ));
    EXPECT_TRUE(qsWordsSet.contains("lizat"   ));
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
    EXPECT_EQ(GetCombinationCount(word.length()), qsList.length());
    qDebug() << qsList;
}

TEST(HelperClass, i18N) {
    QString word = "Internationalization";
    helperClass helper;
    QStringList qsList;
    qsList = helper.getListByWord(word);
    EXPECT_EQ(1, helper.getHashSize());
    EXPECT_EQ(GetCombinationCount(word.length()), qsList.length());
    qDebug() << qsList;
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

    EXPECT_EQ(GetCombinationCount(word.length()), qsList.length());
    qDebug() << qsList;
    helper.printHash();
}

}  // namespace
