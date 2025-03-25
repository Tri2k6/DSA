#include <iostream>
#include <limits.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define endl '\n'
#define vi vector<int> 
#define fileMatrixA "matrix_a.txt"
#define fileMatrixB "matrix_b.txt"
#define fileMatrixC "matrix_c.txt"
#define fileMatrixC_T "matrix_c_transposed.txt"

bool readMatrix(const char* filename, int** &matrix, int &rows, int &cols);
void printMatrix(const char* filename, int** matrix, int rows, int cols);
bool multiplyMatrices(int** a, int aRows, int aCols, int** b, int bRows, int bCols, int** &res, int &resRows, int &resCols);
void transposeMatrix(int** matrix, int rows, int cols, int** &res, int &resRows, int &resCols);


int main() {

    int aRows, aCols, bRows, bCols, cRows, cCols;
    int ** matrixA, **matrixB, ** matrixC;

    if (!readMatrix(fileMatrixA, matrixA, aRows, aCols) || !readMatrix(fileMatrixB, matrixB, bRows, bCols)) {
        cout << "Error for reading matrixA or matrixB";
        return 0;
    } 

    if (multiplyMatrices(matrixA, aRows, aCols, matrixB, bRows, bCols, matrixC, cRows, cCols)) {
        cout << "Successful to multiply matrixA and matrixB" << endl;
        printMatrix(fileMatrixC, matrixC, cRows, cCols);
    } else {
        cout << "Error to multiply matrixA and matrixB" << endl;
    }

    int cRow_T,  cCol_T;
    int ** matrixC_T;

    transposeMatrix(matrixC, cRows, cCols, matrixC_T, cRow_T, cCol_T);
    printMatrix(fileMatrixC_T, matrixC_T, cRow_T, cCol_T);

    return 0;
}

bool readMatrix(const char* filename, int** &matrix, int &rows, int &cols) {
    ifstream input(filename);   
    if (!input.is_open()) return false;

    vector<vi> tmp;
    int fixed_cols = -1;

    while (true) {
        string str;
        getline(input,str);
        istringstream ss(str);

        int val;
        vi v;

        while (ss >> val) {
            v.push_back(val);
            // cout << val << ' ';
        }

        // cout << endl;


        if (v.size() > 0) {
            tmp.push_back(v);
            if (fixed_cols == -1) fixed_cols = v.size();
            else if (v.size() != fixed_cols) return false;
        }

        if (input.eof()) break;
    }

    rows = tmp.size();
    cols = tmp[0].size();
    matrix = new int*[rows];

    for (int i = 0;i < rows;i++) {
        matrix[i] = new int [cols];
        for (int j = 0;j < cols;j++) {
            matrix[i][j] = tmp[i][j];
        }
    }

    return true;
}

void printMatrix(const char* filename, int** matrix, int rows, int cols) {
    ofstream output(filename);

    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            output << matrix[i][j] << ' ';
        }
        output << endl;
    }
}

bool multiplyMatrices(int** a, int aRows, int aCols, int** b, int bRows, int bCols, int** &res, int &resRows, int &resCols) {
    if (aCols != bRows) return false;
    
    resRows = aRows;
    resCols = bCols;
    res = new int *[aRows];
    for (int i = 0;i < aRows;i++) {
        res[i] = new int[bCols];
    }

    for (int i = 0;i < resRows;i++) {
        for (int j = 0;j < resCols;j++) {
            res[i][j] = 0;
            for (int k = 0;k < aCols;k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return true;
}

void transposeMatrix(int** matrix, int rows, int cols, int** &res, int &resRows, int &resCols) {
    resRows = cols;
    resCols = rows;
    
    res = new int * [resRows];
    for (int i = 0;i < resRows;i++) {
        res[i] = new int [resCols];
    }

    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            res[j][i] = matrix[i][j];
        }
    }
}
