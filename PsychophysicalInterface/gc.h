#ifndef GC_H
#define GC_H

#include <string>
#include "document.h"

#include <QStringList>

using namespace std;

class GC
{
public:
    GC();

    static bool loadJSONFromString(rapidjson::Document& doc,string& jsonstring);
    static string getJSONOfValue(rapidjson::Value& v);
    static string getJSONStringFromFile(string filename);

    static string qenc(string to_encapsulate_in_quotes);

    static QStringList shuffledFileList(const QStringList& originalList);

private:

};



#endif // GC_H
