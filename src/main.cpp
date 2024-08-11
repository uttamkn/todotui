#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Task {
  int id;
  std::string desc;

public:
  Task(int id, std::string desc) : id(id), desc(desc) {}
  int getTaskId() const { return id; }
  std::string getTaskDesc() const { return desc; }
  std::string getTask() const {
    return std::to_string(id).append(" ").append(desc);
  }
};

class TaskFile {
  std::fstream todo_data;
  const char *home = std::getenv("HOME");
  std::string filepath = std::string(home) + "/.cache/todo_data.txt";

protected:
  std::vector<Task> tasks;
  // TODO: Figure out a way to add unique id to tasks (its not unique right now)

  void readTasksFromFile() {
    todo_data.open(filepath, std::ios::in);
    std::string line;
    while (getline(todo_data, line)) {
      int id;
      std::string desc;

      // extract id and desc
      std::istringstream iss(line);
      iss >> id;
      std::getline(iss, desc);
      if (!desc.empty() && desc[0] == ' ') {
        desc.erase(desc.begin());
      }

      Task task(id, desc);
      tasks.push_back(task);
    }
    todo_data.close();
  }

  void saveTasksToFile() {
    // Replace old file
    todo_data.open(filepath, std::ios::out);

    for (const Task task : tasks) {
      todo_data << task.getTask() << "\n";
    }

    todo_data.close();
  }

  static TaskFile *instance;

public:
  // Signal handler
  static void handleSignal(int signal) {
    instance->saveTasksToFile();
    std::exit(signal);
  }

  TaskFile() { instance = this; }
};

TaskFile *TaskFile::instance = nullptr;

class ManageTasks : public TaskFile {
  // TODO: Use hashmap instead of a vector
  int id;

public:
  // Constructor
  ManageTasks() {
    readTasksFromFile();
    id = tasks.size();
  }

  // User Interface for the console (only for testing)
  void console_ui() {
    using namespace std;

    while (true) {
      displayTasks();
      cout << "Options: a - add a task\t\td - mark a task as completed\t\tq - "
              "quit\n";
      string choice;
      getline(cin, choice);
      switch (choice[0]) {
      case 'a': {
        string taskDesc;
        cout << "Enter the task description: ";
        getline(cin, taskDesc);
        addTask(taskDesc);
      } break;

      case 'd': {
        string input_id_str;
        int input_id;
        cout << "Enter the task id u want to delete: ";
        getline(cin, input_id_str);

        try {
          input_id = stoi(input_id_str);
        } catch (exception &ex) {
          cout << "\n\nInvalid id\n\n\n";
          continue;
        }

        deleteTask(input_id);
      } break;

      case 'q': {
        saveTasksToFile();
        cout << "exiting...\n";
        return;
      }

      default: {
        saveTasksToFile();
        cout << "invalid input....exiting\n";
        return;
      }
      }
    }
  }

private:
  void addTask(std::string desc) {
    Task task(id++, desc);
    tasks.push_back(task);
    std::cout << "\n\nTask added\n\n\n";
  }

  void deleteTask(int id) {
    int i = 0;
    for (Task task : tasks) {
      if (task.getTaskId() == id) {
        tasks.erase(tasks.begin() + i);
        std::cout << "\n\nTask deleted\n\n\n";
        return;
      }
      i++;
    }
    std::cout << "\n\nTask not found\n\n\n";
  }

  // TODO: Add update functionality

  void displayTasks() {
    std::cout << "=========================== TODOs "
                 "==============================\n";
    if (tasks.size() == 0) {
      std::cout << "\nNone.\n\n";
      std::cout << "==========================================================="
                   "=====\n\n";
      return;
    }

    int idx = 1;
    for (Task task : tasks) {
      std::cout << idx << ". " << task.getTaskDesc()
                << "(id: " << task.getTaskId() << ")"
                << "\n";
      idx++;
    }

    std::cout << "============================================================="
                 "===\n\n";
  }
};

int main() {
  ManageTasks myTasks;
  std::signal(SIGINT, TaskFile::handleSignal);
  myTasks.console_ui();
  return 0;
}
