# HSED

#### 介绍
本项目属于自研课题开发，基于层级搜索算法的浮点算术表达式误差检测。

HSED支持数学表达式的解析，mpfr版本代码生成，是一个命令行工具。

HSED基于LLVM教程——第二章 实现语法分析器和AST实现(https://llvm-tutorial-cn.readthedocs.io/en/latest/chapter-2.html)。

数学表达式示例（来自FPBench基准集http://fpbench.org/benchmarks.html）
* predatorPrey:((4.0 * x) * x) / (1.0 + ((x / 1.11) * (x / 1.11)))
* sqrt_add:(1 / (sqrt((x + 1)) + sqrt(x)))
* NMSEproblem333:((1.0 / (x + 1.0)) - (2.0 / x)) + (1.0 / (x - 1.0))
#### 工作流程
数学表达式->词法分析->语法分析->语义分析->抽象语法树(AST)->代码生成->误差检测

#### 软件架构
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
#### 安装教程
###### 依赖环境
gcc、g++、make、高精度库（mpfr、gmp）、m4

GMP库安装
```
下载链接：https://gmplib.org/
首先需要安装m4库：$sudo apt-get install m4
进入GMP目录：$./configure --enable-cxx
$make
$make check
$sudo make install
```

MPFR库安装
```
下载链接：https://www.mpfr.org/mpfr-current/#download
进入MPFR目录：$./configure --with-gmp-include=/usr/local/include --with-gmp-lib=/usr/local/lib
$make
$make check
$sudo make install
```

#### 使用说明
```
git clone https://github.com/zuoyanzhang/HSED.git
cd path/to/HSED
make
./bin/errordetect.exe
//输入数学表达式生成高精度版本代码
cd detectModule
make
./bin/errorDetect.exe parameter1 parameter2
//parameter1和parameter2表示检测表达式的区间
```
#### 运行效果
执行$./bin/errorDetect.exe 1.0 2.0，运行结果如下：
```
Detection interval: [1, 2]
preprocessing: x = 1.788086, maximumULP = 0.50, maximumRelative = 8.626883e-17

---------------No significant error, excute two-layer search------------------
float-precision layer: x = 1.64610558, maximumULP = 2.71, maximumRelative = 3.090448e-16

double-precision layer: x = 1.6461056093252275, maximumULP = 2.87, maximumRelative = 3.274910e-16, BitsError = 2.0
-------------------------------------------------------------------------------
```

