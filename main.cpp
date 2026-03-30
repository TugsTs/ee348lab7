#include <iostream>
#include <fstream>

using namespace std;
const int SIZE = 4;

//matrix class using template as refence
class Matrix {
private:
    int data[SIZE][SIZE];

public:
    void readFile(ifstream& file);
    void display() const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    int sumOfDiagonals() const;
    void swapRows(int r1, int r2);
};

//define our matrix class methods


//Used nested for loops to read matrix data
void Matrix::readFile(ifstream& file){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            file >> data[i][j];
        }
    }
}

//display matrix 
void Matrix::display() const{
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

// plus(+) operator overload for matrix addition
Matrix Matrix::operator+(const Matrix& other) const{
    Matrix result;

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

// multiply(*) operator overload for matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const{
    Matrix result;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            result.data[i][j] = 0;
            for(int k = 0; k < SIZE; k++){
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

//sum of both diagonals in a matrix
int Matrix::sumOfDiagonals() const{
    int sum = 0;
    for(int i = 0; i < SIZE; i++){
        sum += data[i][i];// topleft to bottomright
        sum += data[i][SIZE - i - 1];// topright to bottomleft
    }
    return sum;
}

//swapping two rows using a temporary variable
void Matrix::swapRows(int r1, int r2){
    if(r1 < 0 || r1 >= SIZE || r2 < 0 || r2 >= SIZE){
        cout << "invalid rows" << endl;
        return;
    }// check for invalid row indices
    for(int j = 0; j < SIZE; j++){
        int temp = data[r1][j];
        data[r1][j] = data[r2][j];
        data[r2][j] = temp;
    }
}

//we need to call our needed methods in main
int main(){
    ifstream file("matrix-data.txt");
    if(!file){
        cout << "File not found" << endl;
        return 1;
    }
    Matrix m1;
    Matrix m2;

    m1.readFile(file);
    m2.readFile(file);

    cout << "Matrix 1:" << endl;
    m1.display();
    cout << "\n";
    cout << "Matrix 2:" << endl;
    m2.display();

    cout << "\n";

    Matrix sum = m1 + m2;
    cout << "Addition:" << endl;
    sum.display();

    cout << "\n";

    Matrix product = m1*m2;
    cout << "Multiplication:" << endl;
    product.display();

    cout << "\n";

    cout << "Sum of the main and secondary diagonals in matrix1: ";
    cout << m1.sumOfDiagonals() << endl;

    cout << "\n";

    m2.swapRows(0, 2);

    cout << "rows '0' and '2' swapped in matrix2" << endl;
    m2.display();

    return 0;
}
