//
// Created by Mohamed Khalil on 10/31/2023.
//

#ifndef DIGITAL_DESIGN_1_PROJECT_TYPEDEFS_H
#define DIGITAL_DESIGN_1_PROJECT_TYPEDEFS_H

#include <vector>

typedef struct {
    char character;
    bool negative;
} AST_SOP_Var;

typedef std::vector<AST_SOP_Var> AST_SOP_Product;
typedef std::vector<AST_SOP_Product> AST_SOP_Vec;

typedef struct {
    char character;
    bool negative;
} AST_POS_Var;

typedef std::vector<AST_POS_Var> AST_POS_Product;
typedef std::vector<AST_POS_Product> AST_POS_Vec;

typedef struct {
    char character;
    bool negative;
} WaveDromVariable;

typedef std::vector<WaveDromVariable> WaveDromProduct;
typedef std::vector<WaveDromProduct> WaveDromSOPVec;


#endif //DIGITAL_DESIGN_1_PROJECT_TYPEDEFS_H
