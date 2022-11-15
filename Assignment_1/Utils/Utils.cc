#include "Utils.h"

// extract function name from the string
Commands Utils :: getFunctionName(std::string line) {
    std::string func = line.substr(0, 6);

    if(func == "Insert") {
        return INSERT;
    }
    else if(func == "Delete") {
        return DELETE;
    }
    else if(func == "Search") {
        for(int i=7;i<line.length();++i) {
            if(line[i] == ',') {
                return SEARCH_RANGE;
            }
        }

        return SEARCH;    
    }

    func = line.substr(0, 10);
    
    if(func == "Initialize") {
        return INITIALIZE;
    }

    return INVALID;
}

// extract parameters from the string
std::pair<int, int> Utils :: getParams(Commands command, std::string line) {
    std::pair<int, int> params;
    if(command == SEARCH_RANGE) {
        std::string temp = "";

        for(int i=7;i<line.length()-1;++i) {
            if(line[i] == ',') {
                params.first = stoi(temp);
                temp = "";
            }
            else {
                temp += line[i];
            }
        }
        
        params.second = stoi(temp);
    }
    else if(command != INITIALIZE) {
        std::string temp = "";

        for(int i=7;i<line.length()-1;++i) {
            temp += line[i];
        }

        params.first = stoi(temp);
    }

    return params;
}

void Utils :: writeToFile(std::ofstream &outputFile, const Key* key) {
    if(!key) {
        outputFile<<"Null"<<std::endl;
    }
    else {
        outputFile<<key->data<<std::endl;
    }
}

void Utils :: writeToFile(std::ofstream &outputFile, const std::vector<const Key*> keys) {
    if(keys.empty()) {
        outputFile<<"Null"<<std::endl;
    }
    else {
        std::string outputString = std::to_string(keys[0]->data);

        for(int i=1;i<keys.size();++i) {
            outputString += "," + std::to_string(keys[i]->data);
        }

        outputFile<<outputString<<std::endl;
    }
}