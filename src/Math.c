

double 
dopoo_double_clamp(double val, double low, double high) 
{
    if (val < low)
        return low;
    else if (val > high)
        return high;
    else
        return val;
}

void 
dopoo_double_swap(double* a, double* b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
