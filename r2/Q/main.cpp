#include <iostream>
#include <utility>
#include <vector>

struct Shape {
  std::vector<std::pair<int, int>> zeroes, ones;
  int height, width;
};

const std::vector<Shape> shapes = {
    {std::vector<std::pair<int, int>>{{0, 0}, {1, 1}},
     std::vector<std::pair<int, int>>{{0, 1}, {1, 0}}, 2, 2},
    {std::vector<std::pair<int, int>>{{0, 1}, {1, 0}},
     std::vector<std::pair<int, int>>{{0, 0}, {1, 1}}, 2, 2},
    {std::vector<std::pair<int, int>>{{0, 1}, {1, 1}},
     std::vector<std::pair<int, int>>{{0, 0}, {1, 0}, {0, 2}, {1, 2}}, 2, 3},

};
