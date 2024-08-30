#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include "Task.h"
#include <unordered_map>

class TaskRepository {
  std::unordered_map<int, Task> tasks;

public:
  TaskRepository();

  static TaskRepository *getInstance();
  int getSize();
  void addTask(const Task &task);
  std::unordered_map<int, Task> &getTasks();
  Task &getTaskById(int id);
  void deleteTaskById(int id);
};

#endif
