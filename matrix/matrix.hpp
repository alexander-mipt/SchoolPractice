#pragma once
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <vector>

namespace M {

class IMatrix {
  public:
    virtual void deleteRow(uint row) = 0;
    virtual void addRow(uint row) = 0;
    virtual void addCol(uint col) = 0;
    virtual void deleteCol(uint col) = 0;
    virtual void printMatrix(const std::string &msg) const = 0;
    virtual void printMatrix() const = 0;
    virtual ~IMatrix() {}
};

class Matrix final: public IMatrix {
    using rowT = std::vector<int>;

  public:
    Matrix(uint N, std::vector<int>);
    void deleteRow(uint row) override;
    void addRow(uint row) override;
    void deleteCol(uint col) override;
    void addCol(uint col) override;
    void printMatrix(const std::string &msg) const override;
    void printMatrix() const override;

    size_t countRowZeros(uint row) const;
    long sumColElems(uint col);
  private:
    void spirallFill();
    std::vector<std::shared_ptr<rowT>> m_M{};
};
} // namespace M