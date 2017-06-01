#include "Matrix.h"
#include "Complex.h"

// util function to print matrices
template<class T>
void print_matrix(Matrix<T> &matrix) {
    cout << "==== begin =====\n";

    for (int i = 0; i < matrix.get_rows(); ++i) {
        for (int j = 0; j < matrix.get_columns(); ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "==== end ====\n\n";
}


int main(int argc, char **argv) {
    using namespace std;

    //=============== int example ===============//

    /* create empty matrix (5 - rows, 6 - columns) */

    Matrix<int> empty_matrix(5, 6);

    cout << "print empty 5 x 6 matrix:\n\n";

    print_matrix<int>(empty_matrix);



    /* read matrix from file */

    Matrix<int> file_matrix((char *) "matrix_2_to_3.txt");

    cout << "print read from file matrix:\n\n";

    print_matrix(file_matrix);



    /* create matrix from another matrix */

    Matrix<int> clone_matrix(file_matrix); // copy constructor will be invoked

    cout << "print cloned matrix:\n\n";

    print_matrix(file_matrix);



    /* copy assignment operator */

    empty_matrix = clone_matrix;

    cout << "print matrix after copy assignment operator:\n\n";

    print_matrix(clone_matrix);


    /* operator + */

    Matrix<int> first_operand((char *) "matrix_2_to_3_other.txt"); // read matrix from some file

    Matrix<int> second_operand(file_matrix);

    Matrix<int> addition_matrix = first_operand + second_operand; // addition

    cout << "Add 2 matrices:\n\n";

    cout << "First one: \n";
    print_matrix(first_operand);

    cout << "Second one: \n";
    print_matrix(second_operand);

    cout << "Their sum:\n";
    print_matrix(addition_matrix);



    /* multiplication */

    Matrix<int> multiplier_matrix((char *) "multiplier_matrix_3_to_5.txt");

    cout << "Multiply 2 matrices:\n\n";

    cout << "First one:\n";
    print_matrix(file_matrix);

    cout << "Second one:\n";
    print_matrix(multiplier_matrix);

    file_matrix *= multiplier_matrix;

    // auto mult_matrix = file_matrix * multiplier_matrix; // i.e. you can also do like this

    cout << "Result of multiplication:\n";
    print_matrix(file_matrix);


    //=============== Complex example ===============//

    size_t rows, columns = 0; // actual size of the matrix will be stored here
    size_t rows2, columns2 = 0;

    // read complex matrices from files
    Complex<int> **data = Complex<int>::read_matrix("complex_matrix_2_to_3.txt", &rows, &columns);
    Complex<int> **data2 = Complex<int>::read_matrix("complex_matrix_3_to_2.txt", &rows2, &columns2);


    Matrix<Complex<int>> complex_matrix(data, rows, columns); // create matrix of complex elements

    cout << "print the complex matrix:\n\n";

    print_matrix<Complex<int>>(complex_matrix); // print the matrix


    Matrix<Complex<int>> complex_matrix2(data2, rows2, columns2); // create another complex matrix

    cout << "print another complex matrix:\n\n";

    print_matrix(complex_matrix2);


    /* operator += */

    complex_matrix += complex_matrix;

    cout << "print the first matrix's += with itself:\n";

    print_matrix(complex_matrix);

    /* operator *= */

    complex_matrix *= complex_matrix2;

    cout << "print the multiplication result of 2 matrices:\n\n";

    print_matrix(complex_matrix);

    // clean up
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }

    for (int i = 0; i < rows2; ++i) {
        delete[] data2[i];
    }

    delete[] data;
    delete[] data2;

    return 0;
}
