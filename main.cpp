
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
    std::string value;
    std::cin >> N;
    std::cin >> Q;
    
    std::cout << "\nNumber of lines specifing tags is " << N  << "." << std::endl;
    std::cout << "Number of ines specifing values is " << Q << "." << std::endl;
    std::getline(std::cin, line);

    std::cout <<"\n----------- Reading and parsing tags -------------" << endl;
//    tab_root.PrintAllSubtags("-");
    TagParser parser;
    for(int i=0;i<N;i++)
    {
        std::getline(std::cin, line); 
        std::cout << line << endl;
        parser.ParseNextLine(line);
    }
    
    vector<Tag> tags = parser.GetTags();
    
    

    
//    std::cout <<"\n\n----------- Printing nested tags        -------------" << endl;
//    tab_root.PrintAllSubtags("-");

//    std::cout <<"\n\n\n----------- PRINT THE RESULTS        -------------" << endl;
//    for(int i=0; i<Q; i++)
//    {
//        std::getline(std::cin, line);
//        cout << line << " = ";
//        cout << tab_root.GetAtributeValue(line) << endl;
//    }

    std::cout <<"\n----------- Requested values -------------" << endl;
    for(int j=0;j<Q;j++)
    {
        std::getline(std::cin, line);
        for(Tag t : tags)
        {
            value = t.GetAtributeValue(line);
            if(value != "")
            {
//                cout << value << endl;
                std::cout <<"requested: " << line << "\t = " << value << endl;
                break;
            }
        }
    }

}
