#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <string>

std::map<std::string, std::string> parseModel(std::string data, std::string & objectName) {

  std::map<std::string, std::string> output;
  std::string level = "";
  std::string label = "";
  std::string value = "";

  int state = 0;

  for (int i = 0; i < data.length(); i++) {

    switch (state) {
      case 0:

        if (data[i] == ':') {

          state = 1;
          i++;

        }
        else {

          objectName += data[i];

        }

        break;
      case 1:

        if (data[i] == ':') {

          state = 2;

        } else if (data[i] == ',') {



        } else if (data[i] == '}') {

          if (label != "" && value != "") output[level + label] = value;

          std::string temp = level.substr(0, level.length() - 1);
          size_t tempPos = temp.find_last_of('.');

          if (tempPos != std::string::npos) {

            level = level.substr(0, tempPos - 1);

          } else {

            level = "";

          }

          label = "";
          value = "";

          state = 1;

        }
        else {

          label += data[i];

        }
        break;
      case 2:

        if (data[i] == ',') {

          state = 1;

          if (label != "" && value != "") output[level + label] = value;

          label = "";
          value = "";

        } else if (data[i] == '{') {

          // Level Increase
          level += label + '.';

          label = "";
          value = "";

          state = 1;

        }
        else if (data[i] == '}') {

          if (label != "" && value != "") output[level + label] = value;

          std::string temp = level.substr(0, level.length() - 1);
          size_t tempPos = temp.find_last_of('.');

          if (tempPos != std::string::npos) {

            level = level.substr(0, tempPos - 1);

          } else {

            level = "";

          }

          label = "";
          value = "";

          state = 1;

       }
        else {

          value += data[i];

        }

        break;
    }

  }

  return output;

}

std::map<std::string, std::string> parseModelFromFile(std::string path, std::string & objectName) {

  std::string parseText;
  std::string buffer;
  std::ifstream modelFile(path);

  while (getline (modelFile, buffer)) {

    parseText += buffer;

  }

  modelFile.close();

  parseText = std::regex_replace(parseText, std::regex(" "), "");
  parseText = std::regex_replace(parseText, std::regex("\n"), "");

  return parseModel(parseText, objectName);

}
