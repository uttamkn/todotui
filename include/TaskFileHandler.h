#ifndef TASKFILEHANDLER_H
#define TASKFILEHANDLER_H

#include <fstream>

class TaskFileHandler {
  std::fstream todo_data;
  const char *home = std::getenv("HOME");
  std::string filepath = std::string(home) + "/.cache/todo_data.json";

public:
  TaskFileHandler();

  static TaskFileHandler *getInstance();
  int readFromFile();
  void writeToFile();
};
#endif
