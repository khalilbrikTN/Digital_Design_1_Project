#include "booleanFunction.h"
#include "iostream"
#include "vector"
#include <algorithm>
#include "cmath"
#include <bitset>
#include <sstream>
#include "fstream"
#include "map"
#include "set"

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
            cout<<"here"<<endl;
            generate_minterms(literals, minterms, "",0); //generate all min_terms based on the literals
            generate_maxterms(literals, maxterms, "",0); //generate all max_terms based on the literals

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
    std::cout << "Enter SoP form!" << std::endl;
    std::cout << "f(";

    for (auto iter_variables = variables.begin(); iter_variables < variables.end() - 1; ++iter_variables) {
        std::cout << *iter_variables << ", ";
    }
    std::cout << variables.back() << ") = "; // This to avoid printing a comma at the end and add a ).

    std::cin >> f; // Read the function from the user.

    if (f.empty()) {
        std::cout << "You entered an empty string! Try again!" << std::endl;
        return false;
    }

    // Split the input string 'f' by the '+' delimiter.
    std::istringstream fStream(f);
    std::string term;
    while (getline(fStream, term, '+')) {
        // Remove all spaces in the term for better matching.
        term.erase(std::remove_if(term.begin(), term.end(), ::isspace), term.end());

        std::set<char> term_vars;  // To hold variables in the current term
        for (size_t i = 0; i < term.size(); ++i) {
            char c = term[i];
            if (isalpha(c)) {
                if (term_vars.find(c) != term_vars.end()) {
                    std::cout << "Variable " << c << " is repeated in term: " << term << std::endl;
                    return false;
                }
                term_vars.insert(c);

                // Check if variable is available
                if (std::find(variables.begin(), variables.end(), c) == variables.end()) {
                    std::cout << "Invalid variable " << c << " detected in term: " << term << std::endl;
                    return false;
                }

                // Check for negation
                if (i + 1 < term.size() && term[i + 1] == '\'') {
                    ++i; // Skip the next character
                }
            } else if (c != '\'') {
                std::cout << "Invalid character " << c << " detected in term: " << term << std::endl;
                return false;
            }
        }
    }
    f_SoP = f;

    std::cout << "Function entered successfully!" << std::endl;
    return true;
}

bool booleanFunction::Read_Validate_PoS() {
    std::string f;
    std::cout << "Enter PoS form!" << std::endl;
    std::cout << "f(";

    for (auto iter_variables = variables.begin(); iter_variables < variables.end() - 1; ++iter_variables) {
        std::cout << *iter_variables << ", ";
    }
    std::cout << variables.back() << ") = "; // This to avoid printing a comma at the end and add a ).

    std::cin >> f; // Read the function from the user.
    if (f.empty()) {
        std::cout << "You entered an empty string! Try again!" << std::endl;
        return false;
    }

    // Split the input string 'f' by the '*' delimiter for maxterms.
    std::istringstream fStream(f);
    std::string term;
    while (getline(fStream, term, '*')) {
        // Remove all spaces in the term for better matching.
        term.erase(std::remove_if(term.begin(), term.end(), ::isspace), term.end());

        std::set<char> term_vars; // To hold variables in the current term
        for (size_t i = 0; i < term.size(); ++i) {
            char c = term[i];
            if (isalpha(c)) {
                if (term_vars.find(c) != term_vars.end()) {
                    std::cout << "Variable " << c << " is repeated in term: " << term << std::endl;
                    return false;
                }
                term_vars.insert(c);

                // Check if variable is available
                if (std::find(variables.begin(), variables.end(), c) == variables.end()) {
                    std::cout << "Invalid variable " << c << " detected in term: " << term << std::endl;
                    return false;
                }

                // Check for negation
                if (i + 1 < term.size() && term[i + 1] == '\'') {
                    ++i; // Skip the next character
                }
            } else if (c != '\'' && c != '+') {
                std::cout << "Invalid character " << c << " detected in term: " << term << std::endl;
                return false;
            }
        }
    }
    f_PoS = f;


    std::cout << "Function entered successfully!" << std::endl;
    return true;
}


string booleanFunction::canonical_SoP() {
    std::string result = "";

    for(int row = 0; row<minterms_bi.size(); row++){
        for(int col = 0; col<minterms_bi.at(0).size()-1; col++){
            if(minterms_bi.at(row).at(col) == 1){result = result + variables.at(col);}
            else{result = result + variables.at(col) + "\'";}
        }
        result = result + "+";
    }

    cout<<result;
    return result;
}


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
    std::string x, x_bar;


    for(iter; iter < variables.end(); iter++){
        x = *iter;
        x_bar = x + "'";


        literals.push_back(x); //push back x
        literals.push_back(x_bar); //push back x'
    };
}

void booleanFunction::generate_minterms(std::vector<std::string> literals, std::vector<std::string>& minterms, std::string current_minterm, int index) {
    // Base case: if the current index equals the size of the literals vector, we've generated a complete minterm
    if (index == literals.size()) {
        minterms.push_back(current_minterm);
        return;
    }

    // Recursive case: append each literal and its complement to the current minterm
    generate_minterms(literals, minterms, (current_minterm + literals.at(index)), index + 2);
    generate_minterms(literals, minterms, (current_minterm + literals.at(index+1)), index + 2);
}


void booleanFunction::generate_maxterms(std::vector<std::string> literals, std::vector<std::string>& maxterms, std::string current_maxterm, int index) {
    // Base case: if the current index equals the size of the literals vector, we've generated a complete maxterm
    if (index == literals.size()) {
        maxterms.push_back(current_maxterm);
        return;
    }

    // Recursive case: append each literal and its complement to the current maxterm
    generate_maxterms(literals, maxterms, current_maxterm.empty() ? literals.at(index) : current_maxterm + "+" + literals.at(index), index + 2);
    generate_maxterms(literals, maxterms, current_maxterm.empty() ? literals.at(index+1) : current_maxterm + "+" + literals.at(index+1), index + 2);
}



void booleanFunction::Generate_Truth_Table() {
    int n = variables.size();
    int rows = pow(2, n);
    std::map<char, bool> var_values;

    std::cout << "Truth Table:\n";
    for (const auto& var : variables) {
        std::cout << var << " ";
    }
    std::cout << "| f\n";

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < n; ++j) {
            bool val = (i >> j) & 1;
            var_values[variables[n - j - 1]] = val;
        }

        for (const auto& var : variables) {
            std::cout << var_values[var] << " ";
        }

        bool result = false;
        std::istringstream fStream(f_SoP);
        std::string term;
        while (getline(fStream, term, '+')) {
            bool term_value = true;
            for (const auto& var : term) {
                if (var == '\'') {
                    continue;
                }

                bool var_value = var_values[var];
                if (*next(term.begin(), std::distance(term.begin(), std::find(term.begin(), term.end(), var))) == '\'') {
                    var_value = !var_value;
                }
                term_value &= var_value;
            }
            result |= term_value;
        }

        std::cout << "| " << result << "\n";
    }
}


