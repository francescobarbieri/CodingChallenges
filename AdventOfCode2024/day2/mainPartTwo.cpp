#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

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
  auto increasing = std::adjacent_find(vec.begin(), vec.end(), std::greater_equal<int>()) == vec.end();
  auto decreasing = std::adjacent_find(vec.begin(), vec.end(), std::less_equal<int>()) == vec.end();

  return increasing || decreasing;
}

bool adiacentsDifferByThreeAtMost(const std::vector<int>& vec) {
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    if (std::abs(vec[i] - vec[i+1]) > 3) {
      return false;
    }
  }
  return true;
}

bool adiacentDifferByThreeAtMostWithTolerance(const std::vector<int>& vec) {
  for(size_t i = 0; i < static_cast<int>(vec.size()); ++i) {
    std::vector<int> temp(vec);
    temp.erase(temp.begin() + i);

    if(adiacentsDifferByThreeAtMost(temp)) {
      return true;
    }
  }
  return false;
}

bool isMonotonicWithTolerance(const std::vector<int>& vec) {
  for(size_t i = 0; i < vec.size(); ++i) {
    std::vector<int> temp(vec);
    temp.erase(temp.begin() + i);

    if(isMonotonic(temp)) {
      return true;
    }
  }
  return false;
}

int main() {
  std::vector<std::vector<int> > matrix = readReportsFromFile();
  int safeReports = 0;
  std::ofstream outputFile("unsafe.txt");

  for(size_t i = 0; i < matrix.size(); ++i) {
    if(isMonotonicWithTolerance(matrix[i]) && adiacentDifferByThreeAtMostWithTolerance(matrix[i])) {
      ++safeReports;
    } else {
      for (const auto& j : matrix[i]) {
        outputFile << j << ' ';
      }
      outputFile << std::endl;
    }
  }
  outputFile.close();

  std::cout << "The number of safe reports is: " << safeReports << std::endl;

  return 1;
}