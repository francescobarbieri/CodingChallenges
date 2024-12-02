#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

std::vector<std::vector<int> > readReportsFromFile() {
  std::fstream inputFile("input.txt");
  std::string line;
  std::vector<std::vector<int> > matrix;

  if(inputFile.is_open()) {
    while(getline(inputFile, line)) {
      std::vector<int> row;
      std::istringstream iss(line);
      int value;

      while(iss >> value) {
        row.push_back(value);       
      }

      matrix.push_back(row);
    }
    inputFile.close();
  } else {
    std::cerr << "Unable to open file" << std::endl;
  }
  return matrix;
}

bool isMonotonic(const std::vector<int>& vec) {
  if(vec.size()  <= 2 ) return true;

  auto increasing = std::adjacent_find(vec.begin(), vec.end(), std::greater_equal<int>()) == vec.end();
  auto decreasing = std::adjacent_find(vec.begin(), vec.end(), std::less_equal<int>()) == vec.end();

  return increasing || decreasing;
}

bool adiacentsDifferByThreeAtMost(const std::vector<int>& vec) {
  if(vec.size()  <= 2 ) return true;

  for(int i = 0; i < vec.size() - 1; ++i) {
    if(std::abs(vec[i] - vec[i+1]) > 3) {
      return false;
    }
  }
  return true;
}

int main() {
  std::vector<std::vector<int> > matrix = readReportsFromFile();
  int safeReports = 0;

  for(int i = 0; i < matrix.size(); ++i) {
    if(isMonotonic(matrix[i]) && adiacentsDifferByThreeAtMost(matrix[i])) {
      ++safeReports;
    }
  }

  std::cout << "The number of safe reports is: " << safeReports << std::endl;

  return 1;
}