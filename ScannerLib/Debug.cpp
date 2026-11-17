#include "Misc.hpp"

void Debug(map<Info> &M, const int &Method, const int &Row, const int &Number)
{    
    if(!Row || Row > M.size())
    {
        cout << "Invalid row." << endl;
        return;
    }
    switch(Method)
    {
        case SeeRow:
            for(const auto &i : M.at(Row)) cout << i << endl;
            break;
        case SeeSpecific:
            if(Number >= M.at(Row).size())
            {
                cout << "Number is out of bound of the vector." << endl;
                return;
            }
            cout << "[" << Row << "]" << "Position: " << Number << ", " << M.at(Row).at(Number) << endl;
            break;
        default:
            break;
    }
}