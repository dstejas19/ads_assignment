#include "AvlTreeImpl.h"
#include "Utils.h"

int main(int argc, char **argv) {
    std::string line;
    std::ifstream inputFile;
    std::ofstream outputFile;

    AvlTreeHelper *avlTreeHelper = new AvlTreeHelper();
    AvlTreeImpl *avlTreeImpl;

    inputFile.open(argv[1]);
    outputFile.open("output_file.txt");

    while(getline(inputFile, line)) {
        std::cout<<line<<std::endl;
        Commands command = Utils::getFunctionName(line);
        std::pair<int, int> params = Utils::getParams(command, line);

        switch (command) {
            case INITIALISE:
                avlTreeImpl = AvlTreeImpl::initialise(avlTreeHelper);
                break;
            
            case INSERT:
                avlTreeImpl->insert(params.first);
                break;

            case DELETE:
                avlTreeImpl->remove(params.first);
                break;

            case SEARCH:
                Utils::writeToFile(outputFile, avlTreeImpl->search(params.first));
                break;

            case SEARCH_RANGE:
                Utils::writeToFile(outputFile, avlTreeImpl->search(params.first, params.second));
                break;
        }
    }
}