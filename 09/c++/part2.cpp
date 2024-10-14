#include <cstddef>
#include <cstdint>
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

std::uint64_t lengthOf(const std::string string) {
  std::uint64_t returnVal = string.size();

  if (string.find('(') != std::string::npos) {
    returnVal = 0;

    for (std::size_t index = 0; index < string.size(); ++index) {
      if (string[index] == '(') {
        int numChars;
        int repeat;

        sscanf(string.substr(index + 1).c_str(), "%ix%i", &numChars, &repeat);

        returnVal += repeat * lengthOf(string.substr(string.find(')', index) + 1, numChars));

        index = string.find(')', index) + numChars;
      } else if (string[index] != '\n') {
        ++returnVal;
      }
    }
  }

  return returnVal;
}

int main() {
  auto data = readFile().str();

  std::cout << "Decompressed size: " << lengthOf(data) << std::endl;

  return 0;
}
