#ifndef scalar_H
#define scalar_H
#include <bits/stdc++.h>
#include "matrix.h"

class Scalar_operations
{
    public: 
    Scalar_operations();
    void add(Matrix mat, int scal);
    void subtract(Matrix mat, int scal);
    void multiply(Matrix mat, int scal);
    void divide(Matrix mat, int scal);
};

#endif
