#pragma once
#include <cstdint>
#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

namespace M {

int spiral2linear(int row, int colon, int size);

int getCircleRadius(uint row, uint colon, size_t N) {}

class IMatrix {
    virtual void deleteRow(uint row) = 0;
    virtual void addRow(uint row) = 0;
    virtual void addCol(uint col) = 0;
    virtual void deleteCol(uint col) = 0;
    virtual void printMatrix() const = 0;
    virtual void deleteCol() = 0;
    virtual void addCol() = 0;
};

class Matrix : public IMatrix {
    using rowT = std::vector<int>;

  public:
    Matrix(uint N, std::vector<int>);
    void deleteRow(uint row) override;
    void addRow(uint row) override;
    void deleteCol(uint col) override;
    void addCol(uint col) override;
    void printMatrix() const override;

  private:
    void spirallFill();
    std::vector<std::shared_ptr<rowT>> m_M{};
};

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
    m_M.push_back(std::make_shared<std::vector<int>>(std::vector<int>{}));
    for (auto i = m_M.size() - 1; i >= row; --i) {
        auto &tmp = m_M[i - 1];
        m_M[i - 1] = m_M[i];
        m_M[i] = tmp;
    }
}

void Matrix::deleteCol(uint col) {
    for (auto &line_ptr : m_M) {
        auto &line = *line_ptr;
        for (auto i = col; i < m_M.size() - 1; ++i) {
            line[i] = line[i + 1];
        }
        line.pop_back();
    }
}

void Matrix::addCol(uint col) {
    for (auto &line_ptr : m_M) {
        auto &line = *line_ptr;
        line.push_back(0);
        for (auto i = m_M.size() - 1; i >= col; --i) {
            auto &tmp = line[i];
            line[i] = line[i - 1];
            line[i - 1] = tmp;
        }
    }
}

Matrix::Matrix(uint N, std::vector<int>) {
    for (auto i = 0; i < N; ++i) {
        auto row = std::vector<int>(N, 0);
        auto ptr = std::make_shared<std::vector<int>>(row);
        m_M.push_back(ptr);
    }

    spirallFill();
}

void Matrix::spirallFill() {
    int val{0};
    int hStart{0};
    int hEnd{m_M.size()};
    int vStart{0};
    int vEnd{m_M.size()};
    int row{vStart};
    int col{hStart};

    while (hStart <= vStart) {
        // top side
        for (col = hStart; col < hEnd; ++col) {
            m_M.at(row)->at(col) = val++;
        }
        // right side
        for (row = vStart + 1; row < vEnd; ++row) {
            m_M.at(row)->at(col) = val++;
        }
        // bottom side
        for (col = hEnd - 1; col >= hStart; --col) {
            m_M.at(row)->at(col) = val++;
        }
        // left side
        for (row = vEnd - 1; row >= vStart + 1; --row) {
            m_M.at(row)->at(col) = val++;
        }
        hStart++;
        vStart++;
        hEnd--;
        vEnd--;
    }
}

void Matrix::printMatrix() const {
    std::cout << "Matrix dump:\n";
    for (auto &row : m_M) {
        for (auto &elem : *row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}
} // namespace M