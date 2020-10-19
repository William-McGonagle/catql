#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <string>

struct command {

  std::string commandType;
  std::vector<std::string> commandParameters;

};


// Command Parses
bool parseInsert(std::string data, command & returnValue) {

  int state = 0;
  bool writing = true;
  std::vector<std::string> parameters;
  parameters.push_back("");
  parameters.push_back("");

  for (int i = 0; i < data.length(); ++i)
  {

    if (data[i] == '(') {

      writing = false;
      break;

    }

    if (data[i] == ')') { 

      writing = true; 
      break;

    }

    if (writing) {

      switch (state) {

        case 0:

          if (data[i] == ' ') state = 1;

          break;

        case 1:

          if (data[i] == ' ') {
          
            state = 2;
          
          }
          else {

            parameters[0] += data[i];
          
          }

          break;

        case 2:

          if (data[i] == ' ') state = 3;

          break;

        case 3:

          if (data[i] == ' ') {

            return true;
          
          }
          else {
          
            parameters[1] += data[i];
          
          }

          break;

      }

    }

  }

  if (parameters[1][0] == '$') {

    parameters[1] = "VAR_" + parameters[1].substr(1, parameters[1].length());

  }

  returnValue.commandParameters = parameters;

  return true;

}



bool parseFunction(std::string data, command & returnValue) {

  std::string curCommand;

  for (int i = 0; i < data.length(); i++) {

    if (data[i] == ' ')
      break;
    else
      curCommand += data[i];
        
  }

  returnValue.commandType = curCommand;

  std::map<std::string, int> commandMap;
  commandMap["INSERT_INTO"] = 0;

  switch (commandMap[curCommand]) {

    case 0:
      return parseInsert(data, returnValue);

  }

  return false;

}

command parseFunctionFromFile(std::string path) {

  std::string parseText;
  std::string buffer;
  std::ifstream modelFile(path);

  while (getline (modelFile, buffer)) {

    parseText += buffer;

  }

  modelFile.close();

  parseText = std::regex_replace(parseText, std::regex("\n"), "");

  command output;
  parseFunction(parseText, output);
  return output;

}
