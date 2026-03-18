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
  void showMin() {
    double min{1};
    for (auto row{value.begin()}; row != value.end(); ++row) {
      for (auto col{row->begin()}; col != row->end(); ++col) {
        if (*col <= min) {
          min = *col;
        }
      }
    }
    std::cout << min << "\n";
  }
  void showMax() {
    double max{-1};
    for (auto row{value.begin()}; row != value.end(); ++row) {
      for (auto col{row->begin()}; col != row->end(); ++col) {
        if (*col >= max) {
          max = *col;
        }
      }
    }
    std::cout << max << "\n";
  }

  void showMid(double size) {
    double mid{};
    for (auto row{value.begin()}; row != value.end(); ++row) {
      for (auto col{row->begin()}; col != row->end(); ++col) {
        mid += *col;
      }
    }
    std::cout << mid / size << "\n";
  }
};