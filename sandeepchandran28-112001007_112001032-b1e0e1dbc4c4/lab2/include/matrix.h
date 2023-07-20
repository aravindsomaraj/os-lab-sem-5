#ifndef MATRIX_H
#define MATRIX_H
#include <bits/stdc++.h>

class Matrix
{
    // Data Members
    public: 
    int C,R;
    double **v;
    int curr_row;

    // constructor
    Matrix(int r,int c);

    // function definitions
    void fetch_val(bool msg=false);
    void add_row( std::vector<int> num);
    void print_val(bool msg=false);
    void print_to_out(bool msg=true);
    
    void matrix_add(Matrix a);
    void matrix_subtract(Matrix a);
    void matrix_multiply(Matrix a);
    void transpose();
    void determinant();
    void get_Cofactor(double** mat, double** temp, int p, int q, int n);
    bool is_filled();
    int determinant_Matrix( double** mat, int n);

};

#endif
