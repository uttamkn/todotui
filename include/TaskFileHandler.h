#ifndef TASKFILEHANDLER_H
#define TASKFILEHANDLER_H

#include "TaskRepository.h"
#include <fstream>

class TaskFileHandler {
  std::fstream todo_data;
  const char *home = std::getenv("HOME");
  std::string filepath = std::string(home) + "/.cache/todo_data.json";
  TaskRepository &repository;

public:
  TaskFileHandler(TaskRepository &repository);
  static TaskFileHandler *instance;

  int readFromFile();
  void writeToFile();

  // Signal handler
  static void handleSignal(int signal);
};
#endif
