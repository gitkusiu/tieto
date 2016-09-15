//#include<iostream>
#include<iostream>
#include <stdlib.h>
#include"TagParser.hpp"

using std::cout;

void TagParser::ParseNextLine(string line)
{
    Bracket b(line);
    if(b.IsOpening())   // if bracket contains opening tag
    {
        if(tags.size()>0)
        {
            if( tags.back().HasBeenClosed() )    tags.push_back( Tag(b) ); 
            else                                 tags.back().InsertSubTag(b);
        }
        else
            tags.push_back( Tag(b) );
    }
    else                //
    {
        assert(  tags.size()>0               );
        assert( !tags.back().HasBeenClosed() );
        tags.back().InsertSubTag(b);
    }
}


vector<PairStr> TagParser::ParsBracketAtributes(string atributes)
{
    vector<string> s = split(atributes, ' ');
    
    vector<PairStr> out;
    vector<string>::iterator it;
    if( s.size()%3==0 )
    {
        for(it = s.begin(); it != s.end(); it = it+3)
        {
            PairStr p(*(it),*(it+2));
            if(*(it+1) == "=") { out.push_back(p); }
            else           { std::cout << "ERROR : wrong operator";}
        }
    }
    else
    {
        std::cout << "ERROR : Wrong number of atributes.";
        exit(0);
    }
    return out;
}

