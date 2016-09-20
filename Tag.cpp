#include"Tag.hpp"
#include"Bracket.hpp"
#include <stdlib.h>



void Tag::InsertSubTag(Bracket b)
{
    if(b.IsOpening())     //insert new tag
    {
        if( m_subtags.size()<=0 )
        {
            m_subtags.push_back( Tag(b) );
        }
        else
        {
            bool is_closed = m_subtags.back().HasBeenClosed();

            if(is_closed)   m_subtags.push_back( Tag(b) );
            else            m_subtags.back().InsertSubTag(b);
        }
    }
    else                //close existing tag
    {
        if(m_name == b.GetName())
        {
            this->Close();
        }
        else
        {
            assert(m_subtags.size() > 0);
            m_subtags.back().InsertSubTag(b);
        }
    }
}


Tag::Tag(Bracket b) : m_name(b.GetName()),
                      m_closed(false)
    {
        assert(b.IsOpening());   //Tag is created only for opening bracket

        vector<string> s = split(b.GetBody(), ' ');
        assert(s.size()%3==0);

        vector<string>::iterator it;
        for(it = s.begin(); it != s.end(); it = it+3)
        {
            PairStr p(*(it),*(it+2));
            assert(*(it+1) == "=");
            m_atributes.push_back(p);
        }
    }


string Tag::GetAtributeValue(string ref)
{
    size_t i_dot = ref.find(".");        //search for a position of a first dot

    if(i_dot == string::npos)            //if dot has not been found; look for '~'
    {
        size_t i_tylda = ref.find("~");  //search for tylda
        string x = ref.substr(0,i_tylda);
        if(x == m_name)               //check a if name of tag is OK
        {
            string var = ref.substr(i_tylda+1, ref.size()-i_tylda);
            vector<PairStr>::iterator it;
            for(it = m_atributes.begin();      //serch for a atribute with proper name
                it != m_atributes.end();
                it++)
            {
                if(it->first == var) break;
            }

            if( it != m_atributes.end() ) { return it->second; }
            else                    { return "Not Found"; }
        }
        else { return string(""); }
    }
    else                                 //read a subtag
    {
        string x = ref.substr(0,i_dot);
        if(x == m_name)               //check a if name of tag is OK
        {
            string s = ref.substr(i_dot+1, ref.size()-i_dot); //get a subtag part of ref
            //try to get atribute value from each element of subtag
            string t;
            vector<Tag>::iterator it;
            for(it  = m_subtags.begin();
                it != m_subtags.end();
                it++)
            {
                t += it->GetAtributeValue(s); // only one element with return not empty string.
            }
            return t;
        }
        else { return string(""); }
    }
}






