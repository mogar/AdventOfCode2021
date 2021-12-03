
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class SlidingWindow {
private:
    vector<int> window;
    int startidx;
    int endidx;
    int numelems;
public:
    SlidingWindow(int window_size) {
        window.resize(window_size);
        startidx = 0;
        endidx = 0;
        numelems = 0;
    }
    void addMeas(int val) {
        window[endidx] = val;
        
        endidx = (endidx+1) % window.size();
        if (numelems < window.size()) {
            numelems++;
        } else {
            startidx = (startidx+1) % window.size();    
        }
    }
    bool initialized(void) {
        return (numelems == window.size());
    }
    int sumFirstN(int N) {
        if (N > window.size()) {
            return 0;
        }

        int sum = 0;
        for (int i = startidx; i < startidx + N; i++) {
            sum += window[i%window.size()];
        }
        return sum;
    }
    int sumLastN(int N)  {
        if (N > window.size()) {
            return 0;
        }

        int sum = 0;
        for (int i = endidx - 1; i > endidx - 1 - N; i--) {
            sum += window[i%window.size()];
        }
        return sum;
    }

};



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

    int increases = 0;
    SlidingWindow depths(4); // sliding window of 4 depths, allowing for an overlap of 2 between first 3 and last 3
    while (!indata.eof()) {
        int indata_line;
        indata >> indata_line; // get a line of data

        depths.addMeas(indata_line);

        if (depths.initialized()) {
            if (depths.sumLastN(3) > depths.sumFirstN(3)) {
                increases++;
            }
        }

    }

    cout << "there are " << increases << " measurements that are larger than the previous measurement" << endl;

    return 0;
}