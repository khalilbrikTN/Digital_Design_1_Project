#include <iostream>
#include "string"
#include "booleanFunction.h"
#include <vector>
using namespace std;

int main() {

    cout<<"Welcome to Our Logic Optimizer Program"<<endl;

    cout<<"Enter the number of Functions you want to optimise: ";
    int num;
    cin>>num;



    for(int i = 0; i<num; i++){
        booleanFunction* f = new booleanFunction();
        cout<<"In Our Program you have the choice to enter SoP or PoS: \n 1.SoP \n 2.PoS\n"<<endl;
        int choice;
        cout<<"Enter choice: ";
        cin>>choice;
        switch (choice) {
            case 1:
                f->Read_Validate_SoP();
                break;
            case 2:
                f->Read_Validate_PoS();
                break;
            default:
                break;

        }
        f->Generate_Truth_Table();
        f->Generate_Canonical_PoS();


    }






    return 0;
}
