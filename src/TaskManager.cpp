#include "TaskManager.h"

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
  for (const auto &task : tasks) {
    std::cout << idx << ". " << task.second.getTaskDesc()
              << "(id: " << task.second.getTaskId() << ") ";
    std::cout << ((task.second.isCompleted()) ? "✓" : "✗") << "\n";
    idx++;
  }

  std::cout << "============================================================="
               "===\n\n";
}

// Only for testing
void TaskManager::console_ui() {
  using namespace std;

  while (true) {
    printTasks();

    cout << "=========================== Options "
            "===========================\n";
    cout << "a - Add a task\n";
    cout << "c - Mark a task as completed\n";
    cout << "d - Delete a task\n";
    cout << "u - Update a task\n";
    cout << "q - Quit\n";
    cout << "==============================================================="
            "\n";
    cout << "Please enter your choice: ";

    string choice;
    getline(cin, choice);
    switch (choice[0]) {
    case 'a': {
      string taskDesc;
      cout << "\nEnter the task description: ";
      getline(cin, taskDesc);
      addTask(taskDesc);
      cout << "\nTask added successfully.\n\n";
    } break;

    case 'c': {
      string input_id_str;
      int input_id;
      cout << "\nEnter the task id u want to mark as completed: ";
      getline(cin, input_id_str);

      try {
        input_id = stoi(input_id_str);
      } catch (exception &ex) {
        cout << "\nInvalid id. Please enter a valid numeric id.\n\n";
        continue;
      }

      completeTask(input_id);
    } break;

    case 'd': {
      string input_id_str;
      int input_id;
      cout << "\nEnter the task id u want to delete: ";
      getline(cin, input_id_str);

      try {
        input_id = stoi(input_id_str);
      } catch (exception &ex) {
        cout << "\nInvalid id. Please enter a valid numeric id.\n\n";
        continue;
      }

      deleteTask(input_id);
    } break;

    case 'u': {
      string input_id_str;
      int input_id;
      string input_desc;
      cout << "\nEnter the task id u want to update: ";
      getline(cin, input_id_str);
      cout << "Enter the new description: ";
      getline(cin, input_desc);

      try {
        input_id = stoi(input_id_str);
      } catch (exception &ex) {
        cout << "\nInvalid id. Please enter a valid numeric id.\n\n";
        continue;
      }

      updateTask(input_id, input_desc);
    } break;

    case 'q': {
      writeToFile();
      cout << "\nExiting...\n";
      return;
    }

    default: {
      writeToFile();
      cout << "\nInvalid input. Exiting...\n";
      return;
    }
    }
  }
}
