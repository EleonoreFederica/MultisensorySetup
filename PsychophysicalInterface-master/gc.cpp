#include "gc.h"
#include <sstream>
#include "istreamwrapper.h"
#include <iostream>
#include <fstream>
#include "stringbuffer.h"
#include "writer.h"
#include <random>
#include <algorithm>

GC::GC() {}


string GC::qenc(string to_encapsulate_in_quotes)
{
    return "\""+to_encapsulate_in_quotes+"\"";
}

// Load a JSON object from a string
bool GC::loadJSONFromString(rapidjson::Document &doc, string &jsonstring)
{
    istringstream is(jsonstring);
    rapidjson::IStreamWrapper isw(is);
    doc.ParseStream(isw);
    if(!doc.IsObject()){ cout << "ERROR LOADING JSON " << jsonstring << "\n"; return false;}
    return true;
}

// converts a JSON value (so a single part or component of the whole json file) to string format
string GC::getJSONOfValue(rapidjson::Value &v)
{
    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    v.Accept(writer);
    return sb.GetString();
}

// converts a JSON file in to a string
string GC::getJSONStringFromFile(string filename)
{
    std::fstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

// load a srondom shuffled order of the trials list imported
QStringList GC::shuffledFileList(const QStringList& originalList) {
    QStringList list = originalList;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(list.begin(), list.end(), g);
    return list;
}
