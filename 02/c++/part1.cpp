#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#define INPUT "../data/input"

/**
 * Read a file entirely into a stringstream
 *
 * @param The name of the file to read
 * @return The contents of the file
 **/
std::stringstream readFile(const std::string& filename = INPUT) {
  std::ifstream fileStream(filename);
  std::stringstream returnVal;

  returnVal << fileStream.rdbuf();

  return returnVal;
}

/**
 * Read a file entirely into a vector of strings
 *
 * @param The name of the file to read
 * @return The vector of lines in the file
 **/
std::vector<std::string> readFileToVector(const std::string& filename = INPUT) {
  std::ifstream fileStream(filename);
  std::string string;
  std::vector<std::string> returnVal;

  while (std::getline(fileStream, string)) {
    returnVal.push_back(string);
  }

  return returnVal;
}

struct Key {
  std::size_t value;

  Key* L = nullptr;
  Key* R = nullptr;
  Key* U = nullptr;
  Key* D = nullptr;
};

int main() {
  Key keys[9];

  for (std::size_t index = 0; index < 9; ++index) {
    keys[index].value = index + 1;

    if (index >= 3) {
      keys[index].U = &keys[index - 3];
    }

    if (index <= 5) {
      keys[index].D = &keys[index + 3];
    }

    if (index % 3 != 0) {
      keys[index].L = &keys[index - 1];
    }

    if (index % 3 != 2) {
      keys[index].R = &keys[index + 1];
    }
  }

  auto lines = readFileToVector();
  Key* currentKey = &keys[4];

  std::cout << "Code is: ";

  for (const auto& line : lines) {
    for (const auto& command : line) {
      switch (command) {
        case 'U': {
          if (currentKey->U != nullptr) {
            currentKey = currentKey->U;
          }

          break;
        }

        case 'D': {
          if (currentKey->D != nullptr) {
            currentKey = currentKey->D;
          }

          break;
        }

        case 'L': {
          if (currentKey->L != nullptr) {
            currentKey = currentKey->L;
          }

          break;
        }

        case 'R': {
          if (currentKey->R != nullptr) {
            currentKey = currentKey->R;
          }

          break;
        }

        default: {
          std::cerr << "Unknown command \"" << command << "\"" << std::endl;

          break;
        }
      }
    }

    std::cout << currentKey->value;
  }

  std::cout << std::endl;

  return 0;
}
