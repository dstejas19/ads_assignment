#define UTILS_H

#include "../Enums/Commands.h"
#include "Node/Key.h"
#include "fstream"

#include <string>
#include <vector>
#include <iostream>

class Utils {
public:
    static Commands getFunctionName(std::string line);
    static std::pair<int, int> getParams(Commands command, std::string line);
    static void writeToFile(std::ofstream &outputFile, const Key* key);
    static void writeToFile(std::ofstream &outputFile, const std::vector<const Key*> key);
};