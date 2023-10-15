#ifndef __DOPOOMATH__
#define __DOPOOMATH__

static const double DoubleOneMinusEpsilon = 0x1.fffffffffffffp-1;
static const float FloatOneMinusEpsilon = 0x1.fffffep-1;

static const float toleranceF = 1e-5f;
static const double toleranceD = 1e-15;

static const float deltaF = 1e-5f;
static const double deltaD = 1e-9;

static const double invPi = 0.31830988618379067154;
static const double inv2Pi = 0.15915494309189533577;
static const double inv4Pi = 0.07957747154594766788;
static const double piOver2 = 1.57079632679489661923;
static const double piOver4 = 0.78539816339744830961;
static const double sqrt2 = 1.41421356237309504880;

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

double 
dopoo_double_clamp(double val, double low, double high) ;

void 
dopoo_double_swap(double* a, double* b);

#endif
