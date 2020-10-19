#include <iostream>
#include <string>
#include "./parser/objectParser.cpp"

int main() {

  std::string modelName;
  std::map<std::string, std::string> data = parseModelFromFile("./mechanim/objects/user.shango", modelName);

  std::cout << "Model Name: " << modelName << std::endl;

  for (const auto& [key, value] : data) {

    std::cout << key << " = " << value << std::endl;

  }

  return 0;

}
