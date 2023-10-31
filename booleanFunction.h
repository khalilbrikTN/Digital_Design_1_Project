#ifndef DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H
#define DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H

#include <string>
#include <vector>

class booleanFunction {

public:
    // Constructor to initialize the class
    booleanFunction();

    // Destructor to clean up resources
    ~booleanFunction();

    //----------------------------- Here Starts Adam Code ----------------------------------

    std::string Generate_EPI(const std::vector<int>& minterms, const std::vector<std::string>& primeImplicants);

    bool isCoveredBy(int minterm, const std::string& pi);

    void Print_Uncovered_Minterms(const std::vector<int>& minterms, const std::vector<std::string>& primeImplicants);


        //----------------------------- Here Ends Adam Code ------------------------------------

    // Read and validate a Boolean expression given as Sum of Products (SoP).
    // Returns true if the input is valid, false otherwise.
    bool Read_Validate_SoP();

    // Read and validate a Boolean expression given as Product of Sums (PoS).
    // Returns true if the input is valid, false otherwise.
    bool Read_Validate_PoS();

    // Generate and return the truth table of the expression as a string.
    std::string Generate_Truth_Table();

    // Generate and return the canonical Sum of Products (SoP) representation as a string.
    std::string Generate_Canonical_SoP();

    // Generate and return the canonical Product of Sums (PoS) representation as a string.
    std::string Generate_Canonical_PoS();

    // Generate and return the Prime Implicants as a string.
    std::string Generate_PI();

    // Print the minterms that are not covered by the essential PIs.
    std::string Generate_uncovered_minterms();

    // Generate and return the minimized Boolean expression of the Boolean function as a string.
    std::string Generate_minimized_expression();

    // Draw the Karnaugh Map (K-Map) showing the solution as a string.
    std::string Generate_K_MAP();


    //The following functions are helper functions for the previous main functions.

    //This function will generate all possible literals and store them in the literals vector.
    void Generate_literals();


private:
    std::string f_SoP; // Holds the value of the validated Sum of Products (SoP) function.
    std::string f_PoS; // Holds the value of the validated Product of Sums (PoS) function.
    std::vector<char> variables; // Holds the names of the characters.
    std::vector<std::string> literals; //Holds all possible literals based on the entered variables.

};

#endif //DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H
