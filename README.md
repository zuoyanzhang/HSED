#### Introduction
HSED (Hierarchical search algorithm for error detection in floating-point arithmetic expressions).

HSED supports the parsing of mathematical expressions, MPFR version code generation and is a command line tool.

HSED based LLVM Tutorial-Chapter 2 implementing the Syntax Parser and AST Implementation (https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl02.html).

Example mathematical expressions (from the FPBench benchmark set http://fpbench.org/benchmarks.html).
* predatorPrey:((4.0 * x) * x) / (1.0 + ((x / 1.11) * (x / 1.11)))
* sqrt_add:(1 / (sqrt((x + 1)) + sqrt(x)))
* NMSEproblem333:((1.0 / (x + 1.0)) - (2.0 / x)) + (1.0 / (x - 1.0))
#### Engineering Process
Mathematical expressions -> lexical analysis -> syntactic analysis -> semantic analysis -> abstract syntax tree (AST) -> code generation -> error detection

#### Software Architecture
```
.
├── bin
├── include
│   ├── basic.hpp
│   ├── color.hpp
│   ├── geneCode.hpp
│   ├── laxerASTLY.hpp
│   └── parserASTLY.hpp
├── Makefile
├── README.md
└── src
│   ├── basic.cpp
│   ├── geneCode.cpp
│   ├── laxerASTLY.cpp
│   ├── main.cpp
│   └── parserASTLY.cpp
├── detectModule
│    ├── bin
│    ├── include
│    │   ├── common.hpp
│    │   ├── float.hpp
│    │   └── getresult.hpp
│    ├── Makefile
│    └── src
│        ├── common.cpp
│        ├── float.cpp
│        ├── main.cpp
└──      └── getresult.cpp
```
#### Installation Tutorial
###### Environmentally Dependent
gcc、g++、make、high precision library (MPFR, GMP)、m4

GMP library installation
```
Downloads links: https://gmplib.org/
First you need to install the m4 library: $ sudo apt-get install m4
$ wget https://gmplib.org/download/gmp/gmp-6.2.1.tar.xz
$ tar -xvJf gmp-6.2.1.tar.xz
$ cd gmp-6.2.1
$ ./configure --enable-cxx
$ make
$ make check
$ sudo make install
```

MPFR library installation
```
Downloads links: https://www.mpfr.org/mpfr-current/#download
$ wget https://www.mpfr.org/mpfr-current/mpfr-4.2.0.tar.xz
$ tar -xvJf mpfr-4.2.0.tar.xz
$ cd mpfr-4.2.0
$ ./configure --with-gmp-include=/usr/local/include --with-gmp-lib=/usr/local/lib
$ make
$ make check
$ sudo make install
```

#### Instructions for use
```
$ git clone https://github.com/zuoyanzhang/HSED.git
$ cd path/to/HSED
$ make
$ bin/errordetect.exe
ready> input expressions
e.g: ready> (x * x * x) / (x - 5.2331)
    ready> exit
$ cd detectModule
$ make
$ bin/errorDetect.exe parameter1 parameter2
e.g: bin/errorDetect.exe 1.0 2.0
//the parameter1 and parameter2 indicate the left and right endpoints of the detection interval.
```
#### Running Results
执行$./bin/errorDetect.exe 1.0 2.0，运行结果如下：
```
Detection interval: [1, 2]
preprocessing: x = 1.277344, maximumULP = 0.50, maximumRelative = 1.053593e-16

---------------No significant error, excute two-layer search------------------
float-precision layer: x = 1.01296334, maximumULP = 3.15, maximumRelative = 3.551087e-16

double-precision layer: x = 1.0129633739247148, maximumULP = 3.29, maximumRelative = 3.705561e-16, BitsError = 2.1
-------------------------------------------------------------------------------
```

#### Thesis Experimental Test Cases
| No. | Benchmark            | Expression                                                                                                                   |                D               | Relative Error |
|-----|----------------------|------------------------------------------------------------------------------------------------------------------------------|:------------------------------:|:--------------:|
| 1   | sqroot               |                       1.0 + 0.5   * x - 0.125 * x * x + 0.0625 * x * x * x - 0.0390625 * x * x * x * x                       | [0,1]                          |    3.17E-16    |
| 2   | sqrt_add             |                                               1.0 / (sqrt(x + 1.0) +   sqrt(x))                                              | [1,1000]                       |    2.72E-16    |
| 3   | exp1x                |                                                      (exp(x) - 1.0) / x                                                      | [0.01,0.5]                     |    1.09E-14    |
| 4   | exp1x_log            |                                                 (exp(x) - 1.0) / log(exp(x))                                                 | [0.01,0.5]                     |    2.52E-16    |
| 5   | NMSEexample37        |                                                         exp(x) - 1.0                                                         | [0.01,100]                     |    8.62E-15    |
| 6   | NMSEproblem336       |                                                     log(x + 1.0) - log(x)                                                    | [0.01,100]                     |    6.73E-14    |
| 7   | NMSEexample39        |                                                    1.0 / x - 1.0 / tan(x)                                                    | [0.01,100]                     |    5.59E-12    |
| 8   | NMSEproblem341       |                                                   (1.0 - cos(x)) / (x * x)                                                   | [0.01,100]                     |    3.58E-03    |
| 9   | NMSEsection311       |                                                    exp(x) / (exp(x) - 1.0)                                                   | [0.01,100]                     |    8.59E-15    |
| 10  | NMSEproblem345       |                                                  (x - sin(x)) / (x - tan(x))                                                 | [0.01,100]                     |    7.79E-12    |
| 11  | NMSEproblem337       |                                                    exp(x) - 2.0 + exp(-x)                                                    | [0.01,100]                     |    1.49E-12    |
| 12  | verhulst             |                                                 (4.0 * x) / (x / 1.11 + 1.0)                                                 | [0.1,0.3]                      |    1.66E-16    |
| 13  | predatorPrey         |                                          (4.0 * x * x) / (1 + x / 1.11   + x / 1.11)                                         | [0.1,0.3]                      |    3.15E-16    |
| 14  | logexp               |                                                       log(exp(x) - 1.0)                                                      | [0.01,8]                       |    4.99E-13    |
| 15  | sine                 |                 x - (x * x * x) / 6.0 + (x * x   * x * x * x) / 120.0 - (x * x * x * x * x * x * x) / 5040.0                 | [-1.57079632679,1.57079632679] |    2.74E-16    |
| 16  | carbonGas            | ((35000000.0 + ((0.401 *   (1000.0 / x)) * (1000.0 / x))) * (x - (1000.0 * 4.27e-5))) - ((1.3806503e-23   * 1000.0) * 300.0) | [0.1,0.5]                      |    2.89E-16    |
| 17  | NMSEproblem341       |                                                   (1.0 - cos(x)) / (x * x)                                                   | [0.01,100]                     |    3.58E-03    |
| 18  | NMSEexample38        |                                      (((x + 1.0) * log(x + 1.0)) -   (x * log(x))) - 1.0                                     | [0.01,100]                     |    5.58E-04    |
| 19  | NMSEproblem334       |                                                     cbrt(x + 1) - cbrt(x)                                                    | [0.01,100]                     |    2.13E-13    |
| 20  | NMSEproblem333       |                                     ((1.0 / (x + 1.0)) - (2.0 /   x)) + (1.0 / (x - 1.0))                                    | [0.01,100]                     |    1.54E-12    |
| 21  | NMSEproblem331       |                                                      1.0/(x+1) - (1.0/x)                                                     | [0.01,100]                     |    1.68E-14    |
| 22  | NMSEexample36        |                                                 1.0/sqrt(x) - 1.0 / sqrt(x+1)                                                | [0.01,100]                     |    4.76E-14    |
| 23  | NMSEexample35        |                                               1.0 / tan(x + 1) - 1.0 /   tan(x)                                              | [0.01,100]                     |    9.57E-15    |
| 24  | NMSEexample34        |                                                    (1.0 - cos(x)) / sin(x)                                                   | [0.01,100]                     |    3.58E-03    |
| 25  | NMSEexample31        |                                                     sqrt(x + 1) - sqrt(x)                                                    | [0,100]                        |    3.27E-14    |
| 26  | test05_nonlin1_r4    |                                                     (x - 1) / (x * x - 1)                                                    | [1.00001,2]                    |    4.80E-12    |
| 27  | test05_nonlin1_test2 |                                                        1.0 / (x + 1.0)                                                       | [1.00001,2]                    |    1.66E-16    |
| 28  | intro-example-mixed  |                                                         x / ( x + 1)                                                         | [1,999]                        |    1.67E-16    |
| 29  | sineOrder3           |                               (0.954929658551372 * x) -   (0.12900613773279798 * ((x * x) * x))                              | [-2,2]                         |    3.73E-16    |
| 30  | bsplines3            |                                                      (-x * x * x) / 6.0                                                      | [0,1]                          |    2.19E-16    |
| 31  | NMSEexample310       |                                                    log(1 - x) / log(1 + x)                                                   | [0.001,1]                      |    1.11E-13    |
| 32  | NMSEproblem343       |                                                    log((1 - x) / (1 + x))                                                    | [0.001,1]                      |    4.57E-14    |


