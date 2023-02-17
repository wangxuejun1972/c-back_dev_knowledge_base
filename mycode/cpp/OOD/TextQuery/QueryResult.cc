#include "QueryResult.h"
#include <sstream>
#include <stdexcept>
#include <utility>
#include "TextQuery.h"
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;
using std::runtime_error;

TextQuery::TextQuery(const string& filename) : _file(new vector<string>()) {
    ifstream ifs(filename);
    if (!ifs) {
        throw runtime_error("No input file!");
    }
    string line;
    while (getline(ifs, line)) {
        _file->push_back(line);
        int n = _file->size() - 1;  //行号
        istringstream iss(line);
        string word;
        while (iss >> word) {
            auto& lines = _wordMap[word];
            if (!lines) {
                lines.reset(new set<line_no>());
            }

            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string& word) const {
    //如果没有找到单词，返回一个指向空行号set的share_ptr
    static shared_ptr<set<line_no>> nodata(new set<line_no>());
    auto it = _wordMap.find(word);
    if (it == _wordMap.end()) {
        return QueryResult(word, nodata, _file);
    } else {
        return QueryResult(word, it->second, _file);
    }
}

ostream& print(ostream& os, const QueryResult& qr) {
    os << qr._queryWord << " occurs " << qr._lines->size() << " "
       << make_plural(qr._lines->size(), "time", "s") << endl;
    for (auto num : *qr._lines) {
        os << "(line " << num + 1 << ") " << *(qr._file->begin() + num) << endl;
    }
    return os;
}