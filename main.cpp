#include <iostream>
#include "string"
#include "booleanFunction.h"
#include <vector>
using namespace std;

int main() {

    booleanFunction* f = new booleanFunction();
    while(!f->Read_Validate_SoP()){};
    f->Generate_Truth_Table();


    



    return 0;
}
