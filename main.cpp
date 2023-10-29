#include <iostream>
#include "string"
#include "booleanFunction.h"
#include <vector>
using namespace std;

int main() {
    /*booleanFunction* f = new booleanFunction();
    f->Read_Validate_SoP();
    f->Read_Validate_PoS();*/

    std::vector<int> minterms = {1, 3, 4, 6, 7, 8, 9, 11};
    std::vector<std::string> primeImplicants = {"-0-", "--1", "1--", "-11"};


    booleanFunction bf;

    string result = bf.Generate_EPI(minterms, primeImplicants);

    cout << "Resulting Essential Prime Implicants: " << result << std::endl;

    return 0;
}
