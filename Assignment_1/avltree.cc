#include "Tree/AvlTreeImpl.h"
#include "Utils/Utils.h"

int main(int argc, char **argv) {
    std::string line;
    std::ifstream inputFile;
    std::ofstream outputFile;

    AvlTreeImpl *avlTreeImpl;

    inputFile.open(argv[1]);
    outputFile.open("output_file.txt");

    while(getline(inputFile, line)) {
        std::cout<<line<<std::endl;
        Commands command = Utils::getFunctionName(line);

        if(command == INVALID) {
            std::cout<<"Invalid Command"<<std::endl;
            continue;
        }
        
        std::pair<int, int> params = Utils::getParams(command, line);

        switch (command) {
            case INITIALIZE:
                avlTreeImpl = AvlTreeImpl::initialize();
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

    inputFile.close();
    outputFile.close();

    return 0;
}