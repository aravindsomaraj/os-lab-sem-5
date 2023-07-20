#include <bits/stdc++.h>
#include <iomanip>
#include "../include/matrix.h"
#include "../include/log.h"

using namespace std;

    // constructor
    Matrix::Matrix(int r,int c)
    {
        R=r;
        C=c;
        v = new double* [R];
        for (int i=0;i<R;i++)
            v[i]= new double[C];
        curr_row=0;
    }

    // Member Functions()
    void Matrix::fetch_val(bool msg /*=false*/)
    {
        if (msg)
            cout << "to get the values for the matrix \n";
        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                cin >> v[i][j];
            }
        }
    }

    void Matrix::add_row(vector<int> num)
    {
        int j=0;
        for(int t:num)
        {
            v[curr_row][j]=t;
            j++;
        }
        curr_row++;
    }

    bool Matrix::is_filled()
    {
        if(curr_row != R)
            return false;
            
        return true;
    }

    void Matrix::print_val(bool msg/*=false*/)
    {
        if(msg)
            cout << "printing values in matrix\n";
        for(int i=0;i<R;i++)
        {
            string tt="";
            for(int j=0;j<C;j++)
            {
                tt+= to_string(v[i][j])+" ";
                // L_(linfo) << v[i][j] << " ";
            }
                L_(linfo) <<tt;
        }
    }

    void Matrix::print_to_out(bool msg/*=true*/)
    {
        if(msg)
        {
            cout << R <<" "<<C<<endl;
            string tt="";
            for(int i=0;i<R;i++)
                {
                    for(int j=0;j<C;j++)
                    {
                        cout << v[i][j] << ",";
                    }
                        cout <<"\n";
                }
        }
        else
        {
                cout <<v[0][0]<<"\n";
        }
    }

    void Matrix::matrix_add(Matrix a)
    {
        if(a.C!=C || a.R!=R)
        {
            L_(lerror) << "Matrix dimension missmatch, can't add";
            return;
        }

        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                v[i][j]=v[i][j]+a.v[i][j];
            }
        }
        L_(linfo) <<"addition of matrices completed";
    }

    void Matrix::matrix_subtract(Matrix a)
    {
        if(a.C!=C || a.R!=R)
        {
            L_(lerror) << "Matrix dimension missmatch, can't subtract";
            return;
        }

        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                v[i][j]=v[i][j]-a.v[i][j];
            }
        }
        L_(linfo) <<"subtraction of matrices completed";
    }

    void Matrix::matrix_multiply(Matrix a)
    {
        if(a.R!=C)
        {
            L_(lerror) << "Matrix dimension missmatch, can't multiply\t" << R<<"\t" <<C <<"\t"<<a.R <<"\t"<<a.C;
            return;
        }

        double **y;
        y=new double*[R];
        for (int i=0;i<R;i++)
            y[i]=new double[a.C];

        for(int i=0;i<R;i++)
        {
            for(int j=0;j<a.C;j++)
            {
                y[i][j]=0;
                for(int k=0;k<C;k++)
                {
                    y[i][j]+=v[i][k]*(a.v[k][j]);
                }
            }
        }

        C=a.C;

        v = new double* [R];
        for (int i=0;i<R;i++)
            v[i]= new double[C];
        v=y;


        L_(linfo) <<"multiplication of matrices completed";
    }

    void Matrix::transpose()
    {
        double **temp;
        temp = new double*[C];

        for (int i=0;i<C;i++)
            temp[i]= new double[R];

        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                temp[j][i]=v[i][j];
            }
        }

        int t=R;
        R=C;
        C=t;

        v = new double* [R];
        for (int i=0;i<R;i++)
            v[i]= new double[C];
        
        v=temp;
        L_(linfo) <<"transpose of matrix generated";
    }

    void Matrix::determinant(){

        if(C!=R)
        {
            L_(lerror) << "not a square matrix "<< R << " x "<<C;
            return;
        }

        int ans=determinant_Matrix(v,C);
       
        double **y;
        y= new double*[1];
        for (int i=0;i<1;i++)
            y[i]= new double[1];
        y[0][0]=ans;

        C=1;
        R=C;
        v = new double* [R];
        for (int i=0;i<R;i++)
            v[i]= new double[C];

        v=y;

        L_(linfo) <<"determinant of matrix computed:" <<ans << "\t" << R << "\t" <<C ;
    }

    void Matrix::get_Cofactor(double** mat, double** temp, int p,int q, int n)
    {
        int i=0, j=0;

        for (int row=0; row<n; row++)
        {
            for (int col=0; col<n; col++)
            {
                if (row!=p && col!=q)
                {
                    temp[i][j++] = mat[row][col];
    
                    if (j == n-1)
                    {
                        j=0;
                        i++;
                    }
                }
            }
        }
    }

    int Matrix::determinant_Matrix( double** mat, int n)
    {
        int N=n;
        int D = 0;
    
        if (n == 1)
            return mat[0][0];
            
    	// array to store cofactors
        double** temp; 
        temp = new double* [n];
        
        for (int i=0;i<n;i++)
            temp[i]= new double[n];
    
    	// To store sign
        int sign = 1; 
        
        // Iterate for each element of first row
        for (int j=0; j<n; j++)
        {
            //to find the Cofactor of mat[0][j]
            get_Cofactor(mat, temp, 0, j, n);
            D += sign * mat[0][j]
                * determinant_Matrix(temp, n-1);
    
            sign = -sign;
        }
        return D;
    }


