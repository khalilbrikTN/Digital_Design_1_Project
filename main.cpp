#include <iostream>
#include "string"
#include "booleanFunction.h"
#include <vector>
using namespace std;

int main() {
    /*booleanFunction* f = new booleanFunction();
    f->Read_Validate_SoP();
    f->Read_Validate_PoS();*/

    /*std::vector<int> minterms = {1, 3, 4, 6, 7, 8, 9, 11};
    std::vector<std::string> primeImplicants = {"-0-", "--1", "1--", "-11"};

    std::vector<int> minterms = {0, 2, 3, 8, 10, 16, 17, 18, 19, 21, 24, 26};
    std::vector<std::string> primeImplicants = {"--0-0", "-001-", "100--", "10-01"};

    std::vector<int> minterms = {10, 18, 26, 40, 41, 42, 48, 49, 50, 52, 53, 56, 57, 60, 61};
    std::vector<std::string> primeImplicants = {"11--0-", "1-100-", "-01010", "-10010", "0-1010"};

    vector<int> minterms = {1, 2, 4, 8, 10, 15};
    vector<string> primeImplicants = {"10--", "--01"};*/

    vector<int> minterms = {5, 35, 60, 68, 90, 127, 110};
    vector<string> primeImplicants = {"00----1", "10--1--", "11----0"};

    booleanFunction bf;

    string result = bf.Generate_EPI(minterms, primeImplicants);

    bf.Print_Uncovered_Minterms(minterms, primeImplicants);

    cout << "Resulting Essential Prime Implicants: " << result << std::endl;

    return 0;
}
