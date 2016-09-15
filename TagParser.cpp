//#include<iostream>
#include<iostream>
#include <stdlib.h>
#include"TagParser.hpp"

using std::cout;

void TagParser::ParseNextLine(string line)
{
    Bracket b(line);
    if(b.IsOpening())   // opening tag
    {
        if(tags.size()>0)
        {
            if( tags.back().HasBeenClosed() )    tags.push_back( Tag(b) ); 
            else                                 tags.back().InsertSubTag(b);
        }
        else
            tags.push_back( Tag(b) );
    }
    else                // closing tag
    {
        assert(  tags.size()>0               );
        assert( !tags.back().HasBeenClosed() );
        tags.back().InsertSubTag(b);
    }
}

