
#include<sstream>
#include<algorithm>
#include<vector>

#include"Tag.hpp"
#include"TagParser.hpp"

int N, Q;
using namespace std;
int main()
{
    
    string line;
    string text;
    string value;
    cin >> N;
    cin >> Q;
    
    cout << "\nNumber of lines specifing tags is " << N << endl;
    cout << "Number of ines specifing values is "  << Q << endl;
    getline(cin, line);

    cout <<"\n----------- Reading and parsing tags -------------" << endl;
    TagParser parser;
    for(int i=0;i<N;i++)
    {
        getline(cin, line); 
        cout << line << endl;
        parser.ParseNextLine(line);
    }

    vector<Tag> tags = parser.GetTags();
    cout <<"\n----------- Requested values -------------" << endl;
    for(int j=0;j<Q;j++)
    {
        getline(std::cin, line);
        for(Tag t : tags)
        {
            value = t.GetAtributeValue(line);
            if(value != "")
            {
                cout << "requested: " << line << "\t = " << value << endl;
                break;
            }
        }
    }
}
