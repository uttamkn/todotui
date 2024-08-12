#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "TaskFileHandler.h"
#include <iostream>

class TaskManager : public TaskFileHandler {
  int id;

public:
  TaskManager();

  // User Interface for the console (only for testing)
  void console_ui();

private:
  void addTask(std::string desc);
  void completeTask(int id);
  void deleteTask(int id);
  void updateTask(int id, std::string desc);
  void printTasks();
};
#endif
