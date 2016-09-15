#ifndef __BRACKET_HPP__
#define __BRACKET_HPP__

#include<string>
#include<vector>

using std::string;
using std::vector;

class Bracket
{
public: 
    
    // Bracket(string str) : m_name(str)
    // In constructor string is analized
    Bracket(string str);

    bool   IsOpening() {return m_is_opening;}
    string GetName()   {return m_name;}
    string GetBody()   {return m_body;}

private:
    string m_name;
    string m_body;
    bool   m_is_opening;   // is bracket opeining;
};


#endif
