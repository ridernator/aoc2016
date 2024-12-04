#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
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

struct Bot {
  std::int64_t id = -1;
  std::int64_t low = -1;
  std::int64_t high = -1;
  std::int64_t lowTo = -1;
  std::int64_t highTo = -1;
};

void addNum(const std::int64_t num,
            Bot& bot) {
  if (bot.high == -1) {
    bot.high = num;
  } else if (bot.low == -1) {
    bot.low = std::min(bot.high, num);
    bot.high = std::max(bot.high, num);
  }
}

void clearBot(Bot& bot) {
  bot.low = -1;
  bot.high = -1;
}

int main() {
  const auto data = readFileToVector();

  std::map<std::int64_t, Bot> bots;
  const std::int64_t minNumber = 17;
  const std::int64_t maxNumber = 61;

  for (const auto& line : data) {
    if (line.find("value") != std::string::npos) {
      std::int64_t value;
      std::int64_t botId;
      sscanf(line.c_str(), "value %li goes to bot %li", &value, &botId);

      addNum(value, bots[botId]);
      bots[botId].id = botId;
    } else {
      std::int64_t botId;
      std::int64_t lowBotId;
      std::int64_t highBotId;

      if (sscanf(line.c_str(), "bot %li gives low to bot %li and high to bot %li", &botId, &lowBotId, &highBotId) == 3) {
        Bot& bot = bots[botId];
        bots[botId].id = botId;
        bot.lowTo = lowBotId;
        bot.highTo = highBotId;
      } else if (sscanf(line.c_str(), "bot %li gives low to output %li and high to bot %li", &botId, &lowBotId, &highBotId) == 3) {
        Bot& bot = bots[botId];
        bots[botId].id = botId;
        bot.lowTo = -1;
        bot.highTo = highBotId;
      } else if (sscanf(line.c_str(), "bot %li gives low to bot %li and high to output %li", &botId, &lowBotId, &highBotId) == 3) {
        Bot& bot = bots[botId];
        bots[botId].id = botId;
        bot.lowTo = lowBotId;
        bot.highTo = -1;
      } else if (sscanf(line.c_str(), "bot %li gives low to output %li and high to output %li", &botId, &lowBotId, &highBotId) == 3) {
        Bot& bot = bots[botId];
        bots[botId].id = botId;
        bot.lowTo = -1;
        bot.highTo = -1;
      } else {
      }
    }
  }

  std::int64_t comparatorBot = -1;

  while (true) {
    for (auto& bot : bots) {
      if ((bot.second.low == minNumber) && (bot.second.high == maxNumber)) {
        comparatorBot = bot.second.id;

        break;
      }

      if ((bot.second.low != -1) && (bot.second.high != -1)) {
        if (bot.second.lowTo != -1) {
          addNum(bot.second.low, bots[bot.second.lowTo]);
          bots[bot.second.lowTo].id = bot.second.lowTo;
        }

        if (bot.second.highTo != -1) {
          addNum(bot.second.high, bots[bot.second.highTo]);
          bots[bot.second.highTo].id = bot.second.highTo;
        }

        clearBot(bot.second);
      }
    }

    if (comparatorBot != -1) {
      break;
    }
  }

  std::cout << "Comparator bot is bot " << comparatorBot << std::endl;
}
