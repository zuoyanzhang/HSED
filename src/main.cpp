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
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    installOperatorsForStr();
    string inputStr = string(argv[1]);
    auto originExpr = ParseExpressionFromString(inputStr);
    vector<string> vars;
    getVariablesFromExpr(originExpr, vars);
    auto funcNameMpfr = geneMpfrCode(inputStr, vars);
    return 0;
}