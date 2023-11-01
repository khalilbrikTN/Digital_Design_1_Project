
#include <iostream>
#include <string>
#include "booleanFunction.h"
#include <vector>
using namespace std;

int main() {

booleanFunction* f = new booleanFunction();
f->Read_Validate_PoS();
f->Read_Validate_SoP();
f->generate_truth_table();

/*
cout<<f->canonical_sop();
cout<<endl;
cout<<f->canonical_pos();*/







    return 0;
}




