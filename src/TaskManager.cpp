#include "TaskManager.h"
#include <iostream>

TaskManager::TaskManager() : id(readFromFile()) {}

void TaskManager::addTask(std::string desc) {
  tasks[id] = Task(++id, desc, false);
  std::cout << "\n\nTask added\n\n\n";
}

void TaskManager::completeTask(int id) {
  const auto it = tasks.find(id);

  if (it == tasks.end()) {
    std::cout << "\n\nTask not found\n\n\n";
    return;
  }

  it->second.markAsCompleted();
}

void TaskManager::deleteTask(int id) {
  const auto it = tasks.find(id);

  if (it == tasks.end()) {
    std::cout << "\n\nTask not found\n\n\n";
    return;
  }

  tasks.erase(it);
}

void TaskManager::updateTask(int id, std::string desc) {
  const auto it = tasks.find(id);

  if (it == tasks.end()) {
    std::cout << "\n\nTask not found\n\n\n";
    return;
  }

  it->second.updateDesc(desc);
}

// Only for testing
void TaskManager::printTasks() {
  std::cout << "=========================== TODOs "
               "==============================\n";
  if (tasks.size() == 0) {
    std::cout << "\nNo Tasks available.\n\n";
    std::cout << "==========================================================="
                 "=====\n\n";
    return;
  }

  int idx = 1;
  for (const auto &[id, task] : tasks) {
    std::cout << idx << ". " << task.getTaskDesc()
              << "(id: " << task.getTaskId() << ") ";
    std::cout << ((task.isCompleted()) ? "✓" : "✗") << "\n";
    idx++;
  }

  std::cout << "============================================================="
               "===\n\n";
}

void TaskManager::console_ui() {

  while (true) {
    printTasks();

    std::cout << "=========================== Options "
                 "===========================\n";
    std::cout << "a - Add a task\n";
    std::cout << "c - Mark a task as completed\n";
    std::cout << "d - Delete a task\n";
    std::cout << "u - Update a task\n";
    std::cout << "q - Quit\n";
    std::cout
        << "==============================================================="
           "\n";
    std::cout << "Please enter your choice: ";

    std::string choice;
    getline(std::cin, choice);
    switch (choice[0]) {
    case 'a': {
      std::string taskDesc;
      std::cout << "\nEnter the task description: ";
      getline(std::cin, taskDesc);
      addTask(taskDesc);
      std::cout << "\nTask added successfully.\n\n";
    } break;

    case 'c': {
      std::string input_id_str;
      int input_id;
      std::cout << "\nEnter the task id u want to mark as completed: ";
      getline(std::cin, input_id_str);

      try {
        input_id = stoi(input_id_str);
      } catch (std::exception &ex) {
        std::cout << "\nInvalid id. Please enter a valid numeric id.\n\n";
        continue;
      }

      completeTask(input_id);
    } break;

    case 'd': {
      std::string input_id_str;
      int input_id;
      std::cout << "\nEnter the task id u want to delete: ";
      getline(std::cin, input_id_str);

      try {
        input_id = stoi(input_id_str);
      } catch (std::exception &ex) {
        std::cout << "\nInvalid id. Please enter a valid numeric id.\n\n";
        continue;
      }

      deleteTask(input_id);
    } break;

    case 'u': {
      std::string input_id_str;
      int input_id;
      std::string input_desc;
      std::cout << "\nEnter the task id u want to update: ";
      getline(std::cin, input_id_str);
      std::cout << "Enter the new description: ";
      getline(std::cin, input_desc);

      try {
        input_id = stoi(input_id_str);
      } catch (std::exception &ex) {
        std::cout << "\nInvalid id. Please enter a valid numeric id.\n\n";
        continue;
      }

      updateTask(input_id, input_desc);
    } break;

    case 'q': {
      writeToFile();
      std::cout << "\nExiting...\n";
      return;
    }

    default: {
      writeToFile();
      std::cout << "\nInvalid input. Exiting...\n";
      return;
    }
    }
  }
}
