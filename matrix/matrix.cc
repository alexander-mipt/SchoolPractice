#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
namespace M {
void Matrix::deleteRow(size_t row) {
    if (row >= getNumRows()) {
        throw std::logic_error("Row idx is out of bounds");
    }
    for (auto i = row; i < m_M.size() - 1; ++i) {
        m_M[i] = m_M[i + 1];
    }
    m_M.pop_back();
}

void Matrix::addRow(size_t row) {
    if (row > m_M.size()) {
        throw std::logic_error("Row idx is out of bounds");
    }
    if (getNumCols() == 0) {
        m_M.push_back(std::make_shared<std::vector<int>>(std::vector<int>(1, 0)));
    } else {
        m_M.push_back(std::make_shared<std::vector<int>>(std::vector<int>(getNumCols(), 0)));
    }
    for (auto i = m_M.size() - 1; i >= row + 1; --i) {
        std::swap(m_M[i - 1], m_M[i]);
        // auto &tmp = m_M[i - 1];
        // m_M[i - 1] = m_M[i];
        // m_M[i] = tmp;
    }
}

void Matrix::deleteCol(size_t col) {
    if (col >= getNumCols()) {
        throw std::logic_error("Col idx is out of bounds");
    }
    if (getNumCols() == 1) {
        m_M.clear();
        assert(m_M.size() == 0);
        return;
    }
    for (auto &line_ptr : m_M) {
        auto &line = *line_ptr;
        for (auto i = col; i < line.size() - 1; ++i) {
            line[i] = line[i + 1];
        }
        line.pop_back();
    }
}

void Matrix::addCol(size_t col) {
    if (col > getNumCols()) {
        throw std::logic_error("Col idx is out of bounds");
    }
    if (getNumRows() == 0) {
        addRow(0);
        return;
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

Matrix::Matrix(size_t N, std::vector<int> vals) {
    if (N == 0) {
        throw std::logic_error("Incorrect matrix size");
    }
    for (size_t i = 0; i < N; ++i) {
        auto row = std::vector<int>(N, 0);
        auto ptr = std::make_shared<std::vector<int>>(row);
        m_M.push_back(ptr);
    }
    assert(m_M.size() == m_M.back()->size());

    auto numElems{m_M.size() * m_M.size()};
    if (vals.size() < numElems) {
        const auto extraZeros = numElems - vals.size();
        for (size_t i = 0; i < extraZeros; ++i) {
            vals.push_back(0);
        }
    }
    spirallFill(vals);
}

Matrix::Matrix(size_t N) {
    if (N == 0) {
        throw std::logic_error("Incorrect matrix size");
    }
    for (size_t i = 0; i < N; ++i) {
        auto row = std::vector<int>(N, 0);
        auto ptr = std::make_shared<std::vector<int>>(row);
        m_M.push_back(ptr);
    }
    assert(m_M.size() == m_M.back()->size());
    auto numElems = m_M.size() * m_M.size();
    std::vector<int> vals{};
    for (size_t i = 0; i < numElems; ++i) {
        vals.push_back(i);
    }
    spirallFill(vals);
}

inline size_t center(size_t sz) { return sz / 2 + sz % 2; }

void Matrix::spirallFill(const std::vector<int> &vals) {
    assert(vals.size() >= m_M.size() * m_M.size());
    auto val{vals.cbegin()};
    long hStart{0};
    long hEnd{static_cast<long>(m_M.size())};
    long vStart{0};
    long vEnd{static_cast<long>(m_M.size())};
    while (hStart < static_cast<long>(center(m_M.size()))) {
        assert(hStart < static_cast<long>(m_M.size()));
        assert(vStart < static_cast<long>(m_M.size()));

        long row{vStart};
        long col{hStart};
        // top side
        for (col = hStart; col < hEnd; ++col) {
            m_M.at(row)->at(col) = *(val++);
        }
        col = hEnd - 1;
        // right side
        for (row = vStart + 1; row < vEnd; ++row) {
            m_M.at(row)->at(col) = *(val++);
        }
        row = vEnd - 1;
        // bottom side
        for (col = hEnd - 2; col >= hStart; --col) {
            m_M.at(row)->at(col) = *(val++);
        }
        col = hStart;
        // left side
        for (row = vEnd - 2; row >= vStart + 1; --row) {
            m_M.at(row)->at(col) = *(val++);
        }
        // this->printMatrix();
        hStart++;
        vStart++;
        hEnd--;
        vEnd--;
    }
}

void Matrix::printMatrix(const std::string &msg) const {
    std::cout << "Matrix dump [" << getNumRows() << " x " << getNumCols() << "] " << msg << ":\n";
    for (auto &row : m_M) {
        for (auto &elem : *row) {
            std::cout << std::setw(4) << elem;
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Matrix::printMatrix() const { printMatrix(""); }

size_t Matrix::countRowZeros(size_t row) const {
    if (getNumCols() == 0 || getNumRows() == 0) {
        throw std::logic_error("Calculations on 0 dim matrix");
    }
    if (row > m_M.size()) {
        throw std::logic_error("Row idx is out of bounds");
    }
    return std::count(m_M.at(row)->cbegin(), m_M.at(row)->cend(), 0);
}

long Matrix::sumColElems(size_t col) const {
    if (getNumCols() == 0 || getNumRows() == 0) {
        throw std::logic_error("Calculations on 0 dim matrix");
    }
    if (col >= getNumCols()) {
        throw std::logic_error("Col idx is out of bounds");
    }
    long result{0};
    for (const auto &line_ptr : m_M) {
        const auto &line = *line_ptr;
        result += line.at(col);
    }
    return result;
}

long Matrix::sumRowElems(size_t row) const {
    if (getNumCols() == 0 || getNumRows() == 0) {
        throw std::logic_error("Calculations on 0 dim matrix");
    }
    if (row >= getNumRows()) {
        throw std::logic_error("Row idx is out of bounds");
    }
    auto &line = *m_M.at(row);
    long result{0};
    for (const auto &elem : line) {
        result += elem;
    }
    return result;
}

size_t Matrix::getNumElems() const { return m_M.size() * m_M.size(); }

size_t Matrix::getNumRows() const { return m_M.size(); }

size_t Matrix::getNumCols() const { return (m_M.size() == 0) ? 0 : m_M.at(0)->size(); }

} // namespace M