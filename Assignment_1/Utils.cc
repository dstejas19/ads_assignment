#include "Utils.h"

Commands Utils :: getFunctionName(std::string line) {
    if(line[0] == 'D') {
        return DELETE;
    }

    if(line[0] == 'I') {
        if(line[2] == 'I') {
            return INITIALISE;
        }

        return INSERT;
    }

    for(int i=7;i<line.length();++i) {
        if(line[i] == ',') {
            return SEARCH_RANGE;
        }
    }

    return SEARCH;
}

std::pair<int, int> Utils :: getParams(Commands command, std::string line) {
    std::pair<int, int> params;

    if(command == SEARCH_RANGE) {
        std::string temp = "";

        for(int i=7;i<line.length()-1;++i) {
            if(line[i] == ',') {
                std::cout<<temp<<std::endl;
                params.first = stoi(temp);
                temp = "";
            }
            else {
                temp += line[i];
            }
        }
        
        std::cout<<temp<<std::endl;
        params.second = stoi(temp);
    }
    else if(command != INITIALISE) {
        std::string temp = "";

        for(int i=7;i<line.length()-1;++i) {
            temp += line[i];
        }

        std::cout<<temp<<std::endl;
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
        outputFile<<keys[0]->data;

        for(int i=1;i<keys.size();++i) {
            outputFile<<"," + keys[0]->data;
        }

        outputFile<<std::endl;
    }
}