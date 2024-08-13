#include "TaskManager.h"
#include <iostream>

TaskManager::TaskManager() : fileHandler(repository) {
  // Read tasks
  id = fileHandler.readFromFile();
};

void TaskManager::addTask(std::string desc) {
  repository.addTask(Task(++id, desc, false));
}

void TaskManager::completeTask(int id) {
  try {
    repository.getTaskById(id).markAsCompleted();
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

void TaskManager::deleteTask(int id) {
  try {
    repository.deleteTaskById(id);
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

void TaskManager::updateTask(int id, std::string desc) {
  try {
    repository.getTaskById(id).updateDesc(desc);
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

void TaskManager::saveTasks() {
  try {
    fileHandler.writeToFile();
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

// Only for testing
void TaskManager::printTasks() {
  std::cout << "=========================== TODOs "
               "==============================\n";
  if (repository.getSize() == 0) {
    std::cout << "\nNo Tasks available.\n\n";
    std::cout << "==========================================================="
                 "=====\n\n";
    return;
  }

  int idx = 1;
  for (const auto &[id, task] : repository.getTasks()) {
    std::cout << idx << ". " << task.getTaskDesc()
              << "(id: " << task.getTaskId() << ") ";
    std::cout << ((task.isCompleted()) ? "✓" : "✗") << "\n";
    idx++;
  }

  std::cout << "============================================================="
               "===\n\n";
}
