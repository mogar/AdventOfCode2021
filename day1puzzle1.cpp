
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

void printUsage(char ** argv) {
    cout << "usage: " << endl;
    coud << "\t" << argv[0] << "-f inputpath.txt" << endl;
}

char * getInputPath(char ** begin, char ** end) {
    char ** p = std::find(begin, end, "-f");
    // increment past the -f string to get filepath
    if (p != end && ++p != end) {
        return *p;
    }
    return nullptr;
}

int main(int argc, char ** argv) {

    char * filepath = getInputPath(argv, argv + argc);
    if (filepath == nullptr) {
        printUsage(argv);
        return -1;
    }

    ifstream indata;
    indata.open(filepath);

    if (!indata.is_open()) {
        cout << "ERROR: couldn't open file " << filepath << endl;
        return -1;
    }

    while (!indata.eof()) {
        string indata_line;
        indata >> indata_line; // get a line of data

        // TODO: stuff
    }

}