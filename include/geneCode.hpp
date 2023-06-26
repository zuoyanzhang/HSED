#ifndef _GENECODE
#define _GENECODE

#include "basic.hpp"

#include<stdio.h>
#include <fstream>
#include<iostream>
#include<vector>
using namespace std;
using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::string;

bool getVariablesFromExpr(const ast_ptr &expr, vector<string> &vars);

int geneMpfrCode(const string exprStr, vector<string> vars);

#endif