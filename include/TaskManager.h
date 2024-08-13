#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "TaskFileHandler.h"
#include "TaskRepository.h"

class TaskManager {
  int id;
  TaskRepository repository;
  TaskFileHandler fileHandler;

public:
  TaskManager();
  void addTask(std::string desc);
  void completeTask(int id);
  void deleteTask(int id);
  void updateTask(int id, std::string desc);
  void saveTasks();
  void printTasks();
};
#endif
