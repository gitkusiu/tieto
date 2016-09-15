#ifndef __TAG_HPP__
#define __TAG_HPP__

#include<utility>
#include<string>
#include<vector>
#include<iostream>
#include"Bracket.hpp"

#include<cassert>
using namespace std;
typedef pair<string,string> PairStr;


extern vector<string> split(string str, char c);


// Class representing tags.
// 
class Tag
{
public:
    Tag(Bracket b);

    void InsertSubTag(Bracket b);

    // method which analize given reference, compare with a strucutre of parsed 
    // atributes/subtags and return a value of a proper atribute.
    string GetAtributeValue(string ref);



    string GetName() {return m_name;}
    bool HasBeenClosed() {return m_closed;}
    void Close() { m_closed = true;}

    vector< Tag >     GetSubTags() { return m_subtags;}
    vector< PairStr > GetAtributes() { return m_atributes;}
    
private:
    string            m_name;         // name of tag 
    vector< PairStr > m_atributes;    // list of atributes
    vector< Tag >     m_subtags;      // list of nested tags
    bool              m_closed;
};







#endif
