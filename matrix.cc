#include "matrix.hpp"
#include <cassert>
#include <iomanip>
#include <algorithm>
namespace M {
void Matrix::deleteRow(uint row) {
    if (row >= m_M.size()) {
        throw std::logic_error("Row idx is out of bounds");
    }
    for (auto i = row; i < m_M.size() - 1; ++i) {
        m_M[i] = m_M[i + 1];
    }
    m_M.pop_back();
}

void Matrix::addRow(uint row) {
    if (row > m_M.size()) {
        throw std::logic_error("Row idx is out of bounds");
    }
    m_M.push_back(std::make_shared<std::vector<int>>(std::vector<int>(m_M.at(0)->size(), 0)));
    for (auto i = m_M.size() - 1; i >= row + 1; --i) {
        std::swap(m_M[i - 1], m_M[i]);
        // auto &tmp = m_M[i - 1];
        // m_M[i - 1] = m_M[i];
        // m_M[i] = tmp;
    }
}

void Matrix::deleteCol(uint col) {
    if (col > m_M.at(0)->size()) {
        throw std::logic_error("Col idx is out of bounds");
    }
    for (auto &line_ptr : m_M) {
        auto &line = *line_ptr;
        for (auto i = col; i < line.size() - 1; ++i) {
            line[i] = line[i + 1];
        }
        line.pop_back();
    }
}

void Matrix::addCol(uint col) {
    if (col > m_M.at(0)->size()) {
        throw std::logic_error("Col idx is out of bounds");
    }
    for (auto &line_ptr : m_M) {
        auto &line = *line_ptr;
        line.push_back(0);
        for (auto i = line.size() - 1; i >= col + 1; --i) {
            auto tmp = line.at(i);
            line[i] = line.at(i - 1);
            line[i - 1] = tmp;
        }
    }
}

Matrix::Matrix(uint N, std::vector<int>) {
    if (N == 0) {
        throw std::logic_error("Incorrect matrix size");
    }
    for (auto i = 0; i < N; ++i) {
        auto row = std::vector<int>(N, 0);
        auto ptr = std::make_shared<std::vector<int>>(row);
        m_M.push_back(ptr);
    }
    assert(m_M.size() == m_M.back()->size());

    spirallFill();
}

inline size_t center(size_t sz) {
    return sz / 2 + sz % 2;
}

void Matrix::spirallFill() {
    int val{0};
    int hStart{0};
    int hEnd{m_M.size()};
    int vStart{0};
    int vEnd{m_M.size()};
    while (hStart < center(m_M.size())) {
        assert(hStart < m_M.size());
        assert(vStart < m_M.size());
        
        int row{vStart};
        int col{hStart};
        // top side
        for (col = hStart; col < hEnd; ++col) {
            m_M.at(row)->at(col) = val++;
        }
        col = hEnd - 1;
        // right side
        for (row = vStart + 1; row < vEnd; ++row) {
            m_M.at(row)->at(col) = val++;
        }
        row = vEnd - 1;
        // bottom side
        for (col = hEnd - 2; col >= hStart; --col) {
            m_M.at(row)->at(col) = val++;
        }
        col = hStart;
        // left side
        for (row = vEnd - 2; row >= vStart + 1; --row) {
            m_M.at(row)->at(col) = val++;
        }
        // this->printMatrix();
        hStart++;
        vStart++;
        hEnd--;
        vEnd--;
    }
}

void Matrix::printMatrix(const std::string& msg) const {
    std::cout << "Matrix dump " << msg << ":\n";
    for (auto &row : m_M) {
        for (auto &elem : *row) {
            std::cout << std::setw(4) << elem;
        }
        std::cout << std::endl;
    }
}

void Matrix::printMatrix() const {
    printMatrix("");
}

size_t Matrix::countRowZeros(uint row) const {
    if (row > m_M.size()) {
        throw std::logic_error("Row idx is out of bounds");
    }
    return std::count(m_M.at(row)->cbegin(), m_M.at(row)->cend(), 0);
}

long Matrix::sumColElems(uint col) {
    if (col > m_M.at(0)->size()) {
        throw std::logic_error("Col idx is out of bounds");
    }
    long result{0};
    for (const auto &line_ptr: m_M) {
        const auto &line = *line_ptr;
        result += line.at(col);
    }
    return result;
}

} // namespace M