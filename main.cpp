#include "Matrix.h"
#include "Complex.h"

using namespace std;

int main(int argc, char **argv) {

    using namespace std;


    // read Complex matrix from file
    size_t *rows = new size_t[1];
    size_t *columns = new size_t[1];

    // create complex matrix
    Complex<int> **data = Complex<int>::read_matrix("complex_matrix.txt", rows, columns);

    Matrix<Complex<int>> complex_matrix(data, *rows, *columns);

    // pirnt complex matrix
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *columns; ++j) {
            cout << complex_matrix[i][j] << "\t";
        }
        cout << endl;
    }


    // multiply
    complex_matrix *= complex_matrix;

    // print again
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *columns; ++j) {
            cout << complex_matrix[i][j] << "\t";
        }
        cout << endl;
    }


    // clean up
    for (int i = 0; i < *rows; ++i) {
        delete[] data[i];
    }

    delete[] data;

    return 0;
}
