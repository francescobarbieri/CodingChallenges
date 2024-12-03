#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

int main() {
  std::regex pattern("mul\\((\\d{1}|\\d{2}|\\d{3}),(\\d{1}|\\d{2}|\\d{3})\\)");
  
  std::fstream inputFile("input.txt");
  std::string text;

  int sum = 0;

  if(inputFile.is_open()) {
    while(getline(inputFile, text)) {
      auto words_begin = std::sregex_iterator(text.begin(), text.end(), pattern);
      auto words_end = std::sregex_iterator();

      for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        
        if(match.size() == 3) {
          try {
            int num1 = std::stoi(match[1].str());
            int num2 = std::stoi(match[2].str());

            int result = num1 * num2;
            sum += result;
          } catch (const std::invalid_argument& e) {
            std::cout << "Invalid number format: " << e.what() << std::endl;
          } catch (const std::out_of_range& e) {
            std::cout << "Number out of range: " << e.what() << std::endl;
          }
        }
      }
    }
  } 
  
  std::cout << "Result: " << sum << std::endl;

  return 1;
}