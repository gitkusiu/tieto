//#include <limits.h>
#include "TagParser.hpp"
#include "gtest/gtest.h"


TEST(BracketTest, OpeningBracket)
{
    string name("tag1");
//    char c[] = ;
    string atribute("name = \"Test\"");
    string str = "<"+name+" "+atribute+">";
    Bracket br(str);
  
    EXPECT_EQ(name,  br.GetName());
    EXPECT_EQ(true, br.IsOpening());
    EXPECT_EQ(atribute, br.GetBody());
}


TEST(BracketTest, ClosingBracket)
{
    string name("tag1");
    string str = "</"+name+">";
    Bracket br(str);
  
    EXPECT_EQ(name,  br.GetName());
    EXPECT_EQ(false, br.IsOpening());
    EXPECT_EQ("", br.GetBody());
}



TEST(TagTest, Constructor)
{
    string name("tag1");
    string atribute("name = Test");
    string str = "<"+name+" "+atribute+">";
    Bracket br(str);
    Tag     t(br);

    EXPECT_EQ(name,   t.GetName());
    EXPECT_EQ(false,  t.HasBeenClosed());

    PairStr p("name", "Test");
    EXPECT_EQ(1,      t.GetAtributes().size());
    EXPECT_EQ(p,      t.GetAtributes()[0]);

    t.Close();
    EXPECT_EQ(true,   t.HasBeenClosed());
}


TEST(TagTest, InsertSubTag)
{
    string  name1("tag1");
    string  atribute("name = Test");
    Bracket b1("<"+name1+" "+atribute+">");
    Tag     t1(b1);
    PairStr p1("name", "Test");
    EXPECT_EQ(name1,                   t1.GetName());
    EXPECT_EQ(false,                   t1.HasBeenClosed());
    EXPECT_EQ(1,                       t1.GetAtributes().size());
    EXPECT_EQ(PairStr("name", "Test"), t1.GetAtributes()[0]);
    EXPECT_EQ(0,                       t1.GetSubTags().size());


    string  name2("tag2");
    string  atribute2("value = MyValue");
    Bracket b2("<"+name2+" "+atribute2+">");
    t1.InsertSubTag(b2);
    EXPECT_EQ(name1,                       t1.GetName());
    EXPECT_EQ(false,                       t1.HasBeenClosed());
    EXPECT_EQ(1,                           t1.GetAtributes().size());
    EXPECT_EQ(PairStr("name", "Test"),     t1.GetAtributes()[0]);
//  ----------------
    EXPECT_EQ(1,                           t1.GetSubTags().size());
    EXPECT_EQ(name2,                       t1.GetSubTags()[0].GetName());
    EXPECT_EQ(false,                       t1.GetSubTags()[0].HasBeenClosed());
    EXPECT_EQ(1,                           t1.GetSubTags()[0].GetAtributes().size());
    EXPECT_EQ(PairStr("value", "MyValue"), t1.GetSubTags()[0].GetAtributes()[0]);


    t1.InsertSubTag( Bracket("</"+name2+">") );
    EXPECT_EQ(name1,                       t1.GetName());
    EXPECT_EQ(false,                       t1.HasBeenClosed());
    EXPECT_EQ(1,                           t1.GetAtributes().size());
    EXPECT_EQ(PairStr("name", "Test"),     t1.GetAtributes()[0]);
//  ----------------
    EXPECT_EQ(1,                           t1.GetSubTags().size());
    EXPECT_EQ(name2,                       t1.GetSubTags()[0].GetName());
    EXPECT_EQ(true,                        t1.GetSubTags()[0].HasBeenClosed());
    EXPECT_EQ(1,                           t1.GetSubTags()[0].GetAtributes().size());
    EXPECT_EQ(PairStr("value", "MyValue"), t1.GetSubTags()[0].GetAtributes()[0]);


    string s1 = t1.GetAtributeValue("tag1.tag2~value");
    string s2 = t1.GetAtributeValue("tag1~name");
    string s3 = t1.GetAtributeValue("tag1~value");
    EXPECT_EQ("MyValue",     s1);
    EXPECT_EQ("Test",s2);
    EXPECT_EQ("Not Found",   s3);
}


TEST(TagParserTest, ClosingParseNextLine)
{
    TagParser parser;
    parser.ParseNextLine("<tag1 value = \"HelloWorld\">");

    vector<Tag> tags = parser.GetTags();
    EXPECT_EQ(1, tags.size());

    Tag x = tags[0];
    EXPECT_EQ(0, x.GetSubTags().size());

    vector<PairStr> l_atrs = x.GetAtributes();
    EXPECT_EQ(1,                l_atrs.size());
    EXPECT_EQ("value",          l_atrs[0].first);
    EXPECT_EQ("\"HelloWorld\"", l_atrs[0].second);



//    parser.ParseNextLine("<tag2 name = \"Name1\">");

//    tags = parser.GetTags();
//    EXPECT_EQ(1, tags.size());

//    x = tags[0];
//    EXPECT_EQ(1, x.GetSubTags().size());
//    
//    l_atrs = x.GetAtributes();
//    EXPECT_EQ(1,                l_atrs.size());
//    EXPECT_EQ("value",          l_atrs[0].first);
//    EXPECT_EQ("\"HelloWorld\"", l_atrs[0].second);
//    
//    vector<Tag> subtags = x.GetSubTags();
    
}



GTEST_API_ int main(int argc, char **argv) {



  
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
  

