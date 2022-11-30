#pragma once
#include <cstdint>
#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace M {

class IMatrix {
  public:
    // delete row w/ idx in [0; row_num)
    virtual void deleteRow(size_t row) = 0;
    virtual void deleteCol(size_t col) = 0;
    // add row w/ idx in [0; row_num]
    virtual void addRow(size_t row) = 0;
    virtual void addCol(size_t col) = 0;
    // printers
    virtual void printMatrix(const std::string &msg) const = 0;
    virtual void printMatrix() const = 0;
    // getters
    virtual size_t getNumElems() const = 0;
    virtual size_t getNumRows() const = 0;
    virtual size_t getNumCols() const = 0;

    virtual ~IMatrix() {}
};

class Matrix final : public IMatrix {
    using rowT = std::vector<int>;
    using matrixT = std::vector<std::shared_ptr<rowT>>;

  public:
    // fill matrix NxN w/ 1, 2, ... in spiral clockwise direction
    Matrix(size_t N);
    // same as the 1st constructor, but we can determine sequnce of vals
    Matrix(size_t N, std::vector<int> vals);

    // overrided interface from IMatrix
    void deleteRow(size_t row) override;
    void addRow(size_t row) override;
    void deleteCol(size_t col) override;
    void addCol(size_t col) override;
    void printMatrix(const std::string &msg) const override;
    void printMatrix() const override;
    size_t getNumElems() const override;
    size_t getNumRows() const override;
    size_t getNumCols() const override;

    // additional methids for task
    size_t countRowZeros(size_t row) const;
    long sumColElems(size_t col) const;
    long sumRowElems(size_t row) const;

  private:
    // fill matrix in spiral clockwise dir w/ values listed in vector (sequentally)
    void spirallFill(const std::vector<int> &vals);
    // state
    matrixT m_M{};
};
} // namespace M