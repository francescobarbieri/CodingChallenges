#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

std::vector<std::string> splitString(std::string& s, char delimiter, bool ignoreEmpty) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);

  while (std::getline(tokenStream, token, delimiter)) {
      if (!token.empty() || !ignoreEmpty) {
          tokens.push_back(token);
      }
  }

  // Handle the case where the string ends with the delimiter
  if (s.back() == delimiter && !ignoreEmpty) {
      tokens.push_back("");
  }

  return tokens;
}


int main() {
  ifstream inputFile("input.txt");
  string readLine;
  std::multiset<int> leftList;
  std::multiset<int> rightList;
  int sumOfAllDistances;

  if(inputFile.is_open()) {
    while(getline(inputFile, readLine)) {
      auto parts = splitString(readLine, ' ', true);
      leftList.insert(stoi(parts[0]));
      rightList.insert(stoi(parts[1]));
    }
    inputFile.close();
  } else {
    cerr << "Unable to open file" << endl;
  }

  auto it1 = leftList.begin();
  auto it2 = rightList.begin();

  for(; it1 != leftList.end(); it1++, it2++) {
    sumOfAllDistances += abs(*it1 - *it2);
  }

  cout << "Sum of all distances: " << sumOfAllDistances << "\n";

  return 1;
}