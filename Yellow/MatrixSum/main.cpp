#include <iostream>
#include <vector>

using namespace std;


class Matrix {
public:
    Matrix(int new_rows = 0, int new_cols = 0) {
        if(new_rows < 0 || new_cols < 0) {
            throw out_of_range("Out of range");
        }
        rows = new_rows;
        cols = new_cols;
        data = vector{rows * cols};
    }
    void Reset(int new_rows, int new_cols) {
        if(new_rows < 0 || new_cols < 0) {
            throw out_of_range("Out of range");
        }
        rows = new_rows;
        cols = new_cols;
        data.clear();
        data = vector{rows * cols};
    }
    int At(int row, int col) const {
        if( row < 0 || row > rows ||
                col < 0 || col > cols) {
            throw out_of_range("Out of range");
        }
        return data[row*cols + col];
    }
    int& At(int row, int col) {
        if( row < 0 || row > rows ||
                col < 0 || col > cols) {
            throw out_of_range("Out of range");
        }
        return data[row*cols + col];
    }
    int GetNumRows() const {
        return rows;
    }
    int GetNumColumns() const {
        return cols;
    }
private:
    int rows;
    int cols;
    vector<int> data;
};

istream& operator>>(istream& stream, Matrix& matrix) {
    int rows = 0;
    int cols = 0;
    int i = 0;

    try {
        stream >> rows >> cols;

        matrix = {rows, cols};

        while(i < rows * cols) {
            stream >> matrix.At(i/cols, i%cols);
            ++i;
        }
    }  catch (exception& ex) {
    }

    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
    try {
        stream << matrix.GetNumRows() << ' ' <<
                  matrix.GetNumColumns();
        stream << EOF;

        for(int i = 0; i < matrix.GetNumRows(); ++i) {
            for(int j = 0; j < matrix.GetNumColumns(); ++j) {
                stream << matrix.At(i, j) << ' ';
            }
            stream << EOF;
        }
    }  catch (exception& ex) {
    }

    return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if(lhs.GetNumRows() != rhs.GetNumRows() ||
            lhs.GetNumColumns() != rhs.GetNumColumns()) {
        return false;
    }

    for(int i = 0; i < lhs.GetNumRows(); ++i) {
        for(int j = 0; j < lhs.GetNumColumns(); ++j) {
            if(lhs.At(i, j) != rhs.At(i, j)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    if(lhs.GetNumRows() != rhs.GetNumRows() ||
            lhs.GetNumColumns() != rhs.GetNumColumns()) {
        throw invalid_argument("Matrices have a different sizes");
    }

    Matrix result{lhs.GetNumRows(), lhs.GetNumColumns()};
    for(int i = 0; i < lhs.GetNumRows(); ++i) {
        for(int j = 0; j < lhs.GetNumColumns(); ++j) {
            result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }

    return result;
}

int main()
{
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
    return 0;
}
