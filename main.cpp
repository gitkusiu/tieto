
#include<sstream>
#include<algorithm>
#include<vector>

#include"Tag.hpp"
#include"TagParser.hpp"

int N, Q;



int main()
{
    
    std::string line;
    std::string text;
    std::cin >> N;
    std::cin >> Q;
    
    std::cout << "N=" << N << " Q=" << Q << std::endl;
    std::getline(std::cin, line);

    TagParser parser;
    for(int i=0;i<N;i++)
    {
        std::getline(std::cin, line); 
        parser.ParseNextLine(line);
    }
    
    vector<Tag> tttt = parser.GetTags();
    
    Tag tab_root = tttt[0];
    
//    std::cout <<"\n\n----------- Printing nested tags        -------------" << endl;
//    tab_root.PrintAllSubtags("-");

//    std::cout <<"\n\n\n----------- PRINT THE RESULTS        -------------" << endl;
//    for(int i=0; i<Q; i++)
//    {
//        std::getline(std::cin, line);
//        cout << line << " = ";
//        cout << tab_root.GetAtributeValue(line) << endl;
//    }

}
