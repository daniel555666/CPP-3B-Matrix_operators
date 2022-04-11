#include "Matrix.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include"doctest.h"

using namespace zich;
using namespace std;

TEST_CASE("CASE1 THROWS")
{

    vector<double> arr2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};

    CHECK_THROWS(Matrix m1(arr2, 8, 8));  // row and col make bigger matrix then the input
    CHECK_THROWS(Matrix m2(arr2, 1, 8)); // need place for 9 numbers
    CHECK_THROWS(Matrix m3(arr2, 0, 8)); // zero row
    CHECK_THROWS(Matrix m4(arr2, -1, 8)); // minus row
    CHECK_THROWS(Matrix m5(arr2, -1, 0)); // minus row and zero col
}


TEST_CASE("CASE2 ")
{

    vector<double> arr2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};          
    vector<double> arr3 = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    vector<double> arr5 = {5, 0, 0, 0, 5, 0, 0, 0, 5};
    vector<double> arr1 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> arrMinus1 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};

    Matrix m2(arr2, 3, 3);
    Matrix m3(arr3, 3, 3);
    Matrix m5(arr5, 3, 3);
    Matrix m1(arr1, 3, 3);
    Matrix m1minus(arrMinus1, 3, 3);

    CHECK((m1 != m2) == true);
    CHECK((m1 == m2) == false);
    CHECK((m1 <= m2) == true);
    CHECK((m1 < m2) == true);
    CHECK((m2 < m2) == false);
    CHECK((m1 >= m3) == false);
    CHECK((m1 > m3) == false);

    CHECK(((m1 + m2) == m3) == true);
    CHECK(((m2 + m3) == m5) == true);

    CHECK(((m5 - m2) == m3) == true);
    CHECK(((m3 - m2) == m1) == true);

    CHECK(((m2 - m3) == -m1) == true);
    CHECK(((-(m1)) == m1minus) == true);
    CHECK(((+m1 == m1)) == true);

    CHECK(((--m2) == m1) == true);
    CHECK(((++m1)==m2)==true);

    CHECK(((m1 * 5) == m5) == true);
    CHECK(((m1 * (-1)) == -m1) == true);

    CHECK(((m1 * m3) == m3) == true);

    CHECK(((m1 *= m3) == m3) == true);

}

