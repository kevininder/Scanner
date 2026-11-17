#include "Misc.hpp"

bool isIdentifier(const string &s)
{
    if(isdigit(s.front())) return false;

    for(const auto &c : s)
    {
        if(c == '_') continue;
        if(!iswalnum(c)) return false;
    }

    return true;
}

bool isOperator(const string &s)
{
    const unordered_set<string> Operators
    {
        "+", "-", "*", "/", "<", ">",
        "=", "%", "+=", "-=", "*=", "/=",
        "%=", "<=", ">=", "==", "!", "!=",
        "<<", ">>", "^", "^=", "|", "||",
        "&", "&&", "|=", "&=", "~", "~=",
        "++", "--", "->", "?", "\\", ">>=",
        "<<=", "."
    };

    return Operators.count(s) ? true : false;
}

bool isConstant(const string &s)
{
    if(s.size() >= 3)
    {
        if(isdigit(s.front()) && s.at(1) == 'x') return true;
    }

    return all_of(s.begin(), s.end(), ::isdigit);
}

bool isDataType(const string &s)
{
    return gDataTypes.count(s) ? true : false;
}

bool isKeyword(const string &s)
{
    const unordered_set<string> Keywords
    {
        "if", "else", "do", "while", "switch", "case",
        "break", "return", "for", "continue", "goto",
        "default", "defined", "new", "delete",
        "this", "public", "protected", "private", "override", "sizeof"
    };

    return Keywords.count(s) ? true : false;
}

bool isPreprocessor(const string &s)
{
    const unordered_set<string> Preprocessors
    {
        "#if", "#elif", "#else", "#endif",
        "#define", "#include", "#ifdef", "#ifndef",
        "#error", "#pragma", "#undef", "#warning"
    };
    
    return Preprocessors.count(s) ? true : false;
}

bool isLiteral(const string &s)
{
    return (s.front() == '"' && s.at(s.size() - 1) == '"') || (s.front() == '\'' && s.at(s.size() - 1) == '\'');    // Edge cases, '\'' and "\"".
}

bool isPunctuator(const string &s)
{
    const unordered_set<string> Punctuators{"{", "}", "[", "]", "(", ")", ";", ":", ","};

    return Punctuators.count(s) ? true : false;
}

bool isComment(const string &s)
{
    return s == "//" || s == "/*";
}

bool isOther(const string &s)
{
    return s == " " || s == "\n" || s == "\t" || s == "\r";
}

bool isException(const string &s)
{
    return s == "#";
}

void addInfo(vector<FileInfo> &V, const string &type, string &token, const int &row, set<int> &visitedRow)
{
    FileInfo info(type, token, row);
    const auto [it, inserted] = visitedRow.insert(row);

    if(inserted)
        info.isHead = 1;
    V.push_back(info);
    token.clear();
}

void addInfoAlternative(vector<FileInfo> &V, const string &type, const string &token, const int &row, set<int> &visitedRow)
{
    FileInfo info(type, token, row);
    const auto [it, inserted] = visitedRow.insert(row);

    if(inserted)
        info.isHead = 1;
    V.push_back(info);
}

void debugCreate(map<Info> &M, const vector<FileInfo> &V)
{
    for(const auto &i : V) M[i.Row].push_back(i);
}