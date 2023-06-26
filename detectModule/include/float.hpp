#include "common.hpp"

class DoubleFunction {
public:
    //第二种误差检测方法，操作double的尾数位，且增加显著误差判断分支决定起始操作的尾数位位数
    static void detectMethod2(const double &start, const double &end);
    static void detectMethod2_1(const double &start, const double &end);
    static void detectMethod2_2(const double &start, const double &end);
    //随机采样算法（目的是于模拟退火算法进行效果对比）
    static vector<double> random_test(const double &start, const double &end);
};
