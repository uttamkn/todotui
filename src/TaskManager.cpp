#include "TaskManager.h"
#include "TaskFileHandler.h"
#include "TaskRepository.h"
#include <iostream>

TaskManager::TaskManager() {
  // Read tasks
  id = TaskFileHandler::getInstance()->readFromFile();
};

void TaskManager::addTask(std::string desc) {
  TaskRepository::getInstance()->addTask(Task(++id, desc, false));
  // Save tasks
  saveTasks();
}

void TaskManager::completeTask(int id) {
  try {
    TaskRepository::getInstance()->getTaskById(id).markAsCompleted();
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

void TaskManager::deleteTask(int id) {
  try {
    TaskRepository::getInstance()->deleteTaskById(id);
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

void TaskManager::updateTask(int id, std::string desc) {
  try {
    TaskRepository::getInstance()->getTaskById(id).updateDesc(desc);
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

void TaskManager::saveTasks() {
  try {
    TaskFileHandler::getInstance()->writeToFile();
  } catch (std::exception &ex) {
    std::cout << ex.what() << "\n";
  }
}

// Only for testing
void TaskManager::printTasks() {
  std::cout << "=========================== TODOs "
               "==============================\n";
  if (TaskRepository::getInstance()->getSize() == 0) {
    std::cout << "\nNo Tasks available.\n\n";
    std::cout << "==========================================================="
                 "=====\n\n";
    return;
  }

  int idx = 1;
  for (const auto &[id, task] : TaskRepository::getInstance()->getTasks()) {
    std::cout << idx << ". " << task.getTaskDesc()
              << "(id: " << task.getTaskId() << ") ";
    std::cout << ((task.isCompleted()) ? "✓" : "✗") << "\n";
    idx++;
  }

  std::cout << "============================================================="
               "===\n\n";
}

// Signal handler
void TaskManager::handleSignal(int signal) {
  TaskFileHandler::getInstance()->writeToFile();
  std::exit(signal);
}
