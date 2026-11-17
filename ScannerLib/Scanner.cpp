// Scanner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Misc.hpp"

int main()
{
    string Path;
    getline(cin, Path);

    for(const auto &Item : Scanner::GetResult(Path))
	    cout << Item.Content;
}