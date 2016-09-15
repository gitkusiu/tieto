#include<iostream>
#include"Bracket.hpp"

using std::cout;

// function which splits string 'str' using separation sign c
vector<string> split(string str, char c)
{
    vector<string> out;
    size_t previous = 0;
    for(size_t i = 0; i <= str.size()+1; i++)
    {
        bool i_is_separator    =  str[i] == c;
        bool i_is_at_the_end   =  str[i] == *(str.end());
        bool is_not_empty_set  =  i-previous != 0;
        
        if(is_not_empty_set)
        {
            int n = i-previous;
            if(i_is_separator || i_is_at_the_end)
            {
                if(i_is_at_the_end) {n++;}
                out.push_back(str.substr(previous,n));
                previous = i+1;
            }
        }
    }
    return out;
}

Bracket::Bracket(string str)
{
    vector<string> s = split(str, ' ');
    int n=s.size();

    string & front = s.front();
    string & back  = s.back();
    if(front.size()      <= 0   ||  // chack basic requirements of  with '<'
       back.size()       <= 0   || 
       front[0]          != '<' ||   
       back[back.size()-1] != '>' )
    { cout << "ERROR";}
    else
    {
        if(front[1] == '/') // analisysy of a closing tag
        {
            if(n==1)
            {
//                cout << "*"+front+"*" << front.size() <<endl;
                m_name = front.substr(2,front.size()-3);
                m_is_opening = false;
            }
            else cout << "Error";
            
        }
        else                // analisysy of a opening tag
        {
            if((n-1)%3==0)  //  if there is proper number of fields
            {
                m_name = front.substr(1,front.size()-1) ; //TODO: chack if name is correct (only letters and idgits)

                m_body += s[1];
                for(int i=2; i<n-1; i++)
                    m_body += " "+s[i];
                string ss = s[n-1];
                m_body += " "+ss.substr(0,ss.size()-1);

                m_is_opening = true;
            }
            else cout << "ERROR";
        }
    }
}
