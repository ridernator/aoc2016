#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <cctype>

#define INPUT "../data/input"

enum class Direction {
    N,
    E,
    S,
    W
};

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
    
    // Read to ","
    while (std::getline(fileStream, string, ',')) {
        // Remove all spaces
        string.erase(std::remove_if(string.begin(), string.end(), [] (unsigned char x) {
            return std::isspace(x); 
        }), string.end());

        returnVal.push_back(string);
    }

    return returnVal;
}

void turnRight(Direction& direction) {
    switch (direction) {
        case Direction::N: {
            direction = Direction::E;
            
            break;       
        }

        case Direction::E: {
            direction = Direction::S;
            
            break;       
        }

        case Direction::S: {
            direction = Direction::W;
            
            break;       
        }

        case Direction::W: {
            direction = Direction::N;
            
            break;       
        }
    }
}

void turnLeft(Direction& direction) {
    switch (direction) {
        case Direction::N: {
            direction = Direction::W;
            
            break;       
        }

        case Direction::E: {
            direction = Direction::N;
            
            break;       
        }

        case Direction::S: {
            direction = Direction::E;
            
            break;       
        }

        case Direction::W: {
            direction = Direction::S;
            
            break;       
        }
    }
}

void advance(const Direction direction,
             const int64_t amount,
             int64_t& x,
             int64_t& y) {
    switch (direction) {
        case Direction::N: {
            y += amount;
            
            break;       
        }

        case Direction::E: {
            x += amount;
            
            break;       
        }

        case Direction::S: {
            y -= amount;
            
            break;       
        }

        case Direction::W: {
            x -= amount;
            
            break;       
        }
    }
}

int main() {
    std::vector<std::string> commands = readFileToVector();
    Direction direction = Direction::N;
    int64_t x = 0;
    int64_t y = 0;
    int64_t amount;

    for (const auto& command : commands) {
        if (command[0] == 'R') {
            turnRight(direction);
        } else {
            turnLeft(direction);
        }

        amount = std::stoull(command.substr(1));

        advance(direction, amount, x, y);
    }

    std::cout << "Easter Bunny HQ is at " << x << ", " << y << ". Distance is " << (abs(x) + abs(y)) << std::endl;
}
