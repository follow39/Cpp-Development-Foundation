#include <iostream>
#include <vector>

using namespace std;


class Matrix {
public:
    Matrix(int new_rows = 0, int new_cols = 0) {
        if(new_rows < 0 || new_cols < 0) {
            throw out_of_range("Out of range");
        }
        if(new_rows != 0 && new_cols != 0) {
            rows = new_rows;
            cols = new_cols;
            data = vector<int>(rows * cols);
        }
        else {
            rows = 0;
            cols = 0;
        }
    }
    void Reset(int new_rows, int new_cols) {
        if(new_rows < 0 || new_cols < 0) {
            throw out_of_range("Out of range");
        }
        if(new_rows != 0 && new_cols != 0) {
            rows = new_rows;
            cols = new_cols;
            data.clear();
            data = vector<int>(rows * cols);
        }
        else {
            rows = 0;
            cols = 0;
            data.clear();
            data = vector<int>{};
        }
    }
    int At(int row, int col) const {
        if( row < 0 || row >= rows ||
                col < 0 || col >= cols) {
            throw out_of_range("Out of range");
        }
        return data[row*cols + col];
    }
    int& At(int row, int col) {
        if( row < 0 || row >= rows ||
                col < 0 || col >= cols) {
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

    try {
        stream >> rows >> cols;

        if(rows == 0 && cols == 0) {
            matrix = Matrix{};
        } else {
            matrix = {rows, cols};
            for(int i = 0; i < rows; ++i) {
                for(int j = 0; j < cols; ++j) {
                    stream >> matrix.At(i, j);
                }
            }
        }
    }  catch (exception& ex) {
    }

    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
    try {
        stream << matrix.GetNumRows() << ' ' <<
                  matrix.GetNumColumns();
        stream << '\n';

        for(int i = 0; i < matrix.GetNumRows(); ++i) {
            for(int j = 0; j < matrix.GetNumColumns(); ++j) {
                stream << matrix.At(i, j) << ' ';
            }
            stream << '\n';
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
        throw invalid_argument("");
    }
    if(lhs.GetNumRows() == 0 && rhs.GetNumRows() == 0) {
        return Matrix{};
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
    return 0;
}
