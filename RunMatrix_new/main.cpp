#include <iostream>
#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <fstream>
#include <string>
#include "rapidjson.h"
#include "stringbuffer.h"
#include "writer.h"
#include "document.h"
#include "istreamwrapper.h"
#include <asio.hpp>

#include "graphics.h"
#include "pixel-mapper.h"
#include "matriximage.h"



using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using asio::ip::tcp;


volatile bool interrupt_received = false;

int INPUT_TRIAL_RESET_PORT = 0;
int INPUT_TRIAL_ON_PORT = 0;
int INPUT_RESPONSE_INTERRUPT_PORT = 0;
int MATRICES_CHAINED = 1;
const int WIDTH = 64;
const int HEIGHT = 64;
std::string SERVER_ADDRESS;
std::string SERVER_PORT;
std::string MY_NAME;
uint64_t triggers=0;
std::vector<MatrixImage> images;
int stim_duration;


bool firsttime=true;

bool no_stimuli; // used inside the update image function as a flag to know whther the function has exited false for this reason

enum STATE{NEW_TRIAL,REQUESTING_IMAGE,NO_STIMULI,WAITING_FOR_TRIAL,RUNNING_TRIAL,FINISH};
STATE state=NEW_TRIAL;


static void InterruptHandler(int signo) {    interrupt_received = true;}

// gets file (for file like text file) in JSON format
// returns the content as a string
static std::string getStringFromFile(std::string filename){
    std::fstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

// gets the string in JSON format
// parses the content and if all data are correct returns true (it only reads it)
static bool readJSONFromString(rapidjson::Document& doc,std::string& jsonstring){
    try{
        std::istringstream ifs(jsonstring);
        rapidjson::IStreamWrapper isw(ifs);
        doc.ParseStream(isw);
        return true;
    }
    catch(std::system_error& e){
        std::cerr << "Failed to parse json string " << e.what() <<"\n";
        return false;
    }
}

// !! ACTUALLY NEVER USED FUNCTION !!
// get a string in JSON format (like the output of getStringFromFile)
// reads the string, loads it into a JSON object, parses it and returns 'true' if everything is okay
static bool loadJSONFromString(rapidjson::Document& doc, std::string& jsonstring){
    std::istringstream ifs(jsonstring);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string toread = buffer.str();
    return readJSONFromString(doc, toread);
}

// it combines in one single functions the conversion of JSON into a string
// and reading the string by executing the parsing
static bool readJSONFromFile(rapidjson::Document& doc,std::string filename){
    std::string toread = getStringFromFile(filename); // take the json file and esxtract the content in a string format
    return readJSONFromString(doc,toread);
}

static bool readConfig(){
    try{
        std::cout << "Loading config...";
        rapidjson::Document doc;
        if(!readJSONFromFile(doc,"config.json")) {std::cerr << "Error loading config.json"; return false;}
        SERVER_ADDRESS = doc["SERVER_ADDRESS"].GetString();
        SERVER_PORT = doc["SERVER_PORT"].GetString();
        MY_NAME = doc["MY_NAME"].GetString();
        INPUT_TRIAL_ON_PORT = doc["INPUT_TRIAL_ON_PORT"].GetInt();
        INPUT_TRIAL_RESET_PORT = doc["INPUT_TRIAL_RESET_PORT"].GetInt();
        INPUT_RESPONSE_INTERRUPT_PORT = doc["INPUT_RESPONSE_INTERRUPT_PORT"].GetInt();
        MATRICES_CHAINED = doc["MATRICES_CHAINED"].GetInt();
        std::cout << "...done\n";
        return true;
    }
    catch(std::system_error& e){
        std::cerr << "Failed to load config " << e.what() <<"\n";
        return false;
    }
}

//static bool readTrial(std::string &imageinfo, std::vector<MatrixImage> &images) {
//    try{
//        rapidjson::Document doc;
//        if (doc.Parse(imageinfo.c_str()).HasParseError()) {
//            std::cerr << "Error parsing JSON: " << imageinfo << "\n";
//            return false;
//        }
//        // check for trial duration and stimuli field existance
//        if (!doc.HasMember("DURATION") || !doc.HasMember("STIMULI")) {
//            std::cerr << "JSON missing required fields: " << imageinfo << "\n";
//            return false;
//        }
//        // extyract `stim_duration`
//        stim_duration = doc["DURATION"].GetInt(); // trial_ration has the value of duration
//        std::cout << "  Trial duration: " << stim_duration << "ms\n";

//        // extract `STIMULI` and create corrispondent objects
//        const rapidjson::Value& stimuli_array = doc["STIMULI"].GetArray(); // strimuli_array is the array of all the json-format stimuli
//        if (!stimuli_array.IsArray()) {
//            std::cerr << "STIMULI is not an array\n";
//            return false;
//        } else if (stimuli_array.Empty()) { // if the stimuly array is empty = no stimuli for tis slave in this trial
//            no_stimuli=true; // flag for NO_STIMULI
//            return false;
//        }

//        // now create as output an array of MatrixImage objects, each corresponding to a visual stimulus configuration:
//        // {"ONSET": <value>, "OFFEST": <value>, "PIXELS": [...]}
//        images.clear();
//        for (rapidjson::SizeType i = 0; i < stimuli_array.Size(); ++i){
//            const rapidjson::Value& stimulus = stimuli_array[i];
//            if(stimulus.IsObject()){
//                rapidjson::StringBuffer buffer;
//                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//                stimulus.Accept(writer); // Scrive l'oggetto nel buffer

//                std::string stimulus_string = buffer.GetString();
//                MatrixImage img;
//                if (img.parseInfo(stimulus_string)) { // parsing the object img
//                    images.push_back(img); // if the parsing is fine, add the object element (appending) to the images array
//                } else {
//                    std::cout << "Error parsing image stimulus index: " << i << "\n";
//                    return false;
//                }
//            }
//        }

//        return true;
//    }
//    catch(std::system_error& e){
//        std::cerr << "Failed to load config " << e.what() <<"\n";
//        return false;
//    }
//}

static bool readTrial(std::string &imageinfo, std::vector<MatrixImage> &images) {
    try {
        rapidjson::Document doc;
        if (doc.Parse(imageinfo.c_str()).HasParseError()) {
            std::cerr << "Error parsing JSON: " << imageinfo << "\n";
            return false;
        }

        // Controlla che i campi obbligatori siano presenti
        if (!doc.HasMember("ONSET") || !doc.HasMember("OFFSET") || !doc.HasMember("PIXELS")) {
            std::cerr << "JSON missing required fields: ONSET, OFFSET, or PIXELS\n";
            return false;
        }

        // extract `STIMULI` and create corrispondent objects
        const rapidjson::Value& stimuli_array = doc["STIMULI"].GetArray(); // strimuli_array is the array of all the json-format stimuli
        if (!stimuli_array.IsArray()) {
           std::cerr << "STIMULI is not an array\n";
           return false;
        } else if (stimuli_array.Empty()) { // if the stimuly array is empty = no stimuli for tis slave in this trial
           no_stimuli=true; // flag for NO_STIMULI
           return false;
        }

        // Pulisce il vettore delle immagini
        images.clear();

        // Converte il JSON intero in stringa per compatibilità con MatrixImage::parseInfo()
        for (rapidjson::SizeType i = 0; i < stimuli_array.Size(); ++i){
            const rapidjson::Value& stimulus = stimuli_array[i];
            if(stimulus.IsObject()){
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                stimulus.Accept(writer); // Scrive l'oggetto nel buffer

                std::string stimulus_string = buffer.GetString();
                MatrixImage img;
                if (img.parseInfo(stimulus_string)) { // parsing the object img
                    images.push_back(img); // if the parsing is fine, add the object element (appending) to the images array
                } else {
                    std::cout << "Error parsing image stimulus index: " << i << "\n";
                    return false;
                }
            }
        }


        // Imposta la durata del trial come offset + margine (se non viene usata altrove)
        // stim_duration = img.offset + img.isi;  // oppure usa un valore fisso/marginato

        // Debug print
//        std::cout << "  ONSET: " << img.onset << ", OFFSET: " << img.offset << ",  ISI: " << img.isi;
//        std::cout << ", PX COUNT: " << img.pixels.size() << std::endl;


        return true;
    }
    catch (std::system_error& e) {
        std::cerr << "Failed to load config " << e.what() << "\n";
        return false;
    }
}
void drawImage(Canvas* canvas,std::vector<Pixel>& pixels){
    for(auto& p : pixels) {
        canvas->SetPixel(p.x,p.y,p.r,p.g,p.b);
    }
}


bool updateImageFromNetwork(){
    std::cout << "  Updating image from network: start TCP communication...";
    try{
        no_stimuli=false;
        // auto start = std::chrono::high_resolution_clock::now();
        // start connetion to the network through tcp
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(SERVER_ADDRESS,SERVER_PORT);
        tcp::socket socket(io_context);
        asio::connect(socket,endpoints);
        std::cout << "...connection made...\n";
        // communication of the slave name
        asio::streambuf b;
        std::ostream os(&b);
        os << MY_NAME <<"#";
        asio::write(socket,b);
        b.consume(b.size()+1);
        // reading from the port all the tx message (the data about the trial)
        asio::read_until(socket,b,'#');
        std::istream is(&b);
        std::string imageinfo;
        std::getline(is,imageinfo,'#'); // here imageinfo is now the json file of the single trial {"DURATION":<value>, "STIMULI": [{stim_1},{},...{}]}
        // extraction of the 2 elements: duration value AND the array of stimuli
        bool string_is_ok = true; // variable for checking the exitus of the function readData
        string_is_ok = readTrial(imageinfo,images);
        if(!string_is_ok) // the reading of the trial failed
            return false;
        else{
            // auto finish = std::chrono::high_resolution_clock::now();
            for(auto& m : images) {
                // std::cout <<"...done image loaded in "+std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count())+"ms\n";
                std::cout <<"  Image summary: on("+std::to_string(m.onset)+") off("+std::to_string(m.offset)+") px count("+std::to_string(m.pixels.size())+")\n";
            }
        }
    return true;
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";
        return false;
    }
}



void runMainGameLoop(RGBMatrix* matrix){

    Canvas* canvas = static_cast<Canvas*>(matrix);

    long elapsed=0;
    long stimon=0;
    long stimoff=0;
    auto start = std::chrono::high_resolution_clock::now();
    auto this_time = std::chrono::high_resolution_clock::now();
    canvas->Clear();
    stimon=0;
    stimoff=0;
    size_t current_stimulus_idx = 0;
//    MatrixImage ready_img;
//    std::string jsonstring1 = getStringFromFile("ready_image.json");
//    ready_img.parseInfo(jsonstring1);
//    MatrixImage end_trial_img;
//    std::string jsonstring2 = getStringFromFile("end_trial_image.json");
//    end_trial_img.parseInfo(jsonstring2);


    while(state!=FINISH){
        if(state==NEW_TRIAL){
            this_time = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::microseconds>(this_time-start).count();
            triggers = matrix->AwaitInputChange(.0001); // monitoring the value of input pins within 0.1ms
             // if(triggers&(1<<INPUT_RESPONSE_INTERRUPT_PORT)) std::cout << "\rINPUT_RESPONSE_INTERRUPT_PORT: 1\n";
            if(triggers&(1<<INPUT_TRIAL_RESET_PORT)){ // master communicate a new trial is available and waiting
                state=REQUESTING_IMAGE; // interrupt theimage drawing omly if port of pedal interr from master is set high
            }
        }
        else if(state==REQUESTING_IMAGE){
            std::cout << "> S: REQUESTING IMAGE...\n";
            if(updateImageFromNetwork()){
                triggers = 0;
                matrix->OutputGPIO(triggers);
                state=WAITING_FOR_TRIAL;
                std::cout << "> S: WAITING INPUT_TRIAL_ON_PORT for trial...\n";
            } else {
                if(no_stimuli) { // updating image function returns false either beacuse it was not first time, imageinfo is empty, or there was an error
                    state=NO_STIMULI;
                    std::cout << "> S: NO_STIMULI. Trial should be exectuting. No visual stimuli in this trial for " << MY_NAME<< "\n";
                    std::cout << "  Wait for: " << std::to_string(stim_duration) << "ms\n";
                    start = std::chrono::high_resolution_clock::now();
                }
            }
        }
        else if(state==NO_STIMULI) {
            this_time = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::microseconds>(this_time-start).count();
            if(elapsed>=stim_duration*1000) {
                // if ((triggers & (1 << INPUT_TRIAL_RESET_PORT)) == 0)
                state=NEW_TRIAL;
                std::cout << "\n> S: NEW_TRIAL. Ready...\n";
            } else {
                state=NO_STIMULI;
            }
        }

        else if(state==WAITING_FOR_TRIAL){
            triggers = matrix->AwaitInputChange(.0001);
            if(triggers&(1<<INPUT_TRIAL_ON_PORT)) {
                // std::cout << "\rINPUT_TRIAL_ON_PORT = 1\n";
                triggers = 0;
                matrix->OutputGPIO(triggers);
                state=RUNNING_TRIAL;
                std::cout << "> S: RUNNING TRIAL...\n";
            }
            start = std::chrono::high_resolution_clock::now();
        }
        else if(state==RUNNING_TRIAL){
            // std::cout << "> S: RUNNING TRIAL...\n";
            this_time = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::microseconds>(this_time-start).count();
            triggers = matrix->AwaitInputChange(.0001); // monitoring the value of input pins within 0.1ms
            if(triggers&(1<<INPUT_RESPONSE_INTERRUPT_PORT)) {
                // std::cout << "elapsed: " << std::to_string(elapsed*0.001);
                std::cout << "\rBUTTON INTERRUPT\n";
                triggers = 0;
                current_stimulus_idx = 0;
                canvas->Clear();
                state=NEW_TRIAL;
                start = std::chrono::high_resolution_clock::now();
            }
            else if (current_stimulus_idx < images.size()) { // check for any other stimuli remaining in the list
                MatrixImage& current_image = images[current_stimulus_idx];

                if(elapsed>=current_image.offset*1000){ // offset converted in microseconds (elapsed is too)
                    if(stimoff==0){
                        stimoff = elapsed;
                        canvas->Clear();
                    }
                    std::cout << "Previous on: " << std::to_string(stimon) << "| off: " << std::to_string(stimoff) << "\n\n";
                    canvas->Clear();
                    stimon=0;
                    stimoff=0;

                    current_stimulus_idx ++; // to the next stimulus
                }
                else if(elapsed>=current_image.onset*1000) { // onset converted in microseconds (elapsed is too)
                    if(stimon==0) stimon = elapsed;
                    drawImage(canvas,current_image.pixels);

                }
            } else if(elapsed>=stim_duration*1000){ // if there are no more stimuli and the entrie trial is finshed...
                std::cout << "elapsed: " << std::to_string(elapsed*0.001);
                current_stimulus_idx = 0;
                state = NEW_TRIAL;
                stimon=0; stimoff=0;
                start = std::chrono::high_resolution_clock::now(); // restart the chrono for the ready_image drawing at NEW_TRIal NEXT STATE
                std::cout << "All stimuli executed. TRIAL FINISHED\n\n";
                std::cout << "\n> S: NEW_TRIAL. Ready...\n";
            }

        } /*else if(state==END_TRIAL){
            this_time = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::microseconds>(this_time-start).count();

            if(elapsed>=end_trial_img.offset*1000){ // offset converted in microseconds (elapsed is too)
                if(stimoff==0){
                    stimoff = elapsed;
                    canvas->Clear();
                }
                canvas->Clear();
                stimon=0;
                stimoff=0;
                state=NEW_TRIAL;
                std::cout << "\n> S: NEW_TRIAL. Ready...\n";
                start = std::chrono::high_resolution_clock::now();
            }
            else if(elapsed>=end_trial_img.onset*1000) { // onset converted in microseconds (elapsed is too)
                if(stimon==0)
                    stimon = elapsed;
                drawImage(canvas,end_trial_img.pixels);
            }
        }*/
    }
}


int main(int argc, char *argv[]) {
    if(!readConfig()) return -1;

    std::cout << "Init matrix...";
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm";  // or e.g. "adafruit-hat" could be faster?
    defaults.rows = WIDTH;
    defaults.cols = HEIGHT;
    defaults.chain_length = MATRICES_CHAINED;
    defaults.brightness = 100;
    defaults.pwm_lsb_nanoseconds=50;
    // defaults.pwm_bits=2;
    // defaults.pwm_dither_bits=1;
    // defaults.disable_hardware_pulsing=true;
    // defaults.limit_refresh_rate_hz=100;
    // defaults.row_address_type = 0;
    defaults.show_refresh_rate = false;
    RGBMatrix *matrix = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);

    if (matrix == NULL) return 1;
    uint64_t ports = 1<<INPUT_TRIAL_ON_PORT;
    ports+=1<<INPUT_TRIAL_RESET_PORT;
    ports+=1<<INPUT_RESPONSE_INTERRUPT_PORT;
    matrix->RequestInputs(ports);
    std::cout << "...done.\n";

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    runMainGameLoop(matrix);
    matrix->Clear();
    delete matrix;
    std::cout << ".. done init matrix";
    return 0;
}
