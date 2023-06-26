#include "basic.hpp"
#include "color.hpp"
#include "laxerASTLY.hpp"
#include "parserASTLY.hpp"
#include "geneCode.hpp"
#include <fstream>
#include <chrono>
#include <iomanip>
using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::endl;
int main() {
    installOperatorsForStr();
    fprintf(stderr, GREEN "ready> " RESET);
    string inputStr = "";
    int getlineCount = 0;
    while (getline(cin, inputStr)) {
        ++getlineCount;
        if (inputStr == "exit;" || inputStr == "quit;" || inputStr == "exit" || inputStr == "quit" ) {
            fprintf(stderr, "main: the application is end after inputing '%s'\n", inputStr.c_str());
            break;
        }
        if (inputStr.empty()) {
            fprintf(stderr, "WARNING: main: please input a expression before pressing Enter\n");
            fprintf(stderr, GREEN "ready> " RESET);
            continue;
        } else if (inputStr.back() == ';') {
            fprintf(stderr, "you do not need to add a ';' after the expression\n");
            inputStr.pop_back();
        }
        auto originExpr = ParseExpressionFromString(inputStr);
        vector<string> vars;
        getVariablesFromExpr(originExpr, vars);
        auto funcNameMpfr = geneMpfrCode(inputStr, vars);
        fprintf(stderr, GREEN "ready> " RESET);
    }
}