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
    //This constructor should be removed !!!
    Tag(string p_name) : m_name(p_name), m_closed(false) {}
    Tag(Bracket b);

    string GetName() {return m_name;}

    void InsertSubTag(Bracket b);

    void AddAtribute(PairStr a) { m_atributes.push_back(a);}
    void AddAtributes(vector< PairStr > a)
    {
        m_atributes.insert(m_atributes.end(),
                           a.begin(),
                           a.end());
    }

//    void PrintAllSubtags(string prefix);

    // method which analize given reference, compare with a strucutre of parsed 
    // atributes/subtags and return a value of a proper atribute.
    string GetAtributeValue(string ref);
    
    vector< Tag >     GetSubTags() { return m_subtags;}
    vector< PairStr > GetAtributes() { return m_atributes;}
    
    
    bool HasBeenClosed() {return m_closed;}
    void Close() { m_closed = true;}

private:
    string            m_name;         // name of tag 
    vector< PairStr > m_atributes;    // list of atributes
    vector< Tag >     m_subtags;      // list of nested tags
    bool              m_closed;
};







#endif
