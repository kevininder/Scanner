#ifndef __MISC_HPP__
#define __MISC_HPP__

#include "Scanner.hpp"

enum Method
{
    SeeRow,
    SeeSpecific
};

extern unordered_set<string> gDataTypes;

bool isIdentifier(const string &s);
bool isOperator(const string &s);
bool isConstant(const string &s);
bool isDataType(const string &s);
bool isKeyword(const string &s);
bool isPreprocessor(const string &s);
bool isLiteral(const string &s);
bool isPunctuator(const string &s);
bool isComment(const string &s);
bool isOther(const string &s);
bool isException(const string &s);
void addInfo(vector<FileInfo> &V, const string &type, string &token, const int &row, set<int> &visitedRow);
void addInfoAlternative(vector<FileInfo> &V, const string &type, const string &token, const int &row, set<int> &visitedRow);
void debugCreate(map<Info> &M, const vector<FileInfo> &V);
void Debug(map<Info> &M, const int &Method, const int &Row, const int &Number);
#endif  // End of __MISC_HPP__