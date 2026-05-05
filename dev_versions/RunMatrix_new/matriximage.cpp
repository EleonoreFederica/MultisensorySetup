#include "matriximage.h"
#include "sstream"
#include "istreamwrapper.h"


void MatrixImage::reset()
{
    onset=-99;
    offset=-99;
    pixels.clear();
}

bool MatrixImage::parseInfo(std::string jsonstring)
{
    reset();
    rapidjson::Document doc;
    std::istringstream ifs(jsonstring);
    rapidjson::IStreamWrapper isw(ifs);
    doc.ParseStream(isw);
    if(!doc.IsObject()){ std::cout << "FAILED TO READ OBJECT \n"; return false;}
    // std::cout << "json string " << jsonstring << "\n";
    if(doc.HasMember("ONSET")) onset = doc["ONSET"].GetInt();
    else {std::cout << "ERROR: NO ON SPECIFIED\n"; return false;}
    if(doc.HasMember("OFFSET")) offset = doc["OFFSET"].GetInt();
    else {std::cout << "ERROR: NO OFF SPECIFIED\n"; return false;}
    if(doc.HasMember("ISI")) isi = doc["ISI"].GetInt();
    else {std::cout << "ERROR: NO ISI SPECIFIED\n"; return false;}
    if(doc.HasMember("PIXELS")){
        std::cout << "  start pixels...";
        for(auto& g : doc["PIXELS"].GetArray()){
            if(!g.IsArray()) std::cout << "jsonstring is not an array of arrays" << "\n";
            pixels.push_back(Pixel(g.GetArray()[0].GetInt(),g.GetArray()[1].GetInt(),g.GetArray()[2].GetInt(),g.GetArray()[3].GetInt(),g.GetArray()[4].GetInt()));
        }
        std::cout << "...done pixels...\n";
    }
    return true;
}


