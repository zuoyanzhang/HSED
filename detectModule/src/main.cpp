#include "float.hpp"

using std::cin;
using std::cout;
typedef union {
    int i;
    float f;
} FL;

typedef union {
    long int i;
    double d;
} DL;

int main(int argc, char *argv[]) {
    if (argc == 3) {
        double start = atof(argv[1]);
        double end = atof(argv[2]);
        if (start > end) {
            cout << "start > end, input range error, you have to input start <= end" << endl;
            return 0;
        } else if (end <= 0) {//处理start和end<=0的情况
            DoubleFunction::detectMethod2_1(start, end);
        } else if (start < 0 && end > 0) {//处理start<0但是end>0的情况，即区间跨越了0
            DoubleFunction::detectMethod2_2(start, end);
        } else {//处理start和end都大于等于0的情况
            DoubleFunction::detectMethod2(start, end); 
        }
    } else if (argc == 5) { //双参算术表达式
        
    } else {
        cout << "please input 3 or 5 numbers" << endl;
    }
    return 0;
}
