#ifndef TASKFILEHANDLER_H
#define TASKFILEHANDLER_H

#include "Task.h"
#include <fstream>
#include <unordered_map>

class TaskFileHandler {
  std::fstream todo_data;
  const char *home = std::getenv("HOME");
  std::string filepath = std::string(home) + "/.cache/todo_data.csv";

protected:
  std::unordered_map<int, Task> tasks;
  static TaskFileHandler *instance;

  int readFromFile();
  void writeToFile();

public:
  TaskFileHandler();

  // Signal handler
  static void handleSignal(int signal);
};

#endif
