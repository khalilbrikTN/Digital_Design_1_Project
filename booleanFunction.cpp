#include "booleanFunction.h"
#include "iostream"
#include "vector"
#include <algorithm>
#include "cmath"
#include <bitset>
#include <sstream>
#include "set"
#include "map"
#include "Typedefs.h"

using namespace std;

//-----------------------------Here Starts Khalil Code----------------------------------

// Constructor to initialize the class
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
        }
    }

};


// Destructor to clean up resources
booleanFunction::~booleanFunction() {
};

//Validate if a function is in SoP
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
    cout<<f_SoP<<endl;
    std::cout << "Function entered successfully!" << std::endl;
    return true;
};

//Validate if a function is in PoS
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
    cout<<f_PoS<<endl;

    std::cout << "Function entered successfully!" << std::endl;
    return true;
}

//Canonical SoP

AST_SOP_Vec booleanFunction::parse_sop(const string& sop) {
    AST_SOP_Vec sop_vector;
    AST_SOP_Product current_product;

    for (int i = 0; i < sop.length(); i++) {

        char current_char = sop[i];
        char next_char = sop[i + 1];
        switch (current_char) {
            // case for lowercase alphabet characters
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                if (next_char == '\'') {
                    current_product.push_back({current_char, true});
                } else {
                    current_product.push_back({current_char, false});
                }
                break;
            case '+':
                sop_vector.push_back(current_product);
                current_product.clear();
                break;
            case ' ':
            case '\'':
                break;
            default:
                cout << "Invalid character in SOP: " << current_char << endl;
                break;
        }
    }
    if (!current_product.empty()) {
        sop_vector.push_back(current_product);
    }
    return sop_vector;
}

std::string booleanFunction::string_from_sop_vec(const AST_SOP_Vec& sop_vector) {
    std::string sop;
    for (int i = 0; i < sop_vector.size(); i++) {
        const AST_SOP_Product& product = sop_vector[i];
        std::string product_string;
        for (int j = 0; j < product.size(); j++) {
            const AST_SOP_Var& variable = product[j];
            product_string += variable.character;
            if (variable.negative) {
                product_string += '\'';
            }
        }
        sop += product_string;
        if (i != sop_vector.size() - 1) {
            sop += " + ";
        }
    }
    return sop;
}

AST_SOP_Vec booleanFunction::canonical_sop_from_sop(const AST_SOP_Vec& sop_vector, const std::vector<char>& variables) {
    AST_SOP_Vec canonical_sop_vector;
    for (const AST_SOP_Product& product : sop_vector) {
        int num_of_missing_variables = variables.size() - product.size();
        for (int i = 0; i < pow(2, num_of_missing_variables); i++) {
            AST_SOP_Product current_product = product;
            for (int j = 0; j < num_of_missing_variables; j++) {
                char variable = variables[product.size() + j];
                if (i & (1 << j)) {
                    current_product.push_back({variable, true});
                } else {
                    current_product.push_back({variable, false});
                }
            }
            canonical_sop_vector.push_back(current_product);
        }
    }
    return canonical_sop_vector;
}

std::string booleanFunction::canonical_sop() {
    AST_SOP_Vec sop_vector = parse_sop(f_SoP);
    AST_SOP_Vec canonical_sop_vector = canonical_sop_from_sop(sop_vector, variables);
    return string_from_sop_vec(canonical_sop_vector);
}
/////


//Canonical PoS
AST_POS_Vec booleanFunction::parse_pos(const std::string& pos) {
    AST_POS_Vec pos_vector;
    AST_POS_Product current_product;

    for (int i = 0; i < pos.length(); i++) {
        char current_char = pos[i];
        char next_char = pos[i + 1];
        switch (current_char) {
            // case for lowercase alphabet characters
            case 'a': case 'b': case 'c': // ... (and so on)
                if (next_char == '\'') {
                    current_product.push_back({current_char, true});
                } else {
                    current_product.push_back({current_char, false});
                }
                break;
            case '(':
                pos_vector.push_back(current_product);
                current_product.clear();
                break;
            case ' ':
            case '\'':
            case ')':
                break;
            default:
                std::cout << "Invalid character in PoS: " << current_char << std::endl;
                break;
        }
    }
    if (!current_product.empty()) {
        pos_vector.push_back(current_product);
    }
    return pos_vector;
}

std::string booleanFunction::string_from_pos_vec(const AST_POS_Vec& pos_vector) {
    std::string pos;
    for (int i = 0; i < pos_vector.size(); i++) {
        const AST_POS_Product& product = pos_vector[i];
        std::string product_string = "(";
        for (int j = 0; j < product.size(); j++) {
            const AST_POS_Var& variable = product[j];
            product_string += variable.character;
            if (variable.negative) {
                product_string += '\'';
            }
            if (j != product.size() - 1) {
                product_string += " + ";
            }
        }
        product_string += ")";
        pos += product_string;
        if (i != pos_vector.size() - 1) {
            pos += " ";
        }
    }
    return pos;
}

AST_POS_Vec booleanFunction::canonical_pos_from_pos(const AST_POS_Vec& pos_vector, const std::vector<char>& variables) {
    AST_POS_Vec canonical_pos_vector;
    for (const AST_POS_Product& product : pos_vector) {
        int num_of_missing_variables = variables.size() - product.size();
        for (int i = 0; i < pow(2, num_of_missing_variables); i++) {
            AST_POS_Product current_product = product;
            for (int j = 0; j < num_of_missing_variables; j++) {
                char variable = variables[product.size() + j];
                if (i & (1 << j)) {
                    current_product.push_back({variable, true});
                } else {
                    current_product.push_back({variable, false});
                }
            }
            canonical_pos_vector.push_back(current_product);
        }
    }
    return canonical_pos_vector;
}

std::string booleanFunction::canonical_pos() {
    AST_POS_Vec pos_vector = parse_pos(f_PoS);
    AST_POS_Vec canonical_pos_vector = canonical_pos_from_pos(pos_vector, variables);
    return string_from_pos_vec(canonical_pos_vector);
}
/////



// Function to generate and print the truth table

bool booleanFunction::evaluate_sop(const std::string& sop, const std::map<char, bool>& var_values) {
    std::istringstream iss(sop);
    std::string term;
    while (iss >> term) {
        bool term_result = true;
        for (const char& var : term) {
            if (var == '\'') continue; // skip negation
            bool value = false; // Default value
            auto it = var_values.find(tolower(var));
            if (it != var_values.end()) {
                value = it->second;
            }
            term_result &= value;
            if (isupper(var)) term_result = !term_result;
        }
        if (term_result) return true;
    }
    return false;
}


void booleanFunction::generate_truth_table() {
    string sop = canonical_sop();
    int num_vars = variables.size();
    int num_rows = std::pow(2, num_vars);

    // Print header
    for (const char& var : variables) {
        std::cout << var << " ";
    }
    std::cout << "| f\n";

    // Generate truth table
    for (int i = 0; i < num_rows; ++i) {
        std::map<char, bool> var_values;
        for (int j = 0; j < num_vars; ++j) {
            bool val = (i >> j) & 1;
            std::cout << val << " ";
            var_values[variables[j]] = val;
        }

        // Evaluate and print function output
        bool output = evaluate_sop(sop, var_values);
        std::cout << "| " << output << "\n";
    }
}












//-----------------------------Here Ends Khalil Code----------------------------------





//----------------------------- Here Starts Adam Code ----------------------------------


// Function to count the number of '1' characters in a string
int countOnes(const string& s) {
    return count(s.begin(), s.end(), '1');
}

// Function to generate the Prime Implicants

vector<string> booleanFunction::GenerateAndPrintPIs(const vector<int>& minterms) {
    // Define a Term structure to represent binary representation and original minterms
    struct Term {
        string binary;
        set<int> originalMinterms;
    };

    // Convert all minterms to their 32-bit binary representation and initialize them as the current terms
    vector<Term> currentTerms;
    for (int m : minterms) {
        currentTerms.push_back({bitset<32>(m).to_string(), {m}});
    }

    // Set to keep track of prime implicants
    set<string> primeImplicants;

    // Loop until no more combinations are found
    while (true) {
        vector<Term> nextTerms; // Terms for the next iteration
        set<string> used;      // Track combined terms

        // Try to combine terms
        for (int i = 0; i < currentTerms.size(); ++i) {
            bool combined = false; // Track if a term was combined

            for (int j = 0; j < currentTerms.size(); ++j) {
                if (i == j) continue;

                int diffCount = 0;    // Count of differing bits
                int diffIndex = -1;   // Index of the differing bit

                // Compare bits of terms
                for (int k = 0; k < variables.size(); k++) {
                    if (currentTerms[i].binary[32 - k - 1] != currentTerms[j].binary[32 - k - 1]) {
                        diffCount++;
                        diffIndex = k;
                    }
                }

                // If only one bit differs, combine the terms
                if (diffCount == 1) {
                    combined = true;
                    used.insert(currentTerms[i].binary);
                    used.insert(currentTerms[j].binary);
                    string newBinary = currentTerms[i].binary;
                    newBinary[32 - diffIndex - 1] = '-';
                    set<int> combinedMinterms = currentTerms[i].originalMinterms;
                    combinedMinterms.insert(currentTerms[j].originalMinterms.begin(), currentTerms[j].originalMinterms.end());
                    nextTerms.push_back({newBinary, combinedMinterms});
                }
            }

            // If a term was not combined and not used before, it's a prime implicant
            if (!combined && used.find(currentTerms[i].binary) == used.end()) {
                primeImplicants.insert(currentTerms[i].binary);
            }
        }

        // If no combinations are found, break out of the loop
        if (nextTerms.empty()) {
            break;
        }

        currentTerms = nextTerms; // Update current terms for next iteration
    }

    // Extract the relevant bits from prime implicants and store in a vector
    vector<string> resultImplicants;
    for (const string& pi : primeImplicants) {
        resultImplicants.push_back(pi.substr(32 - variables.size()));
    }

    for (const string& pi : resultImplicants) {
        cout << "Prime Implicant: " << pi << endl;
    }


    return resultImplicants;
}

// Function to check if a minterm is covered by a prime implicant
bool booleanFunction::isCoveredBy(int minterm, const string& pi) {
    // Convert minterm to 32-bit binary representation
    bitset<32> mintermBits(minterm);
    string mintermStr = mintermBits.to_string();
    mintermStr = mintermStr.substr(mintermStr.size() - pi.size());

    // Compare minterm with prime implicant
    for (int i = 0; i < pi.size(); i++) {
        if (pi[i] == '-') continue; // Ignore don't care conditions
        if (pi[i] != mintermStr[i]) return false;
    }

    return true; // Minterm is covered by the prime implicant
}

// Function to generate and return Essential Prime Implicants in Boolean expression format
string booleanFunction::Generate_EPI(const vector<int>& minterms, const vector<string>& primeImplicants) {
    vector<string> essentialPrimeImplicants;

    // Identify essential prime implicants
    for (int i = 0; i < minterms.size(); i++) {
        int count = 0;          // Track number of prime implicants that cover a minterm
        string potentialEPI;   // Store potential essential prime implicant

        // Check coverage of minterm by prime implicants
        for (int j = 0; j < primeImplicants.size(); j++) {
            if (isCoveredBy(minterms[i], primeImplicants[j])) {
                count++;
                potentialEPI = primeImplicants[j];
            }
        }

        // If only one prime implicant covers, it's essential
        if (count == 1 && find(essentialPrimeImplicants.begin(), essentialPrimeImplicants.end(), potentialEPI) == essentialPrimeImplicants.end()) {
            essentialPrimeImplicants.push_back(potentialEPI);
        }
    }

    // Convert essential prime implicants to Boolean expression format
    string epiExpression = "";
    for (int epiIndex = 0; epiIndex < essentialPrimeImplicants.size(); epiIndex++) {
        string epi = essentialPrimeImplicants[epiIndex];
        string term = "";

        for (int i = 0; i < epi.size(); ++i) {
            if (epi[i] == '1') term += string(1, variables[i]) + " . "; // AND operation
            else if (epi[i] == '0') term += string(1, variables[i]) + "'" + " . "; // Negation and AND
        }

        if (!term.empty()) {
            term = term.substr(0, term.length() - 3);
            epiExpression += "(" + term + ") + "; // OR operation between terms
        }
    }

    if (!epiExpression.empty()) epiExpression = epiExpression.substr(0, epiExpression.length() - 3);

    cout << "Essential Prime Implicants are: " << epiExpression << endl;
    return epiExpression;
}

vector<int> booleanFunction::getMintermNumbers() {
    vector<int> minterms;

    // Split the f_SoP by '+' delimiter
    istringstream fStream(f_SoP);
    string term;
    while (getline(fStream, term, '+')) {
        // Convert term to its binary representation
        std::string binStr;
        for (char var : variables) {
            size_t pos = term.find(var);
            if (pos == string::npos) {
                // Variable not found
                binStr.push_back('0');
            } else if (pos + 1 < term.size() && term[pos + 1] == '\'') {
                // Negated variable
                binStr.push_back('0');
            } else {
                // Non-negated variable
                binStr.push_back('1');
            }
        }

        // Convert binary string to integer and add to minterms list
        minterms.push_back(stoi(binStr, nullptr, 2));
    }

    return minterms;
}

// Function to display minterms not covered by essential prime implicants
void booleanFunction::Print_Uncovered_Minterms(const vector<int>& minterms, const vector<string>& primeImplicants) {
    vector<int> uncoveredMinterms; // Track uncovered minterms

    for (int i = 0; i < minterms.size(); i++) {
        bool isCovered = false;  // Track coverage of minterm

        for (int j = 0; j < primeImplicants.size(); j++) {
            if (isCoveredBy(minterms[i], primeImplicants[j])) {
                isCovered = true;
                break;
            }
        }

        if (!isCovered) uncoveredMinterms.push_back(minterms[i]);
    }

    // Display the uncovered minterms
    if (uncoveredMinterms.empty()) {
        cout << "There are no uncovered minterms." << endl;
    } else {
        // Display the uncovered minterms
        cout << "Minterms not covered by Essential Prime Implicants are: ";
        for (int minterm : uncoveredMinterms) {
            cout << minterm << " ";
        }
        cout << endl;
    }
}

/* The following code is not yet functional
 * It was intended to 1) generate minterms from the PoS function
 * 2) Convert from SoP to PoS in case the first method did not work
 *
std::vector<int> booleanFunction::PoS_to_Minterms() {
    int totalVariables = variables.size();
    int totalMinterms = pow(2, totalVariables);

    // Split the PoS string by '*' to get the terms
    std::istringstream fStream(f_PoS);
    std::string term;
    std::set<int> sopMinterms;
    while (getline(fStream, term, '*')) {
        // Convert each term to its minterm form
        int mintermValue = 0;
        int bitPosition = 0;
        for (size_t i = 0; i < term.size(); ++i) {
            char c = term[i];
            if (isalpha(c)) {
                // If the variable is NOT negated, then set the bit to 0
                if (i + 1 >= term.size() || term[i + 1] != '\'') {
                    mintermValue += pow(2, totalVariables - 1 - bitPosition);
                }
                bitPosition++;
            }
        }
        sopMinterms.insert(mintermValue);
    }

    // Find the minterms NOT in the SoP to get the minterms of the PoS
    std::vector<int> result;
    for (int i = 0; i < totalMinterms; ++i) {
        if (sopMinterms.find(i) == sopMinterms.end()) {
            result.push_back(i);
        }
    }

    return result;
}

std::string booleanFunction::ConvertPoSToSoP() {
    std::string sopFunction = ""; // Initialize the SoP function as an empty string

    // Split the PoS input string 'f_PoS' by the '*' delimiter for maxterms.
    std::istringstream fStream(f_PoS);
    std::string term;
    bool firstTerm = true; // To handle adding '+' between terms

    while (getline(fStream, term, '*')) {
        // Remove all spaces in the term for better matching.
        term.erase(std::remove_if(term.begin(), term.end(), ::isspace), term.end());

        std::set<char> term_vars; // To hold variables in the current term
        bool firstVar = true; // To handle adding '.' between variables

        for (size_t i = 0; i < term.size(); ++i) {
            char c = term[i];

            if (isalpha(c)) {
                if (!firstVar) {
                    sopFunction += '.'; // Add '.' between variables
                }
                sopFunction += c;

                // Check for negation
                if (i + 1 < term.size() && term[i + 1] == '\'') {
                    sopFunction += '\''; // Add '\'' for negation
                    ++i; // Skip the next character
                }

                term_vars.insert(c);
                firstVar = false;
            } else {
                std::cout << "Invalid character " << c << " detected in term: " << term << std::endl;
                return ""; // Return an empty string for an invalid term
            }
        }

        if (!term_vars.empty()) {
            if (!firstTerm) {
                sopFunction += '+'; // Add '+' between terms
            }
            firstTerm = false;
        }
    }

    return sopFunction;
}
*/
//----------------------------- Here Ends Adam Code ------------------------------------








void booleanFunction::generateKmap(const std::vector<std::string>& minterms, const std::vector<char>& variables) {
    // Determine the number of variables (n) from the variable vector size
    int n = variables.size();

    // Calculate the number of cells in the K-map
    int numCells = pow(2, n);

    // Create a 2D K-map array with all cells initialized to 0
    std::vector<std::vector<int>> kmap(numCells, std::vector<int>(numCells, 0));

    // Fill in the K-map with 1s for the specified minterms
    for (const std::string& minterm : minterms) {
        int mintermValue = std::stoi(minterm);

        // Convert the minterm to binary representation
        std::vector<int> binaryRepresentation(n, 0);
        int temp = mintermValue;

        for (int i = n - 1; i >= 0; i--) {
            binaryRepresentation[i] = temp % 2;
            temp /= 2;
        }

        // Determine the row and column indices in the K-map
        int row = 0;
        int col = 0;
        for (int i = 0; i < n; i++) {
            row = row * 2 + binaryRepresentation[i];
            col = col * 2 + (binaryRepresentation[i] == 0 ? 1 : 0); // Invert 0 to 1 and vice versa
        }

        // Mark the cell with 1 to indicate the minterm
        kmap[row][col] = 1;
    }

    // Print the K-map
    for (int i = 0; i < numCells; i++) {
        for (int j = 0; j < numCells; j++) {
            std::cout << kmap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



/*string output_final_html_from_sop(string sop) {

    WaveDromSOPVec sop_vector;

    string html_header = R"""(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>WaveDrom Minimized Circuit Display</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/skins/default.js" type="text/javascript"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/wavedrom.min.js" type="text/javascript"></script>

</head>
<body onload="WaveDrom.ProcessAll()">

<script type="WaveDrom">
{ assign: [
  ["out",
    ["|",
    )""";

    string html_footer = R"""(
    ]
  ]
]}
</script>

</body>
</html>
    )""";

    string html_wavedrom_sop = html_header;
    sop_vector = parse_sop(sop);

    for (int i = 0; i < sop_vector.size(); i++) {
        WaveDromProduct current_product = sop_vector[i];
        html_wavedrom_sop += "[\"&\", ";
        for (int j = 0; j < current_product.size(); j++) {
            WaveDromVariable current_variable = current_product[j];
            if (current_variable.negative) {
                html_wavedrom_sop += "[\"~\", \"" + string(1, current_variable.character) + "\"], ";
            } else {
                html_wavedrom_sop += "\"" + string(1, current_variable.character) + "\", ";
            }
        }
        html_wavedrom_sop += "],\n";
    }

    html_wavedrom_sop += html_footer;
    return html_wavedrom_sop;
}*/

