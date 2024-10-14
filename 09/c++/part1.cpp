#include <cstddef>
#include <cstdio>
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

int main() {
  auto data = readFile().str();
  std::stringstream output;

  for (std::size_t index = 0; index < data.size(); ++index) {
    if (data[index] == '(') {
      int numChars;
      int repeat;

      sscanf(data.substr(index + 1).c_str(), "%ix%i", &numChars, &repeat);
      index = data.find(')', index);

      for (int index2 = 0; index2 < repeat; ++index2) {
        output << data.substr(index + 1, numChars);
      }

      index += numChars;
    } else if (data[index] != '\n') {
      output << data[index];
    }
  }

  std::cout << "Decompressed size: " << output.str().size() << std::endl;

  return 0;
}
