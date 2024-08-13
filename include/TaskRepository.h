#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include "Task.h"
#include <unordered_map>

class TaskRepository {
  std::unordered_map<int, Task> tasks;

public:
  TaskRepository();
  TaskRepository(int id);

  int getSize();
  void addTask(Task task);
  std::unordered_map<int, Task> &getTasks();
  Task &getTaskById(int id);
  void deleteTaskById(int id);
};

#endif
