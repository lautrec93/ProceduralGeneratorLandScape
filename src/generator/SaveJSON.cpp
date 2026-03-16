#include <fstream>
#include <vector>

void saveJSON(const std::vector<std::vector<double>> &field,
              const std::string &filename) {
  std::ofstream file(filename);

  file << "[\n";

  for (size_t i = 0; i < field.size(); ++i) {
    file << "  [";

    for (size_t j = 0; j < field[i].size(); ++j) {
      file << field[i][j];

      if (j + 1 < field[i].size())
        file << ", ";
    }

    file << "]";

    if (i + 1 < field.size())
      file << ",";

    file << "\n";
  }

  file << "]\n";
}