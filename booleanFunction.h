#ifndef DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H
#define DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H

#include <string>


class booleanFunction {

public:
    // Constructor to initialize the class
    booleanFunction();

    // Destructor to clean up resources
    ~booleanFunction();

    // Read and validate a Boolean expression given as Sum of Products (SoP).
    // Returns true if the input is valid, false otherwise.
    bool Read_Validate_SoP(std::string f);

    // Read and validate a Boolean expression given as Product of Sums (PoS).
    // Returns true if the input is valid, false otherwise.
    bool Read_Validate_PoS(std::string f);

    // Generate and return the truth table of the expression as a string.
    std::string Generate_Truth_Table();

    // Generate and return the canonical Sum of Products (SoP) representation as a string.
    std::string Generate_Canonical_SoP();

    // Generate and return the canonical Product of Sums (PoS) representation as a string.
    std::string Generate_Canonical_PoS();

    // Generate and return the Prime Implicants as a string.
    std::string Generate_PI();

    // Generate and return the Essential Prime Implicants as a string.
    std::string Generate_EPI();

    // Print the minterms that are not covered by the essential PIs.
    std::string Generate_uncovered_minterms();

    // Generate and return the minimized Boolean expression of the Boolean function as a string.
    std::string Generate_minimized_expression();

    // Draw the Karnaugh Map (K-Map) showing the solution as a string.
    std::string Generate_K_MAP();

private:
    std::string f_SoP; // Holds the value of the validated Sum of Products (SoP) function.
    std::string f_PoS; // Holds the value of the validated Product of Sums (PoS) function.

};

#endif //DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H
