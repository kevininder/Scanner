#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__

#include "../ScannerLib/Custom_STL.hpp"

using namespace std;
#define Info int, vector<FileInfo>

class FileInfo
{
    friend ostream &operator<<(ostream &out, const FileInfo &info)
    {
        out << "Type: " << info.Type << ", Head: " << info.isHead << ", Content: " << info.Content;
        return out;
    }

    public: 
        string Type;
        string Content;
        int Row;
        bool isHead{};

        FileInfo(string Type, string Content, int Row)
        {
            this->Type = Type;
            this->Content = Content;
            this->Row = Row;
        }
        virtual ~FileInfo() {}
};

namespace Scanner
{
    vector<FileInfo> GetResult(const string &FilePath, const string &TablePath = "", bool SkipWsAndTab = false);
};
#endif // End of __SCANNER_HPP__