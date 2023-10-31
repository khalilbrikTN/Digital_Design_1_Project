#ifndef DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H
#define DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H

#include <string>
#include <vector>

class booleanFunction {

public:
    // Default constructor
    booleanFunction();

    // Destructor
    ~booleanFunction();

    //----------------------------- Here Starts Adam Code ----------------------------------

    // Generate Essential Prime Implicants based on the given minterms and prime implicants.
    std::string Generate_EPI(const std::vector<int>& minterms, const std::vector<std::string>& primeImplicants);

    // Check if a minterm is covered by a given prime implicant.
    bool isCoveredBy(int minterm, const std::string& pi);

    //----------------------------- Here Ends Adam Code ------------------------------------

    // Validates and reads a Sum of Products (SoP) expression.
    bool Read_Validate_SoP();

    // Validates and reads a Product of Sums (PoS) expression.
    bool Read_Validate_PoS();

    // Generate and print the truth table for the given expression.
    void Generate_Truth_Table();

    // Generate canonical Sum of Products (SoP) representation.
    std::string canonical_SoP();

    // Generate canonical Product of Sums (PoS) representation.
    std::string Generate_Canonical_PoS();

    // Generate Prime Implicants for the function.
    std::vector<std::string> GenerateAndPrintPIs(std::vector<int>& minterms);

    // Generate Essential Prime Implicants for the function.
    std::string Generate_EPI();

    // Generate minterms not covered by essential prime implicants.
    std::string Print_Uncovered_Minterms();

    // Generate minimized expression.
    std::string Generate_minimized_expression();

    // Generate Karnaugh Map (K-Map).
    std::string Generate_K_MAP();

    void Print_Uncovered_Minterms(std::vector<int>& minterms,std::vector<std::string>& primeImplicants);

    // Helper functions for generating literals, minterms, and maxterms.
    void Generate_literals();
    void generate_minterms(std::vector<std::string> literals, std::vector<std::string>& minterms, std::string current_minterm, int index);
    void generate_maxterms(std::vector<std::string> literals, std::vector<std::string>& maxterms, std::string current_maxterm, int index);


    WaveDromSOPVec parse_sop(const string& sop);
    string output_final_html_from_sop(string sop);



private:
    // Holds the validated Sum of Products (SoP) function.
    std::string f_SoP;

    // Holds the validated Product of Sums (PoS) function.
    std::string f_PoS;

    // Holds the names of the variables.
    std::vector<char> variables;

    // Holds all possible literals based on the entered variables.
    std::vector<std::string> literals;

    // Holds all possible minterms.
    std::vector<std::string> minterms;

    // Holds all possible maxterms.
    std::vector<std::string> maxterms;

    // Holds binary representation of minterms.
    std::vector<std::vector<int>> minterms_bi;

    // Holds binary representation of maxterms.
    std::vector<std::vector<int>> maxterms_bi;
};

#endif //DIGITAL_DESIGN_1_PROJECT_BOOLEANFUNCTION_H
