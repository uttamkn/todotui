#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <string>

class TaskManager {
  int id;

public:
  TaskManager();
  void addTask(std::string desc);
  void completeTask(int id);
  void deleteTask(int id);
  void updateTask(int id, std::string desc);
  void saveTasks();
  void printTasks();

  // Signal handler
  static void handleSignal(int signal);
};
#endif
