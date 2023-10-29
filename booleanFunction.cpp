#include "booleanFunction.h"
#include "iostream"
#include "vector"
#include <algorithm>
#include <bitset>
using namespace std;


booleanFunction::booleanFunction() {
    //The constructor function will receive the list of variable names and perform the necessary checks.

    std::cout<<"___Welcome to our Logic Minimizer Application___"<<std::endl;
    std::cout<<"Please enter the variable names that will be use in the function! "<<std::endl;
    std::cout<<"Note: Variable name is a character between 'a' and 'z'."<<std::endl;
    std::cout<<"Enter '/' to quit the entering process. "<<std::endl;


    char var;
    while(var != '/'){
        std::cout<<"variable: ";
        std::cin>>var;
        if(var != '/') {
            if (!(int(var) >= 97 && int(var) <= 122)) { //Check if the character is between 'a' and 'z'.
                std::cout << "Last entered variable is not valid. Please Try again! " << std::endl;
            } else {
                variables.push_back(var); //If valid a character will be added to the vector of characters.
            };
        }
        else{
            std::cout<<"Thank you for entering the variable names!"<<std::endl;
            Generate_literals(); //Once variables are there we can generate literals.
        }
    }

};

booleanFunction::~booleanFunction() {
};



//----------------------------- Here Starts Adam Code ----------------------------------



// Function to check if a minterm is covered by a given prime implicant

bool booleanFunction::isCoveredBy(int minterm, const string& pi) {
    // Convert minterm to binary representation as a string
    bitset<32> mintermBits(minterm); // assuming 32 bits, adjust as needed
    string mintermStr = mintermBits.to_string();
    mintermStr = mintermStr.substr(mintermStr.size() - pi.size());  // Truncate to match the length of pi

    // Compare the minterm string and the prime implicant string
    for (size_t i = 0; i < pi.size(); ++i) {
        if (pi[i] == '-') {
            continue; // Skip 'don't care' condition
        }
        if (pi[i] != mintermStr[i]) {
            return false;  // Mismatch found
        }
    }

    return true;  // No mismatch found
}


// Function to generate and return Essential Prime Implicants

string booleanFunction::Generate_EPI(const vector<int>& minterms, const vector<string>& primeImplicants) {

    vector<string> essentialPrimeImplicants;

    // Loop through each minterm to find Essential Prime Implicants
    for (size_t i = 0; i < minterms.size(); ++i) {
        int count = 0;
        string candidateEPI;

        // Check if this minterm is covered by only one PI
        for (size_t j = 0; j < primeImplicants.size(); ++j) {
            if (isCoveredBy(minterms[i], primeImplicants[j])) {
                count++;
                candidateEPI = primeImplicants[j];
            }
        }

        // If only one PI covers this minterm, it's essential
        if (count == 1) {
            if (find(essentialPrimeImplicants.begin(), essentialPrimeImplicants.end(), candidateEPI)
                == essentialPrimeImplicants.end()) {
                essentialPrimeImplicants.push_back(candidateEPI);
            }
        }
    }

    // Create a string representation of all essential prime implicants
    string epiString = "";
    for (size_t i = 0; i < essentialPrimeImplicants.size(); ++i) {
        epiString += essentialPrimeImplicants[i] + " + ";
    }
    epiString = epiString.substr(0, epiString.length() - 3);  // Remove the last " + "

    cout << "Essential Prime Implicants are: " << epiString << endl;

    return epiString;
}


//----------------------------- Here Ends Adam Code ------------------------------------



bool booleanFunction::Read_Validate_SoP() {

    std::string f;
    std::cout<<"Enter SoP form!"<<std::endl;
    std::cout<<"f(";

    std::vector<char>::iterator iter_variables = variables.begin();
    for(iter_variables; iter_variables < variables.end()-1; iter_variables++){
        std::cout<<*iter_variables<<", ";
    };
    std::cout<<*iter_variables<<") = "; // This to avoid printing a comma at the end and add a ).


    std::cin>>f; //Read the function from the user.
    if(f == ""){
        std::cout<<"You entered an empty string! Try again! "<<std::endl;
    }else{
        std::vector<std::string>::iterator iter_literals = literals.begin();
        for(iter_literals; iter_literals < literals.end()-1; iter_literals++){
            std::cout<<*iter_literals<<", ";
        }
    }


    return true;


};


bool booleanFunction::Read_Validate_PoS() {
    std::string minterm;


};

std::string booleanFunction::Generate_Truth_Table() {
};

std::string booleanFunction::Generate_Canonical_SoP() {
};

std::string booleanFunction::Generate_Canonical_PoS() {
};

std::string booleanFunction::Generate_PI() {
};

std::string booleanFunction::Generate_EPI() {
};

std::string booleanFunction::Generate_uncovered_minterms() {
};

std::string booleanFunction::Generate_minimized_expression() {
};

std::string booleanFunction::Generate_K_MAP() {
};



void booleanFunction::Generate_literals(){

    std::vector<char>::iterator iter = variables.begin();
    for(iter; iter < variables.end()-1; iter++){
        std::cout<<std::to_string(*iter)<<std::endl;
        literals.push_back(std::to_string(*iter)); //push back x
        literals.push_back(std::to_string(*iter) + "'"); //push back x'
    };
}
