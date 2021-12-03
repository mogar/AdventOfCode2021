
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

void printUsage(char ** argv) {
    cout << "usage: " << endl;
    cout << "\t" << argv[0] << " -f inputpath.txt" << endl;
}

char * getInputPath(char ** begin, char ** end) {
    const string option = "-f";
    char ** p = find(begin, end, option);

    // increment past the -f string to get filepath
    if (p != end && ++p != end) {
        return *p;
    }
    return nullptr;
}

int main(int argc, char * argv[]) {

    char * filepath = getInputPath(argv, argv + argc);
    
    cout << "input: " << filepath << endl;
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

    int increases = -1; // set to -1 so that our first value will bring us up to zero
    int last_depth = -1; // choose a depth that's for sure less than the first depth
    while (!indata.eof()) {
        int indata_line;
        indata >> indata_line; // get a line of data

        if (indata_line > last_depth) {
            increases++;
        }
        last_depth = indata_line;
    }

    cout << "there are " << increases << " measurements that are larger than the previous measurement" << endl;

    return 0;
}