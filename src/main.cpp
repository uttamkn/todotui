#include <iostream>
#include <string>
#include <vector>
class Task {
  int id;
  std::string desc;

public:
  Task(int id, std::string desc) : id(id), desc(desc) {}

public:
  int getId() { return id; }
  std::string getTask() { return desc; }
};

class ManageTasks {
  // TODO: try using a map instead of a vector
  std::vector<Task> tasks;
  int id;

  void addTask(std::string desc) {
    Task task(id++, desc);
    tasks.push_back(task);
    std::cout << "\n\nTask added\n\n\n";
    // TODO: Save all tasks in a file
  }

  void deleteTask(int id) {
    int i = 0;
    for (Task task : tasks) {
      if (task.getId() == id) {
        tasks.erase(tasks.begin() + i);
        std::cout << "\n\nTask deleted\n\n\n";
        return;
      }
      i++;
    }
    std::cout << "\n\nTask not found\n\n\n";
  }

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
      std::cout << idx << ". " << task.getTask() << "(id: " << task.getId()
                << ")"
                << "\n";
      idx++;
    }

    std::cout << "============================================================="
                 "===\n\n";
  }

public:
  // Constructor
  ManageTasks() : id(0) {
    // TODO: import all tasks from the saved file
  }

  // User interface
  void ui() {
    using namespace std;

    while (true) {
      // TODO: Add update functionality
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
        string id_str;
        int id;
        cout << "Enter the task id u want to delete: ";
        getline(cin, id_str);

        try {
          id = stoi(id_str);
        } catch (exception &ex) {
          cout << "\n\nInvalid id\n\n\n";
          continue;
        }

        deleteTask(id);
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
};

int main() {
  ManageTasks myTasks;
  myTasks.ui();
  return 0;
}
