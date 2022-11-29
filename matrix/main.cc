#include "matrix.hpp"

int main() {
    M::Matrix obj{4, std::vector<int>{}};
    obj.printMatrix();
    obj.addCol(2);
    obj.printMatrix();
    obj.deleteCol(2);
    obj.printMatrix();
    obj.addRow(2);
    obj.printMatrix();
    obj.deleteRow(2);
    obj.printMatrix();
    obj.deleteRow(2);
    obj.printMatrix();
    obj.deleteCol(2);
    obj.printMatrix("test 2");
    obj.addCol(3);
    obj.addRow(3);
    obj.addCol(4);
    obj.addCol(5);
    obj.printMatrix();
    obj.addRow(4);
    obj.addRow(5);
    obj.addRow(6);
    obj.printMatrix();
    obj.deleteCol(0);
    obj.printMatrix("del col[0]");
    obj.deleteRow(0);
    obj.printMatrix("del row[0]");
    std::cout << obj.sumColElems(0) << std::endl;
}