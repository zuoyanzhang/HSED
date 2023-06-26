#include "common.hpp"

double getULP(double x, double origin);
double getRelativeError(double x, double origin);
double getULP2(double x, double y, double z, double origin);
double getRelativeError2(double x, double y, double z, double origin);
double getFloatToDoubleOfOrigin(const float &inputx);
double getDoubleOfOrigin(const double &inputx);
double getFloatToDoubleOfOrigin2(const float &inputx, const double &inputy, const double &inputz);
double getDoubleOfOrigin2(const double &inputx, const double &inputy, const double &inputz);