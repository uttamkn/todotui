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

  int readTasksFromFile() {
    todo_data.open(filepath, std::ios::in);
    std::string line;
    int id = 0;
    while (getline(todo_data, line)) {
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

    // return the last id
    return id;
  }

  void writeTasksToFile() {
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
    instance->writeTasksToFile();
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
  ManageTasks() { id = readTasksFromFile(); }

  // User Interface for the console (only for testing)
  void console_ui() {
    using namespace std;

    while (true) {
      displayTasks();
      cout << "=========================== Options "
              "===========================\n";
      cout << "a - Add a task\n";
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
        writeTasksToFile();
        cout << "\nExiting...\n";
        return;
      }

      default: {
        writeTasksToFile();
        cout << "\nInvalid input. Exiting...\n";
        return;
      }
      }
    }
  }

private:
  void addTask(std::string desc) {
    Task task(++id, desc);
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

  void updateTask(int id, std::string desc) {
    Task newTask(id, desc);
    int i = 0;
    for (Task task : tasks) {
      if (task.getTaskId() == id) {
        tasks[i] = newTask;
        std::cout << "\n\nTask updated\n\n\n";
        return;
      }
      i++;
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
