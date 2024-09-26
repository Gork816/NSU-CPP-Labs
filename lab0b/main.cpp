#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Wrong amount of arguments." << endl;
        return 1;
    }

    ifstream input(argv[0]);
    ofstream output(argv[1]);

    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }
}