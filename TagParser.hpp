#ifndef __TAGPARSER_HPP__
#define __TAGPARSER_HPP__
#include<string>
#include<vector>
#include<utility>
#include"Tag.hpp"
#include"Bracket.hpp"

using std::string;
using std::vector;
using std::pair;

typedef pair<string,string> PairStr;

class TagParser
{
public:
                    TagParser() {}
    void            ParseNextLine(string line);     //parse next line and update tags acordingly
    vector<Tag>     GetTags() {return tags;}

private:
vector< Tag > tags;
};

#endif
