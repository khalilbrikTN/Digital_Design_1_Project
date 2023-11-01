#ifndef DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H
#define DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H

#include <string>
#include <vector>
#include "map"
#include "Typedefs.h"

using namespace std;

//-----------------------------Here Starts Khalil Code----------------------------------

class booleanFunction {

public:
    // Constructor to initialize the class
    booleanFunction();

    // Destructor to clean up resources
    ~booleanFunction();

    // Read and validate a Boolean expression given as Sum of Products (SoP).
    // Returns true if the input is valid, false otherwise.
    bool Read_Validate_SoP();

    // Read and validate a Boolean expression given as Product of Sums (PoS).
    // Returns true if the input is valid, false otherwise.
    bool Read_Validate_PoS();

    // Generate and return the canonical Sum of Products (SoP) representation as a string.
    std::string Generate_Canonical_SoP();

    // Generate and return the canonical Product of Sums (PoS) representation as a string.
    std::string Generate_Canonical_PoS();

    //Print the truth table of the function
    bool evaluate_sop(const std::string& sop, const std::map<char, bool>& var_values);
    void generate_truth_table();

    vector<string> GenerateAndPrintPIs(const std::vector<int>& minterms);

    bool isCoveredBy(int minterm, const std::string& pi);

    std::string Generate_EPI(const std::vector<int>& minterms, const std::vector<std::string>& primeImplicants);

    void Print_Uncovered_Minterms(const std::vector<int>& minterms, const std::vector<std::string>& primeImplicants);




    // Print the minterms that are not covered by the essential PIs.
    std::string Generate_uncovered_minterms();

    // Generate and return the minimized Boolean expression of the Boolean function as a string.
    std::string Generate_minimized_expression();

    // Draw the Karnaugh Map (K-Map) showing the solution as a string.
    std::string generateKmap();


    //The following functions are helper functions for the previous main functions.

    //This function will generate all possible literals and store them in the literals vector.
     bool evaluateMinterm(const std::string& minterm, const std::vector<bool>& values, const std::vector<char>& variables);
    void nonCanonicalSoPToMinterms();

    void generateKmap(const std::vector<std::string>& minterms, const std::vector<char>& variables);

    //Canonical SoP
    AST_SOP_Vec parse_sop(const string& sop);
    std::string string_from_sop_vec(const AST_SOP_Vec& sop_vector);
    AST_SOP_Vec canonical_sop_from_sop(const AST_SOP_Vec& sop_vector, const std::vector<char>& variables);
    std::string canonical_sop();

    //Canonical PoS
    AST_POS_Vec parse_pos(const std::string& pos);
    std::string string_from_pos_vec(const AST_POS_Vec& pos_vector);
    AST_POS_Vec canonical_pos_from_pos(const AST_POS_Vec& pos_vector, const std::vector<char>& variables);
    std::string canonical_pos();



    //Draw Circuit
    string output_final_html_from_sop(string sop);


    vector<int> getMintermNumbers();



        private:
    std::string f_SoP; // Holds the value of the validated Sum of Products (SoP) function.
    std::string f_PoS; // Holds the value of the validated Product of Sums (PoS) function.
    std::vector<char> variables; // Holds the names of the characters.
    std::vector<vector<int>> truth_table;


};


//-----Khalil Code //--

#endif //DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H