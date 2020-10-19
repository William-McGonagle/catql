#include <iostream>
#include <string>
#include "./parser/objectParser.cpp"
#include "./parser/functionParser.cpp"

int main() {

  std::string modelName;
  command data = parseFunctionFromFile("./mechanim/functions/create-game.cat");

  std::cout << "Command Type: " << data.commandType << std::endl;
  std::cout << "Command Parameters: " << std::endl;

  for(std::string i : data.commandParameters) 
  {

  	std::cout << " - " << i << std::endl;

  } 

  return 0;

}
