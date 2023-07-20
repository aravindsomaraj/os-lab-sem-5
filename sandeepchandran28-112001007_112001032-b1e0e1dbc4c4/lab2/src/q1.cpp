#include <bits/stdc++.h>
#include <iomanip>
#include "../include/matrix.h"
#include "../include/log.h"
#include "../include/scalar.h"

using namespace std;

vector<int> int_tokenize(string s, string del = "")
{
    vector<int> nums;
    int l;
    int r = s.find(del);
    while (r != -1) {
        nums.push_back(stoi(s.substr(l, r - l)));
        l = r + del.size();
        r = s.find(del, l);
    }
    return nums;
}
void iterate_over_mat(list<Matrix> mat, bool opt)
{

    while(1)
    {
        if(mat.empty()==true)
             break;
        mat.front().print_val(opt);
        mat.pop_front();
    }
}


void iterate_over_intl(list<int> mat,bool convert=false){
    while(1)
    {
        if(mat.empty()==true)
             break;
        if(convert)
            {
                string item=mat.front()==1? "matrix":"scalar";
                L_(linfo) <<item <<"\t";
            }
        else
            L_(linfo) <<mat.front() <<"\t";
        mat.pop_front();
    }
   
}

void file_read2(list<Matrix> &mat, list<int> &scalars, list<int> &arg)
{
    string line;
    string mode = "n";
    while (getline(cin, line))
    {
        char t = line[0];

        if(int(line[0])==13 || t == '#' ) //accounting for delimiter or comment
            continue;
  
        else if(line.find(",") != -1 && mode =="r")
        {
            // this has values
            vector<int> vnum=int_tokenize(line,",");
            mat.back().add_row(vnum);
            if(mat.back().is_filled())
                mode=="n";
        }

        else if(line.find(" ") != -1)
        {
                // matrix definiton
                int ind = line.find(" ");
                string s1= line.substr(0,ind);
                string s2= line.substr(ind,line.size());
                
                int d1=stoi(s1);
                int d2=stoi(s2);

                Matrix t(d1,d2);
                mat.push_back(t);
                mode = 'r';
                arg.push_back(1);
        }
        
        else 
        {

            int d=stoi(line);
            scalars.push_back(d);
            arg.push_back(0);

        }
    }
}

void print_info(list<Matrix> mat,list<int> scalars,list<int> ord_arg,bool opt=true)
{
        L_(linfo) << "PRINT INFO\n";
        L_(linfo) << "total matrices: " <<mat.size();
        L_(linfo) << "total scalars: " <<scalars.size();
        L_(linfo) << "matrix";
        iterate_over_mat(mat,opt);

        L_(linfo) << "scalars";
        iterate_over_intl(scalars);
        L_(linfo) << "order of arguments";
        iterate_over_intl(ord_arg,true);
}

int main(int argc, char **argv)
{
    initLogger( "logfile.log", ldebug);
    L_(linfo) << "logfile";
    list<Matrix> mat;           //maintains matrices
    list<int> scalars;         //maintains scalars
    list<int> next_arg;     //maintains order

    // 1,0 values for matrices and arguments 

    Scalar_operations smo;

    file_read2(mat,scalars,next_arg);
    L_(linfo) << " " <<(argc-1) <<"\n";
    int cc=1;

    int ps;
    bool scalar_mode=false;

    if(next_arg.front()==0)
    {
        next_arg.pop_front();
        next_arg.pop_front();
        next_arg.push_front(0);
        next_arg.push_front(1);
    }

    Matrix mat_backup=mat.front();
    print_info(mat,scalars,next_arg,false);
    
    next_arg.pop_front();
    bool last_op_det=false;


    while(cc<argc)
    {
        string cmd=argv[cc];
        
        L_(ldebug) << "matrices left: " << mat.size() <<"  scalars left: " << scalars.size();
        L_(linfo) << argv[cc];

        // exiting cases
        // no matrices
        if(mat.empty())
        {
            L_(lerror) << "matrix insufficient";
            break;
        }
        //2 argument operations
        if(mat.size()==1 && scalars.size()==0 && (cmd=="-a"||cmd=="-s"||cmd=="-m"))
        {
            // only 1 matrix and no scalars for a 2 part operation
            L_(lerror) << "arguments insufficient";
            break;
        }

        // uni scalar argument divison
        if(scalars.size()==0 && cmd=="-d")
        {
            L_(lerror) << "no scalar to divide with";
            break;
        }

        //converting determinant matrix into a scalar
        if(last_op_det)
        {
            int sv=mat.front().v[0][0];
            L_(linfo) << "using determinant value as scalar : "<<sv;
            scalars.push_front(sv);
            mat.pop_front();
            last_op_det=false;
            next_arg.push_front(0);
        }

        Matrix pm=mat.front();
        
        if(!scalars.empty() && next_arg.front()==0 && cmd!="-x" && cmd!="-t")
        {
            ps=scalars.front();
            scalars.pop_front();
            scalar_mode=true;
            next_arg.pop_front();
        }
        else
        {
            scalar_mode=false;
        }



        if(cmd=="-a")
        {
            if(scalar_mode)
            {
                smo.add(pm,ps);
            }
            else
                {
                    if(mat.empty())
                    {
                        L_(lerror) << "no more matrices to operate upon";
                        // return 1;
                        break;
                    }
                    mat_backup=mat.front();
                    mat.pop_front();
                    Matrix sec=mat.front();
                    sec.matrix_add(pm);
                    next_arg.pop_front();
                }
        }

        else if(cmd=="-s")
        {
            if(scalar_mode)
            {
                smo.subtract(pm,ps);

            }
            else
                {
                    if(mat.empty())
                    {
                        L_(lerror) << "no more matrices to operate upon";
                        break;                        
                    }
                    mat.pop_front();
                    Matrix sec=mat.front(); 
                    mat.pop_front();
                    mat.push_front(pm);
                    mat.front().matrix_subtract(sec);
                    next_arg.pop_front();
                }
        }

        else if(cmd=="-m")
        {
            if(scalar_mode)
            {
                // pm.multiply_scalar(ps);
                smo.multiply(pm,ps);
            }
            else
                {
                    if(mat.empty())
                    {
                        L_(lerror) << "no more matrices to operate upon";
                        break;
                    }
                    mat.pop_front();
                    Matrix sec=mat.front();
                    mat.pop_front();
                    mat.push_front(pm);
                    mat.front().matrix_multiply(sec);
                    next_arg.pop_front();
                }
        }


        else if(cmd=="-d")
        {
          if(scalar_mode)
            {
                smo.divide(pm,ps);
            }
            else
                {
                   L_(lerror) <<"No scalar or determinant found";
                   break; 
                }
        }


        else if(cmd=="-t")
        {
            mat.front().transpose();
        }

        else if (cmd=="-x")
        {
            mat.front().determinant();
            if(mat.front().C==1 && mat.front().R==1) //success
            last_op_det=true;
        }

        else{
            L_(lerror) << "invalid command line argument";

        }

        cc++;
    }

    L_(linfo) <<"FINAL OUTPUT generated";
    if(mat.empty())
    {
        mat_backup.print_to_out();
    }
    else
    {
        if(last_op_det )     //C==1 checking  //print it as a scalar
            mat.front().print_to_out(false);
        else
            mat.front().print_to_out();
    }

    endLogger();
    return 0;
}