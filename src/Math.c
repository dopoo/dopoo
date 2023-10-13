

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
