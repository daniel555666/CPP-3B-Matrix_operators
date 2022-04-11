#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace zich;


Matrix::Matrix(const vector<double> &arr, int row, int col)
{
    if (row <= 0 || col <= 0 || row * col != arr.size())
    {
        throw runtime_error("bad input");
    }
    this->arr = arr;
    this->rows = (size_t)row;
    this->cols = (size_t)col;
}
Matrix::Matrix(){
    this->rows=0;
    this->cols=0;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (this->cols != other.cols || this->rows != other.rows)
    {
        throw runtime_error("Matrix size does not match");
    }
    vector<double> temp;
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        temp.push_back((double)(this->arr[i] + other.arr[i]));
    }
    return Matrix(temp, this->rows, this->cols);
}
Matrix Matrix::operator-() const
{

    vector<double> temp;
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        temp.push_back(this->arr[i] * -1);
    }
    return Matrix(temp, this->rows, this->cols);
}
Matrix &Matrix::operator+=(const Matrix &other)
{
    if (this->cols != other.cols || this->rows != other.rows)
    {
        throw runtime_error("Matrix size does not match");
    }
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        this->arr[i] = this->arr[i] + other.arr[i];
    }
    return *this;
}
Matrix Matrix::operator-(const Matrix &other) const
{
    return (*this) + (-other);
}
Matrix Matrix::operator+() const { return *this; }
Matrix &Matrix::operator-=(const Matrix &other)
{
    return (*this) += (-other);
}
Matrix &Matrix::operator++()
{

    for (size_t i = 0; i < this->arr.size(); i++)
    {
        this->arr[i] = this->arr[i] + 1;
    }
    return *this;
}
Matrix &Matrix::operator--()
{
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        this->arr[i] = this->arr[i] - 1;
    }
    return *this;
}
Matrix Matrix::operator++(int right)
{
    Matrix temp(this->arr, this->rows, this->cols);
    ++(*this);
    return temp;
}
Matrix Matrix::operator--(int right)
{
    Matrix temp(this->arr, this->rows, this->cols);
    --(*this);
    return temp;
}
bool Matrix::operator==(const Matrix &other) const
{
    if (this->cols != other.cols || this->rows != other.rows)
    {
        throw runtime_error("Matrix size does not match");
    }
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        if (this->arr[i] != other.arr[i])
        {
            return false;
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix &other) const
{
    bool b=false;
    if (*this == other)
    {
        return b;
    }
    return !b;
}
bool Matrix::operator<(const Matrix &other) const
{
    if (this->cols != other.cols || this->rows != other.rows)
    {
        throw runtime_error("Matrix size does not match");
    }
    int sumThis = 0;
    int sumOther = 0;
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        sumThis += this->arr[i];
        sumOther += other.arr[i];
    }
    bool b=true; //for tidy
    if (sumThis < sumOther)
    {
        return b;
    }
        return !b;
}

bool Matrix::operator<=(const Matrix &other) const
{
    bool b=true;
    if (*this < other || *this == other)
    {
        return b;
    }
    return !b;
}
bool Matrix::operator>(const Matrix &other) const
{
    if (this->cols != other.cols || this->rows != other.rows)
    {
        throw runtime_error("Matrix size does not match");
    }
    int sumThis = 0;
    int sumOther = 0;
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        sumThis += this->arr[i];
        sumOther += other.arr[i];
    }
    bool b=true;
    if (sumThis > sumOther)
    {
        return b;
    }
        return !b;
}
bool Matrix::operator>=(const Matrix &other) const
{   bool b= true;
    if (*this > other || *this == other)
    {
        return b;
    }
    return !b;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (this->cols != other.rows)
    {
        throw runtime_error("Matrix size does not match");
    }
    vector<double> temp;

    for (size_t i = 0; i < this->rows; i++)            //rows for
    {
        for (size_t j = 0; j < other.cols; j++)         //cols for
        {
            double sum = 0;
            for (size_t k = 0; k < this->cols; k++)    //move on the row or cols
            {
                sum += this->arr[i * this->cols + k] * other.arr[k * other.cols + j];
            }
            temp.push_back(sum);
        }
    }
    return Matrix(temp, this->rows, other.cols);
}
Matrix &Matrix::operator*=(double num)
{
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        this->arr[i] *= num;
    }
    return *this;
}
Matrix Matrix::operator*(double num) const
{
    vector<double> temp;
    for (size_t i = 0; i < this->arr.size(); i++)
    {
        temp.push_back(this->arr[i] * num);
    }
    return Matrix(temp, this->rows, this->cols);
}
Matrix &Matrix::operator*=(const Matrix &other)
{
    if (this->cols != other.rows)
    {
        throw runtime_error("Matrix size does not match");
    }
    vector<double> temp;

    for (size_t i = 0; i < this->rows; i++)                   //rows for
    {
        for (size_t j = 0; j < other.cols; j++)               //cols for
        {
            double sum = 0;
            for (size_t k = 0; k < this->cols; k++)            // move on the line or row
            {
                sum += this->arr[i * this->cols + k] * other.arr[k * other.cols + j];
            }
            temp.push_back(sum);
        }
    }
    this->arr = temp;
    this->cols = other.cols;
    return *this;
}

/**
 * @brief splite to strings by a char and insert to vector
 * 
 * @param input the string to split
 * @param splitChar char to split by
 * @return vector<string> 
 */
vector<string> Matrix::split(string input, char splitChar)
{
    vector<string> temp;
    for (size_t i = 0; i < input.size(); i++)    //for on all the string chars
    {
        string str;
        while (input[i] != splitChar && i < input.size())  
        {
            str += input[i++];                          //add the char to the ward
        }
        temp.push_back(str);                          //add the string to the vector
    }
    return temp;
}

namespace zich
{

    ostream &operator<<(ostream &output, const Matrix &mat)
    {
        string str;
        for (size_t i = 0; i < mat.rows; i++)
        {
            output << "[";
            for (size_t j = 0; j < mat.cols; j++)
            {
                output << mat.arr[i * mat.cols + j];
                if ((j + 1) % mat.cols != 0) // check if not in the end of the row
                {
                    output << " ";
                }
            }
            if (i + 1 != mat.rows) // check if not in the end of the col
            {
                output << "]\n";
            }
            else
            {
                output << "]";
            }
        }
        return (output << str);
    }

    istream &operator>>(istream &input, Matrix &mat)
    {
        vector<double> newArr;
        string strInput = " "; // all lines have space in the start also the first one
        char check=0;
        while (check != '\n')  //convert input to string
        {
            check = input.get();
            strInput += check;
        }

        vector<string> rows = Matrix::split(strInput, ',');   //splite to lines
        for (size_t i = 0; i < rows.size(); i++)
        {
            rows[i] = rows[i].substr(2, rows[i].size() - 3); // remove the [ ] from the string
        }
        rows[rows.size() - 1] = rows[rows.size() - 1].substr(0, rows[rows.size() - 1].size() - 1); // remove the last ]
        vector<string> firstRow = Matrix::split(rows[0], ' ');                            // save the numbers of the first row
        size_t cols = firstRow.size(); // save the cols number

        for (size_t i = 0; i < rows.size(); i++)
        {
            vector<string> rowArr = Matrix::split(rows[i], ' ');
            if (rowArr.size() != cols)
            {
                throw runtime_error("bad input (1)");
            }
            for (size_t j = 0; j < rowArr.size(); j++)
            { // split all line to arr with just numbers
                try
                {
                    newArr.push_back(stod(rowArr[j])); // insert the number to the array
                }
                catch (exception e)
                {
                    throw runtime_error("bad input (2)");
                }
            }
        }
        mat.rows = rows.size();
        mat.cols = cols;
        mat.arr = newArr;

        return input;
    }
    Matrix operator*(double num, const Matrix &mat)
    {
        vector<double> temp;
        for (size_t i = 0; i < mat.arr.size(); i++)
        {
            temp.push_back(mat.arr[i] * num);
        }
        return Matrix(temp, mat.rows, mat.cols);
    }
}

// int main()
// {
//     vector<double> arr = {0, 3, 1, 0, 1, 0, 2, 0, 1};
//     Matrix mat(arr, 3, 3);
//     cout<<mat<<endl<<endl;

//     Matrix mat2;
//     istringstream is7{"[1 1 1 1], [1 1 1 1], [1 1 1 1]\n"};
//     is7 >> mat2;
//     cout<<mat2<<endl<<endl;
    
//     vector<double> arr3 = {2, 0, 2, 0, 2, 0,};
//     Matrix mat3(arr3, 3, 2);
//     cout<<mat<<endl<<endl;
//     cout<<mat3<<endl<<endl;
//     cout<<mat*mat3;


//     return 0;
// }