#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>

#define INPUT "../data/input"
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 6

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

void rect(std::array<std::array<bool, SCREEN_HEIGHT>, SCREEN_WIDTH>& display,
          const size_t maxX,
          const size_t maxY) {
    for (size_t x = 0; x < maxX; ++x) {
        for (size_t y = 0; y < maxY; ++y) {
            display[x][y] = true;
        }   
    }
}

void rotateRow(std::array<std::array<bool, SCREEN_HEIGHT>, SCREEN_WIDTH>& display,
               const size_t row,
               const size_t rotateBy) {
    for (size_t rotateIndex = 0; rotateIndex < rotateBy; ++rotateIndex) {
        bool temp = display[SCREEN_WIDTH - 1][row];

        for (size_t index = SCREEN_WIDTH - 1; index > 0; --index) {
            display[index][row] = display[index - 1][row];
        }

        display[0][row] = temp;
    }
}

void rotateColumn(std::array<std::array<bool, SCREEN_HEIGHT>, SCREEN_WIDTH>& display,
                  const size_t column,
                  const size_t rotateBy) {
    for (size_t rotateIndex = 0; rotateIndex < rotateBy; ++rotateIndex) {
        bool temp = display[column][SCREEN_HEIGHT - 1];

        for (size_t index = SCREEN_HEIGHT - 1; index > 0; --index) {
            display[column][index] = display[column][index - 1];
        }

        display[column][0] = temp;
    }
}

uint64_t countLit(std::array<std::array<bool, SCREEN_HEIGHT>, SCREEN_WIDTH>& display) {
    uint64_t returnVal = 0;

    for (size_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (size_t x = 0; x < SCREEN_WIDTH; ++x) {
            if (display[x][y]) {
                ++returnVal;
            }
        }
    }

    return returnVal;
}

int main() {
    std::array<std::array<bool, SCREEN_HEIGHT>, SCREEN_WIDTH> display = {};
    std::vector<std::string> instructions = readFileToVector();

    for (const auto& instruction : instructions) {
        if (instruction.find("rect") != std::string::npos) {
            size_t x;
            size_t y;

            sscanf(instruction.c_str(), "rect %zux%zu", &x, &y);

            rect(display, x, y);
        } else if (instruction.find("row") != std::string::npos) {
            size_t row;
            size_t rotateBy;

            sscanf(instruction.c_str(), "rotate row y=%zu by %zu", &row, &rotateBy);

            rotateRow(display, row, rotateBy);
        } else if (instruction.find("column") != std::string::npos) {
            size_t column;
            size_t rotateBy;

            sscanf(instruction.c_str(), "rotate column x=%zu by %zu", &column, &rotateBy);

            rotateColumn(display, column, rotateBy);
        } else {
            std:: cout << "Don't know what to do with instruction : " << instruction << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    std::cout << "Number of pixels lit=" << countLit(display) << std::endl;
}
