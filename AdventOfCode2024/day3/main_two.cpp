#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

int evaluateMultiplication (std::smatch match) {
  if(match.size() == 3) {
    try {
      int num1 = std::stoi(match[1].str());
      int num2 = std::stoi(match[2].str());
      return num1 * num2;
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid number format: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Number out of range: " << e.what() << std::endl;
    }
  }
}


int main() {
  std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)");  
  std::fstream inputFile("input.txt");
  std::string text;
  int sum = 0;

  if(inputFile.is_open()) {
    while(getline(inputFile, text)) {
      auto words_begin = std::sregex_iterator(text.begin(), text.end(), pattern);
      auto words_end = std::sregex_iterator();
      bool flag = true;

      for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;

        if(match[0] == "do()") {
          flag = true;
        } else if (match[0] == "don't()") {
          flag = false;
        }
        if(flag && match[0] != "do()" && match[0] != "don't()") {
          sum += evaluateMultiplication(match);
        }
      }
    }
  } 
  
  std::cout << "Result: " << sum << std::endl;
  return 1;
}