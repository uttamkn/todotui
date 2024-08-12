#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Task {
  int id;
  std::string desc;
  bool completed;

public:
  Task(int id, std::string desc, bool completed)
      : id(id), desc(desc), completed(completed) {}

  int getTaskId() const { return id; }
  std::string getTaskDesc() const { return desc; }
  bool isCompleted() const { return completed; }
  std::string getTaskCsv() const {
    return std::to_string(id).append(",").append(desc).append(",").append(
        std::to_string(int(completed)));
  }

  void setComplete() { this->completed = true; }
  void updateDesc(std::string desc) { this->desc = desc; }
};

class TaskFile {
  // TODO: Switch to json
  std::fstream todo_data;
  const char *home = std::getenv("HOME");
  std::string filepath = std::string(home) + "/.cache/todo_data.csv";

protected:
  std::vector<Task> tasks;

  int readFromFile() {
    todo_data.open(filepath, std::ios::in);
    std::string line;
    int id = 0;
    while (getline(todo_data, line)) {
      std::string desc;
      bool completed;

      // extract id, desc and completed status
      std::istringstream iss(line);

      std::string id_str;
      getline(iss, id_str, ',');
      id = std::stoi(id_str);

      getline(iss, desc, ',');

      std::string completed_str;
      getline(iss, completed_str, ',');
      completed = (completed_str == "1") ? true : false;

      Task task(id, desc, completed);
      tasks.push_back(task);
    }
    todo_data.close();

    // return the last id
    return id;
  }

  void writeToFile() {
    // Replace old file
    todo_data.open(filepath, std::ios::out);

    for (const Task task : tasks) {
      todo_data << task.getTaskCsv() << "\n";
    }

    todo_data.close();
  }

  static TaskFile *instance;

public:
  // Signal handler
  static void handleSignal(int signal) {
    instance->writeToFile();
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
  ManageTasks() { id = readFromFile(); }

  // User Interface for the console (only for testing)
  void console_ui() {
    using namespace std;

    while (true) {
      displayTasks();

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

private:
  void addTask(std::string desc) {
    Task task(++id, desc, false);
    tasks.push_back(task);
    std::cout << "\n\nTask added\n\n\n";
  }

  void completeTask(int id) {
    for (Task &task : tasks) {
      if (task.getTaskId() == id) {
        task.setComplete();
        std::cout << "\n\nTask completed\n\n\n";
        return;
      }
    }
    std::cout << "\n\nTask not found\n\n\n";
  }

  void deleteTask(int id) {
    int i = 0;
    for (Task &task : tasks) {
      if (task.getTaskId() == id) {
        tasks.erase(tasks.begin() + i);
        std::cout << "\n\nTask deleted\n\n\n";
        return;
      }
      i++;
    }
    std::cout << "\n\nTask not found\n\n\n";
  }

  void updateTask(int id, std::string desc) {
    for (Task &task : tasks) {
      if (task.getTaskId() == id) {
        task.updateDesc(desc);
        std::cout << "\n\nTask updated\n\n\n";
        return;
      }
    }
    std::cout << "\n\nTask not found\n\n\n";
  }

  void displayTasks() {
    std::cout << "=========================== TODOs "
                 "==============================\n";
    if (tasks.size() == 0) {
      std::cout << "\nNo Tasks available.\n\n";
      std::cout << "==========================================================="
                   "=====\n\n";
      return;
    }

    int idx = 1;
    for (Task task : tasks) {
      std::cout << idx << ". " << task.getTaskDesc()
                << "(id: " << task.getTaskId() << ") ";
      std::cout << ((task.isCompleted()) ? "✓" : "✗") << "\n";
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
