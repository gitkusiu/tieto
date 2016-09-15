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

void Tag::InsertOpeningTag(Tag t)
    {
        if(m_name == t.GetName())      // if this is a root tag
        {
            //TODO copy all containers
            m_atributes = t.GetAtributes();
            m_subtags   = t.GetSubTags();
            m_closed    = false;
        }
        else                           // 
        {
            if( m_subtags.size()==0 )           // if all tags has been closed create a new tag and 
            {
                Tag l(t.GetName());
                l.InsertOpeningTag(t);
                m_subtags.push_back(l);
            }
            else
            {
                vector<Tag>::reverse_iterator it;
                for(it=m_subtags.rbegin(); it==m_subtags.rend(); it++)
                {
                    if( !(it->HasBeenClosed()) )   // if there is any open tag inser 't' do it.
                    {
                        it->InsertOpeningTag(t);
                        break;
                    }
                }
            }

        }
    }

    bool Tag::InsertClosingTag(Tag t)
    {
        if(m_name == t.GetName())   // close if 't' has the same tag-name
        {
            if( !HasBeenClosed() )
            {
                Close();
                return true;
            }
            else
            {
                std::cout << "ERROR : Tag can not be cloesed twice.";
                exit(0);
            }
        }
        else                        // pass to proper subtag
        {
            vector<Tag>::iterator it;
            for(it=m_subtags.begin(); it!=m_subtags.end(); it++)
            {
                if( it->InsertClosingTag(t) ){ return true; }
            }
            return false;
        }
    }

//void Tag::PrintAllSubtags(string prefix)
//{
//    cout << prefix + m_name <<  " " << endl;
//    prefix = prefix+"-";
//    for(PairStr a : m_atributes)
//    {
//        cout << prefix + a.first << " = " << a.second << endl;
//    }
//    for(Tag t : m_subtags)
//    {
//        t.PrintAllSubtags(prefix);
//    }
//}


string Tag::GetAtributeValue(string ref)
{
    size_t i_dot = ref.find(".");        //find first dot

    if(i_dot == string::npos)            //last level of nesting; look for '~'
    {
        size_t i_tylda = ref.find("~");  //search for tylda
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






