#include <bits/stdc++.h>
#include <iomanip>
#include "../include/scalar.h"
#include "../include/log.h"
#include "../include/matrix.h"

using namespace std;

    // constructor
    Scalar_operations::Scalar_operations()
    {
    }

    void Scalar_operations::add(Matrix mat, int scal)
    {
        for(int i=0;i<mat.R;i++)
        {
            for(int j=0;j<mat.C;j++)
            {
                mat.v[i][j]+=scal;
            }
        }
        L_(linfo) <<"addition of scalar done";
    }

    void Scalar_operations::subtract(Matrix mat, int scal)
    {
        for(int i=0;i<mat.R;i++)
        {
            for(int j=0;j<mat.C;j++)
            {
                mat.v[i][j]-=scal;
            }
        }
        L_(linfo) <<"subtraction of scalar done";
    }

     void Scalar_operations::multiply(Matrix mat, int scal)
    {
        for(int i=0;i<mat.R;i++)
        {
            for(int j=0;j<mat.C;j++)
            {
                mat.v[i][j]*=scal;
            }
        }
        L_(linfo) <<"multiplication by scalar done";
    }

    void Scalar_operations::divide(Matrix mat, int scal)
    {
        if(scal==0)
        {
            L_(lerror) << "divide by zero exception";
            return;
        }

        for(int i=0;i<mat.R;i++)
        {
            for(int j=0;j<mat.C;j++)
            {
                mat.v[i][j]/=(1.0*scal);
            }
        }
        L_(linfo) <<"division by scalar done";
    }