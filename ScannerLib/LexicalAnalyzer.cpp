/*
* Author: kevininder
* Repo: https://github.com/kevininder/Scanner
* Description: Scanner acts as a translator between raw program text and the compiler.
               It reads a stream of characters and identifies meaningful words and symbols,
               and transforms them into a structured sequence of tokens that can be easily understood,
               or used in later stages. For more, please see the repo.
*/

#include "Misc.hpp"

namespace Scanner
{
    static void LexicalAnalyzer(vector<FileInfo> &V, int row, string &token, set<int> &visitedRow)
    {
        if(isDataType(token)) addInfo(V, "DataType", token, row, visitedRow);
        else if(isKeyword(token)) addInfo(V, "Keyword", token, row, visitedRow);
        else if(isConstant(token)) addInfo(V, "Constant", token, row, visitedRow);
        else if(isPreprocessor(token)) addInfo(V, "Preprocessor", token, row, visitedRow);
        else if(isIdentifier(token)) addInfo(V, "Identifier", token, row, visitedRow);
        else if(isOperator(token)) addInfo(V, "Operator", token, row, visitedRow);
        else if(isLiteral(token)) addInfo(V, "Literal", token, row, visitedRow);
        else if(isPunctuator(token)) addInfo(V, "Punctuator", token, row, visitedRow);
        else if(isOther(token)) addInfo(V, "Other", token, row, visitedRow);
        else if(isException(token)) addInfo(V, "Other", token, row, visitedRow);
        else
        {
            throw(runtime_error("Invalid token!!"));
        }
    }

    vector<FileInfo> GetResult(const string &FilePath, const string &TablePath, bool SkipWsAndTab)
    {
        int r{1};
        char c;
        set<int> visitedRow;
        stack<string> formatS;
        string data{}, s;
        ifstream File(FilePath), Table(TablePath);
        vector<FileInfo> V;

        if(!File.is_open())
        {
            cout << "Fail opening the file." << endl;
            exit(0);
        }
        else if(FilePath.find(".c") == string::npos && FilePath.find(".cpp") == string::npos
        && FilePath.find(".h") == string::npos && FilePath.find(".hpp") == string::npos)
        {
            cout << "Unsupported file type." << endl;
            exit(0);
        }

        if(Table.is_open())
        {
            while(getline(Table, s))
            {
                gDataTypes.insert(s);
            }
        }
    
        while(File >> noskipws >> c)
        {
            if(isComment(data))
            {
                bool singleComment{};
                string buffer{};
            
                if(data == "//") singleComment = 1;
                if(c == '*') buffer = string(1, c);
                data += string(1, c);

                if((singleComment && c != '\n') || !singleComment)
                {
                    while(File >> noskipws >> c)
                    {
                        data += string(1, c);

                        if(singleComment)
                        {
                            if(c == '\n') break;
                        }
                        else
                        {
                            if(c == '*') buffer = string(1, c);
                            else if(buffer.size() && c == '/') buffer += string(1, c);
                            else buffer.clear();
                            if(buffer == "*/") break;
                            if(c == '\n') r++;
                        }
                    }
                }
                addInfo(V, "Comment", data, r, visitedRow);
                if(c == '\n') r++;
                continue;
            }
            if(data == "#" && (c == ' ' || c == '\t'))
            {
                while(File >> noskipws >> c)
                {
                    if(isOther(string(1, c))) continue;
                    data += string(1, c);
                    if(isPreprocessor(data)) break;
                }
                continue;
            }
            if(isException(data) && isException(string(1, c)))
            {
                LexicalAnalyzer(V, r, data, visitedRow);
                data = string(1, c);
                LexicalAnalyzer(V, r, data, visitedRow);
                continue;
            }
            if(!isException(data) && isException(string(1, c)))
            {
                if(data.size()) LexicalAnalyzer(V, r, data, visitedRow);
                data = string(1, c);
                continue;
            }
            if(isPreprocessor(data) && isOther(string(1, c)))
            {            
                LexicalAnalyzer(V, r, data, visitedRow);
                if(SkipWsAndTab)
                {
                    if(c == ' ' || c == '\t') continue;
                    data = string(1, c);
                    LexicalAnalyzer(V, r++, data, visitedRow);
                }
                else
                {
                    data = string(1, c);
                    LexicalAnalyzer(V, r, data, visitedRow);
                    if(c == '\n') r++;
                }
                continue;
            }
            if(isOther(string(1, c)))
            {
                if(data.size()) LexicalAnalyzer(V, r, data, visitedRow);
                if(SkipWsAndTab)
                {
                    if(c == ' ' || c == '\t') continue;
                    data = string(1, c);
                    LexicalAnalyzer(V, r++, data, visitedRow);
                }
                else
                {
                    data = string(1, c);
                    LexicalAnalyzer(V, r, data, visitedRow);
                    if(data == "\n" || c == '\n') r++;
                }
                continue;
            }
            if(isLiteral(string(1, c)))
            {
                if(data.size()) LexicalAnalyzer(V, r, data, visitedRow);
                data = string(1, c);
                while(File >> noskipws >> c)
                {
                    data += string(1, c);
                    if(isLiteral(data)) break;
                }
                LexicalAnalyzer(V, r, data, visitedRow);
                continue;
            }
            if(!isOperator(data) && isOperator(string(1, c)) && data.size())
            {
                LexicalAnalyzer(V, r, data, visitedRow);
            } 
            if(isOperator(data) && !isOperator(string(1, c)))
            {
                LexicalAnalyzer(V, r, data, visitedRow);
            }
            if(isOperator(data) && isOperator(string(1, c)) && 
            !isOperator(data + string(1, c)) && !isComment(data + string(1, c)))
            {
                LexicalAnalyzer(V, r, data, visitedRow);
                data = string(1, c);
                LexicalAnalyzer(V, r, data, visitedRow);
                continue;
            }
            if(isPunctuator(string(1, c)))
            {
                if(data.size()) LexicalAnalyzer(V, r, data, visitedRow);
                data = string(1, c);
                LexicalAnalyzer(V, r, data, visitedRow);
                continue;
            }
            data += string(1, c);
        }
        if(data.size()) LexicalAnalyzer(V, r, data, visitedRow);    

        return V;
    }
}