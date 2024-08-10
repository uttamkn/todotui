#include <iostream>
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
    return std::to_string(getTaskId()).append(" ").append(getTaskDesc());
  }
};

class ManageTasks {
  // TODO: Use hashmap instead of a vector
  std::vector<Task> tasks;
  static int id;

public:
  // Constructor
  // TODO: Save all tasks in a file
  ManageTasks() {}

  // User Interface for the console
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
        cout << "exiting...\n";
        return;
      }

      default: {
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
    // addTaskToFile()
    std::cout << "\n\nTask added\n\n\n";
  }

  void deleteTask(int id) {
    int i = 0;
    for (Task task : tasks) {
      if (task.getTaskId() == id) {
        tasks.erase(tasks.begin() + i);
        // deleteTaskFromFile()
        std::cout << "\n\nTask deleted\n\n\n";
        return;
      }
      i++;
    }
    std::cout << "\n\nTask not found\n\n\n";
  }

  // TODO: Add update functionality

  void displayTasks() {
    std::cout
        << "=========================== TODOs ==============================\n";
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

int ManageTasks::id = 0;

int main() {
  ManageTasks myTasks;
  myTasks.console_ui();
  return 0;
}
