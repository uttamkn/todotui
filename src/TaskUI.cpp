#include "TaskUI.h"
#include <iostream>

TaskUI::TaskUI() : taskManager() {}

void TaskUI::consoleUI() {
  while (true) {
    taskManager.printTasks();

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
      taskManager.addTask(taskDesc);
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

      taskManager.completeTask(input_id);
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

      taskManager.deleteTask(input_id);
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

      taskManager.updateTask(input_id, input_desc);
    } break;

    case 'q': {
      taskManager.saveTasks();
      std::cout << "\nExiting...\n";
      return;
    }

    default: {
      taskManager.saveTasks();
      std::cout << "\nInvalid input. Exiting...\n";
      return;
    }
    }
  }
}
