#include <iostream>
#include <map>
#include <string>

class Task {
  int id;
  int priority;
  std::string desc;

public:
  Task(int id, int priority, std::string desc)
      : id(id), priority(priority), desc(desc) {}

public:
  int getPriority() { return priority; }
  int getId() { return id; }
  std::string getTask() { return desc; }
};

class ManageTasks {
  std::map<int, Task> tasks;
  int id;

  // Constructor
  ManageTasks() : id(0) {
    // TODO: import all tasks from the saved file
  }

  void addTask(std::string desc, int priority = -1) {
    Task task(id++, priority, desc);
    tasks[task.getId()] = task;
    // TODO: Save all tasks in a file
  }

  void displayTasks() {
    std::cout
        << "=========================== TODOs ==============================\n";
    if (tasks.size() == 0) {
      std::cout << "None.\n";
      return;
    }

    for (std::pair<int, Task> task : tasks) {
      std::cout << task.first << ". " << task.second.getTask() << "\n";
    }

    std::cout
        << "================================================================\n";
  }

public:
  // User interface
  void ui() {
    using namespace std;

    displayTasks();

    while (true) {
      // TODO: Add update functionality
      cout << "Options: a - add a task\td - mark a task as completed\n";
      char choice;
      cin >> choice;

      switch (choice) {
      case 'a': {
        string taskDesc;
        char priority;

        cout << "Enter the task description: ";
        cin >> taskDesc;
        cout << "Priority(optional): ";
      }
      }
    }
  }
};

int main() { return 0; }
