#include "gc.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include "document.h"
#include "istreamwrapper.h"
#include "stringbuffer.h"
#include "writer.h"


GC::GC() {}

std::list<std::string> GC::VISUAL_CONTROLLER_NAMES = std::list<std::string>();
bool GC::USE_INTERFACE_NOT_FILE = false;
bool GC::USE_PEDAL_CONTROL = false;
string GC::EXPERIMENT_FILE_IF_USED = "sample_experiment.json";
int GC::TRIAL_START_PORT=10;
int GC::TRIAL_RESET_PORT=19;
int GC::PEDAL_PORT=17;
int GC::SBJ_READY_PORT=5;
int GC::RESPONSE_INTERRUPT_PORT=24;
int GC::GPIO = lgGpiochipOpen(0);
bool GC::INT_EXECUTION = false;
string GC::V_STIMULI_PATH = "";
vector<int> GC::AUDIO_PORTS = {};
bool GC::loadConfig(string _filename)
{
    int lFlags = 0; /* default line flags */

    rapidjson::Document doc;
    if(!loadJSONFromFile(doc,_filename)){cout << "ERROR LOADING GC CONFIG from " << _filename << "\n"; return false;}
    else cout << "loaded config from " << _filename << " ";
    if(doc.HasMember("VISUAL_CONTROLLER_NAMES")){
        for(auto& g : doc["VISUAL_CONTROLLER_NAMES"].GetArray()){
            GC::VISUAL_CONTROLLER_NAMES.push_back(g.GetString());
            GC::VISUAL_CONTROLLER_NAMES.push_back(g.GetString());
        }
    } else{
        cout << "ERROR: NO VISUAL CONTROLLERS IN config.json. Continuing, but behavior could be undefined.";
    }
    if(doc.HasMember("USE_INTERFACE_NOT_FILE")) GC::USE_INTERFACE_NOT_FILE = doc["USE_INTERFACE_NOT_FILE"].GetBool();
    if(doc.HasMember("USE_PEDAL_CONTROL")) GC::USE_PEDAL_CONTROL = doc["USE_PEDAL_CONTROL"].GetBool();
    if(doc.HasMember("EXPERIMENT_FILE_IF_USED")) GC::EXPERIMENT_FILE_IF_USED = doc["EXPERIMENT_FILE_IF_USED"].GetString();
    if(doc.HasMember("V_STIMULI_PATH")) GC::V_STIMULI_PATH = doc["V_STIMULI_PATH"].GetString();
    if(doc.HasMember("TRIAL_START_PORT")) GC::TRIAL_START_PORT = doc["TRIAL_START_PORT"].GetInt();
    if(doc.HasMember("TRIAL_RESET_PORT")) GC::TRIAL_RESET_PORT = doc["TRIAL_RESET_PORT"].GetInt();
    if(doc.HasMember("SBJ_READY_PORT")) GC::SBJ_READY_PORT = doc["SBJ_READY_PORT"].GetInt();
    if(doc.HasMember("RESPONSE_INTERRUPT_PORT")) GC::RESPONSE_INTERRUPT_PORT = doc["RESPONSE_INTERRUPT_PORT"].GetInt();


    if(doc.HasMember("AUDIO_PORTS")) {
        GC::AUDIO_PORTS.clear();
        for(auto& p : doc["AUDIO_PORTS"].GetArray()){
            int port = p.GetInt();
            GC::AUDIO_PORTS.push_back(port);
            lgGpioClaimOutput(GC::GPIO, lFlags, port, 0); /* initial level 0 */
        }
    }

    // claim port 17 as input for the PEDAL_PORT
    lgGpioClaimInput(GC::GPIO, lFlags, 17);
    // claim ports TRIAL_START_PORT and TRIAL_RESET_PORT as output
    lgGpioClaimOutput(GC::GPIO, lFlags, GC::TRIAL_START_PORT, 0); /* initial level 0 */
    lgGpioClaimOutput(GC::GPIO, lFlags, GC::TRIAL_RESET_PORT, 0); /* initial level 0 */
    // claims ports SBJ_READY_PORT  as output
    lgGpioClaimOutput(GC::GPIO, lFlags, GC::SBJ_READY_PORT , 0); /* initial level 0 */
    // claims ports RESPONSE_INTERRUPT_PORT  as output
    lgGpioClaimOutput(GC::GPIO, lFlags, GC::RESPONSE_INTERRUPT_PORT , 0); /* initial level 0 */

    return true;
}

bool GC::loadJSONFromString(rapidjson::Document &doc, string &jsonstring)
{
    istringstream is(jsonstring);
    rapidjson::IStreamWrapper isw(is);
    doc.ParseStream(isw);
    if(!doc.IsObject() && !doc.IsArray()){ cout << "ERROR LOADING JSON " << jsonstring << "\n"; return false;}
    return true;
}

bool GC::loadJSONFromFile(rapidjson::Document &doc, string filename)
{
    std::fstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    string jsonstring = buffer.str();
    return loadJSONFromString(doc,jsonstring);
}

string GC::getJSONOfValue(rapidjson::Value &v)
{
    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    v.Accept(writer);
    return sb.GetString();
}

string GC::getJSONStringFromFile(string filename)
{
    std::fstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

string GC::getTimeStamp()
{

    std::time_t time = std::time({});
    char timestring[std::size("yyymmddThhmmssZ")];
    std::strftime(std::data(timestring),std::size(timestring),"%Y%m%d%H%M%S",std::localtime(&time));
    return timestring;
}

bool GC::readMessageFromSocket(tcp::socket &socket, string &into_this_string, char delimiter)
{
    try{
        asio::streambuf b;
        asio::read_until(socket,b,delimiter);
        std::istream is(&b);
        std::getline(is,into_this_string,delimiter);
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";
        return false;
    }
    return true;
}

bool GC::writeMessageToSocket(tcp::socket &socket, string &from_this_string, char delimiter)
{
    try{
        asio::error_code ignored_error;
        asio::write(socket,asio::buffer(from_this_string+delimiter),ignored_error);
        return true;
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";
        return false;
    }
}

bool GC::appendToFile(string &filename, string str)
{
    std::string folderName = "TrialOutputs";
    std::filesystem::path folderPath = std::filesystem::current_path() / folderName;
    std::filesystem::path filePath = folderPath / filename;
    std::ofstream fp;
    fp.open(filePath,ios_base::app);
    if(!fp.is_open()) {cout << "ERROR opening file " << filename << "\n"; return false;}
    fp << str;
    fp.close();
    return true;
}

tcp::socket *GC::createNewSocket(int port)
{
    asio::io_context io_context;
    tcp::acceptor acceptor(io_context,tcp::endpoint(tcp::v4(),port));
    tcp::socket* socket = new tcp::socket(io_context);
    acceptor.accept(*socket);
    return socket;
}

void GC::cbf(int e, lgGpioAlert_p evt, void *data)
{
    int i;
    int secs, nanos;

    for (i=0; i<e; i++)
    {
        secs = evt[i].report.timestamp / 1000000000L;
        nanos = evt[i].report.timestamp % 1000000000L;

        printf("chip=%d gpio=%d level=%d time=%d.%09d\n",
               evt[i].report.chip, evt[i].report.gpio, evt[i].report.level,
               secs, nanos);
    }
}
