#include "basic.hpp"
#include "geneCode.hpp"
#include "parserASTLY.hpp"

#include <algorithm>

using std::cout;
using std::endl;
using std::ios;
using std::ios_base;
using std::ofstream;
using std::string;
using std::to_string;

// this version is more faster. 0.000232973s
bool getVariablesFromExpr(const ast_ptr &expr, vector<string> &vars)
{
    if (expr == nullptr)
    {
        fprintf(stderr, "ERROR: getVariablesFromExpr: the input is nullptr\n");
        exit(EXIT_FAILURE);
    }
    auto type = expr->type();
    if (type == "Number")
    {
        return true;
    }
    else if (type == "Variable")
    {
        VariableExprAST *varPtr = dynamic_cast<VariableExprAST *>(expr.get());
        auto var = varPtr->getVariable();
        vars.push_back(var);
        return true;
    }
    else if (type == "Call")
    {
        CallExprAST *callPtr = dynamic_cast<CallExprAST *>(expr.get());
        auto &args = callPtr->getArgs();
        for (auto &arg : args)
        {
            if (!getVariablesFromExpr(arg, vars))
            {
                fprintf(stderr, "ERROR: getVariablesFromExpr: run failed\n");
                exit(EXIT_FAILURE);
            }
        }
        std::sort(vars.begin(), vars.end()); // sort to unique the parameters queue
        vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
        return true;
    }
    if (type != "Binary")
    {
        fprintf(stderr, "ERROR: getVariablesFromExpr: type %s is wrong\n", type.c_str());
        exit(EXIT_FAILURE);
    }
    BinaryExprAST *binaryPtr = dynamic_cast<BinaryExprAST *>(expr.get());
    auto &lhs = binaryPtr->getLHS();
    auto &rhs = binaryPtr->getRHS();
    getVariablesFromExpr(lhs, vars);
    getVariablesFromExpr(rhs, vars);
    std::sort(vars.begin(), vars.end()); // sort to unique the parameters queue
    vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
    return true;
}

int geneMpfrCode(const string exprStr, vector<string> vars)
{
    int status = 0;
    ofstream file_clean("./detectModule/src/getresult.cpp", ios_base::out);
    ofstream ofs("./detectModule/src/getresult.cpp", ios::app);

    std::map<string, string> mpfr_map = {
        {"+", "mpfr_add"},
        {"-", "mpfr_sub"},
        {"*", "mpfr_mul"},
        {"/", "mpfr_div"},
        {"exp", "mpfr_exp"},
        {"pow", "mpfr_pow"},
        {"sqrt", "mpfr_sqrt"},
        {"sin", "mpfr_sin"},
        {"log", "mpfr_log"},
        {"cos", "mpfr_cos"},
        {"atan", "mpfr_atan"},
        {"tan", "mpfr_tan"},
        {"cbrt", "mpfr_cbrt"}};
    
    std::unique_ptr<ExprAST> exprAst = ParseExpressionFromString(exprStr);
    // vector<string> vars;
    // getVariablesFromExpr(exprAst, vars);
    size_t mpfr_variables = 0;
    getMpfrParameterNumber(exprAst, mpfr_variables);

    ofs << "#include <getresult.hpp>\n"
        << "double getULP" << "(";
    for (auto &var : vars)
    {
        ofs << "double" << " " << var << ", ";
    }
    ofs << "double origin) {\n"
        << "\tmpfr_t mpfr_origin, mpfr_oracle, ";
    for (size_t i = 0; i < mpfr_variables; ++i)
    {
        if (i != mpfr_variables - 1)
            ofs << "mp" + to_string(i + 1) + ", ";
        else
            ofs << "mp" + to_string(i + 1) + ";\n";
    }
    ofs << "\tmpfr_inits2(128, mpfr_origin, mpfr_oracle, ";
    for (size_t i = 0; i < mpfr_variables; ++i) {
        ofs << "mp" + to_string(i + 1) + ", ";
    }
    ofs << "(mpfr_ptr) 0);\n";
    mpfr_variables = 0;
    string variable_tmp = "";
    mpfrCodeGenerator(exprAst, mpfr_variables, mpfr_map, ofs, variable_tmp);
    ofs << "\n\tmpfr_set(mpfr_oracle, mp" << mpfr_variables << ", MPFR_RNDN);\n" 
        << "\tmpfr_set_d(mpfr_origin, origin, MPFR_RNDN);\n"
        << "\tdouble ulp = computeULPDiff(mpfr_origin, mpfr_oracle);\n";
    ofs << "\tmpfr_clears(mpfr_origin, mpfr_oracle, ";
    for (size_t i = 0; i < mpfr_variables; ++i) {
        ofs << "mp" << to_string(i + 1) << ", ";
    }
    ofs << "(mpfr_ptr) 0);\n";
    ofs << "\tmpfr_free_cache();\n";
    ofs << "\treturn ulp;\n"
        << "}\n";
    
    ofs << "double getRelativeError(";
    for (auto &var : vars)
    {
        ofs << "double" << " " << var << ", ";
    }
    ofs << "double origin) {\n"
        << "\tmpfr_t mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, ";
    for (size_t i = 0; i < mpfr_variables; ++i)
    {
        if (i != mpfr_variables - 1)
            ofs << "mp" + to_string(i + 1) + ", ";
        else
            ofs << "mp" + to_string(i + 1) + ";\n";
    }
    ofs << "\tmpfr_inits2(128, mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, ";
    for (size_t i = 0; i < mpfr_variables; ++i) {
        ofs << "mp" + to_string(i + 1) + ", ";
    }
    ofs << "(mpfr_ptr) 0);\n";
    mpfr_variables = 0;
    mpfrCodeGenerator(exprAst, mpfr_variables, mpfr_map, ofs, variable_tmp);
    ofs << "\n\tmpfr_set(mpfr_oracle, mp" << mpfr_variables << ", MPFR_RNDN);\n" 
        << "\tmpfr_set_d(mpfr_origin, origin, MPFR_RNDN);\n"
        << "\tmpfr_sub(mpfr_absolute, mpfr_oracle, mpfr_origin, MPFR_RNDN);\n"
        << "\tmpfr_div(mpfr_relative, mpfr_absolute, mpfr_oracle, MPFR_RNDN);\n"
        << "\tdouble relative = mpfr_get_d(mpfr_relative, MPFR_RNDN);\n"
        << "\trelative = abs(relative);\n";
    ofs << "\tmpfr_clears(mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, ";
    for (size_t i = 0; i < mpfr_variables; ++i) {
        ofs << "mp" << to_string(i + 1) << ", ";
    }
    ofs << "(mpfr_ptr) 0);\n";
    ofs << "\tmpfr_free_cache();\n";
    ofs << "\treturn relative;\n"
        << "}\n";

    ofs << "double getFloatToDoubleOfOrigin(const float &inputx) {\n"
        << "\tdouble x = (double)inputx;\n";
    for (size_t i = 1; i < vars.size(); ++i) {
        ofs << "\tdouble " << vars[i] << " = " << 0.0 << ";\n";
    }
    ofs << "\treturn " << exprStr << ";\n"
        << "}\n";
    ofs << "double getDoubleOfOrigin(const double &inputx) {\n"
        << "\tdouble x = inputx;\n";
    for (size_t i = 1; i < vars.size(); ++i) {
        ofs << "\tdouble " << vars[i] << " = " << 0.0 << ";\n";
    }
    ofs << "\treturn " << exprStr << ";\n"
        << "}";
    ofs << "\n";

    ofs << "double getFloatToDoubleOfOrigin2(";
    for (auto i = 0; i < vars.size(); ++i) {
        if (i == vars.size() - 1) {
            ofs << "const float &input" << vars[i] << ") {\n";
        } else {
            ofs << "const float &input" << vars[i] << ", ";
        }
    }
    ofs << "\tdouble " << vars[0] << " = (double)input" << vars[0] << ";\n";
    for (size_t i = 1; i < vars.size(); ++i) {
        ofs << "\tdouble " << vars[i] << " = (double)input" << vars[i] << ";\n";
    }
    ofs << "\treturn ";
    for (size_t i = 0; i < vars.size(); ++i) {
        if (i == vars.size() - 1) {
            ofs << vars[i] << ";\n";
        } else {
            ofs << vars[i] << " + ";
        }
    }
    ofs << "}\n";

    ofs << "double getDoubleOfOrigin2(";
    for (auto i = 0; i < vars.size(); ++i) {
        if (i == vars.size() - 1) {
            ofs << "const double &input" << vars[i] << ") {\n";
        } else {
            ofs << "const double &input" << vars[i] << ", ";
        }
    }
    ofs << "\tdouble " << vars[0] << " = input" << vars[0] << ";\n";
    for (size_t i = 1; i < vars.size(); ++i) {
        ofs << "\tdouble " << vars[i] << " = input" << vars[i] << ";\n";
    }
    ofs << "\treturn ";
    for (size_t i = 0; i < vars.size(); ++i) {
        if (i == vars.size() - 1) {
            ofs << vars[i] << ";\n";
        } else {
            ofs << vars[i] << " + ";
        }
    }
    ofs << "}\n";
    return status;
}
