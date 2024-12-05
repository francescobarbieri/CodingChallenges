#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <fstream>

std::pair<int, int> parseRule(std::string& line) {
  size_t delimiterPos = line.find('|');

  int firstPart = std::stoi(line.substr(0, delimiterPos));
  int secondPart = std::stoi(line.substr(delimiterPos + 1));

  return std::make_pair(firstPart, secondPart);
}

std::vector<int> parseStringToIntVector(const std::string& input) {
  std::vector<int> result;
  std::stringstream ss(input);
  std::string item;

  while (std::getline(ss, item, ',')) {
    try {
        result.push_back(std::stoi(item));
    } catch (const std::invalid_argument& e) {
      std::cerr << "Invalid number format: " << item << std::endl;
    } catch (const std::out_of_range& e) {
      std::cerr << "Number out of range: " << item << std::endl;
    }
  }

  return result;
}

int main() {
  std::fstream file("input.txt");
  std::string line;
  std::map<int, std::set<int> > rules;
  std::vector<std::vector<int> > pageLists;
  int readingRules = true;
  int part1 = 0;
  int part2 = 0;

  if(file.is_open()) {
    while(getline(file, line)) {
      if(line.empty()) {
        readingRules = false;
      }

      if(readingRules) {
        std::pair<int, int> tempParse = parseRule(line);
        rules[tempParse.first].insert(tempParse.second);
      } else {
        pageLists.push_back(parseStringToIntVector(line));
      }
    }
  }

  auto comp = [&rules](int a, int b) {
    return rules[a].find(b) != rules[a].end();
  };

  for (std::vector<int> v : pageLists) {
    if(v.size() > 1){
      if(std::is_sorted(v.begin(), v.end(), comp))  {
        part1 += v[(v.size() - 1) / 2];
      } else {
        std::sort(v.begin(), v.end(), comp);
        part2 += v[(v.size() - 1) / 2];
      }
    }
  }

  std::cout << part1 << std::endl;
  std::cout << part2 << std::endl;

  return 1;
}