#include<iostream>
#include<vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

namespace zich{

    class Matrix{
        private:
            vector<double>arr;
            size_t rows;
            size_t cols;

        public:
            Matrix(const vector<double> &arr,int row,int col);
            Matrix();

            Matrix operator+(const Matrix &other)const;      
            Matrix& operator+=(const Matrix &other); 
            Matrix operator-(const Matrix &other)const;
            Matrix& operator-=(const Matrix &other);  
            Matrix& operator++();
            Matrix operator++(int);        
            Matrix& operator--();
            Matrix operator--(int);        
            Matrix operator-()const;  
            Matrix operator+()const;        
 
            bool operator==(const Matrix &other)const;
            bool operator!=(const Matrix &other)const;
            bool operator<=(const Matrix &other)const;
            bool operator<(const Matrix &other)const;
            bool operator>=(const Matrix &other)const;
            bool operator>(const Matrix &other)const;

            Matrix operator*(const Matrix &other)const;  
            Matrix& operator*=(double num);  
            Matrix operator*(double num)const;   
            Matrix& operator*=(const Matrix &other); 

            
            friend ostream& operator<< (ostream& output, const Matrix& mat);
            friend istream& operator>> (istream& input ,Matrix& mat);
            friend Matrix operator*(double num,const Matrix& mat);
            static vector<string> split(string input, char splitChar);



    };
}