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

  std::int64_t output0 = 0;
  std::int64_t output1 = 0;
  std::int64_t output2 = 0;

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
        bot.lowTo = lowBotId * -1 - 1;
        bot.highTo = highBotId;
      } else if (sscanf(line.c_str(), "bot %li gives low to bot %li and high to output %li", &botId, &lowBotId, &highBotId) == 3) {
        Bot& bot = bots[botId];
        bots[botId].id = botId;
        bot.lowTo = lowBotId;
        bot.highTo = highBotId * -1 - 1;
      } else if (sscanf(line.c_str(), "bot %li gives low to output %li and high to output %li", &botId, &lowBotId, &highBotId) == 3) {
        Bot& bot = bots[botId];
        bots[botId].id = botId;
        bot.lowTo = lowBotId * -1 - 1;
        bot.highTo = highBotId * -1 - 1;
      } else {
      }
    }
  }

  bool anyWorkDone  = true;

  while (anyWorkDone) {
    anyWorkDone = false;

    for (auto& bot : bots) {
      if ((bot.second.low != -1) && (bot.second.high != -1)) {
        anyWorkDone = true;

        if (bot.second.lowTo >= 0) {
          addNum(bot.second.low, bots[bot.second.lowTo]);
          bots[bot.second.lowTo].id = bot.second.lowTo;
        } else if (bot.second.lowTo == -1) {
          output0 = bot.second.low;
        } else if (bot.second.lowTo == -2) {
          output1 = bot.second.low;
        } else if (bot.second.lowTo == -3) {
          output2 = bot.second.low;
        }

        if (bot.second.highTo >= 0) {
          addNum(bot.second.high, bots[bot.second.highTo]);
          bots[bot.second.highTo].id = bot.second.highTo;
        } else if (bot.second.highTo == -1) {
          output0 = bot.second.high;
        } else if (bot.second.highTo == -2) {
          output1 = bot.second.high;
        } else if (bot.second.highTo == -3) {
          output2 = bot.second.high;
        }

        clearBot(bot.second);
      }
    }
  }

  std::cout << "Multiplication of output chips gives " << (output0 * output1 * output2) << std::endl;
}
