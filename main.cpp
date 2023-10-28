#include <iostream>
#include "string"
#include "booleanFunction.h"

using namespace std;

int main() {
    booleanFunction* f = new booleanFunction();
    f->Read_Validate_SoP();
    f->Read_Validate_PoS();

    return 0;
}
