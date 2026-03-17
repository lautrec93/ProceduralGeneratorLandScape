#pragma once
#include <iostream>
template <typename T>

class HeightMapRawContainer {
private:
  T value;

public:
  explicit HeightMapRawContainer(T val) : value(std::move(val)) {}
  const T &getValue() const { return value; }
  void showRawMap() {
    for (auto row{value.begin()}; row != value.end(); ++row) {
      std::cout << "[ ";
      for (auto col{row->begin()}; col != row->end(); ++col) {
        std::cout << *col << " ";
      }
      std::cout << "]\n";
    }
  }
};