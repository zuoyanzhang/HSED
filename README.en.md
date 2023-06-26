# HSED

#### Introduction
HSED(Hierarchical search algorithm for error detection in floating-point arithmetic expressions).

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

