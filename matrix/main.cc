#include "matrix.hpp"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

/* declarations */
// generate random vector of size size w/ values in [min, max] & fixed seed (=0 by default)
std::vector<int> randomVector(int min, int max, size_t size, unsigned seed = 0);
// for task 2
void deleteRowWithMaxZeros(M::Matrix &m);
// for task 3
void deletePositiveCols(M::Matrix &m);
// for task 4
void printMatrixSums(M::Matrix &m);

int main() {
    size_t N = 8; // matrix dimention
    // task 1
    M::Matrix m1{N};     // create
    m1.printMatrix("1"); // print result

    // task 2
    N = 4;
    M::Matrix m2{N, std::vector<int>{1, 3, 5, 4, 6, 0, 7, 1, 1, 8, 9, 0, 1, 0, 0, 0, 8, 8}};
    m2.printMatrix("2");
    deleteRowWithMaxZeros(m2);
    m2.printMatrix("2");

    // task 3
    N = 3;
    M::Matrix m3{N, std::vector<int>{1, 1, 1, 0, -1, 1, 1, 1, 1}};
    m3.printMatrix("3");
    deletePositiveCols(m3);
    m3.addCol(0);
    m3.printMatrix("3");

    // task 4
    N = 4;
    M::Matrix m4{N, randomVector(3, 90, N * N)};
    m4.printMatrix("4");
    printMatrixSums(m4);
}

/* definitions */

std::vector<int> randomVector(int min, int max, size_t size, unsigned seed) {
    assert(min <= max);
    srand(seed);
    std::vector<int> vec{};
    for (size_t i = 0; i < size; ++i) {
        auto val = (rand() % (max - min + 1)) + min;
        vec.push_back(val);
    }
    return vec;
}

void deleteRowWithMaxZeros(M::Matrix &m) {
    size_t zerosMax{0};
    auto row{0};
    for (size_t i = 0; i < m.getNumRows(); ++i) {
        auto zeros = m.countRowZeros(i);
        if (zeros > zerosMax) {
            row = i;
            zerosMax = zeros;
        }
    }
    m.deleteRow(row);
}

void deletePositiveCols(M::Matrix &m) {
    size_t col{0};
    while (col < m.getNumCols()) {
        if (m.sumColElems(col) > 0) {
            m.deleteCol(col);
        } else {
            col++;
        }
    }
}

void printMatrixSums(M::Matrix &m) {
    for (size_t row = 0; row < m.getNumCols(); ++row) {
        std::cout << "Row " << std::setw(4) << row << ": " << m.sumRowElems(row) << "\n";
    }
    std::cout << std::endl;
    for (size_t col = 0; col < m.getNumCols(); ++col) {
        std::cout << "Col " << std::setw(4) << col << ": " << m.sumColElems(col) << "\n";
    }
    std::cout << std::endl;
}