#include "TaskFileHandler.h"
#include <iostream>
#include <sstream>

// Initialize static member
TaskFileHandler *TaskFileHandler::instance = nullptr;

TaskFileHandler::TaskFileHandler() { instance = this; }

int TaskFileHandler::readFromFile() {
  todo_data.open(filepath, std::ios::in);

  if (!todo_data) {
    std::cerr << "Error opening file\n";
    return -1;
  }

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

    tasks[id] = Task(id, desc, completed);
  }
  todo_data.close();

  // return the last id
  return id;
}

void TaskFileHandler::writeToFile() {
  // Replace old file
  todo_data.open(filepath, std::ios::out);

  if (!todo_data) {
    std::cerr << "Error opening file\n";
    return;
  }

  for (const auto &[id, task] : tasks) {
    todo_data << task.getTaskCsv() << "\n";
  }

  todo_data.close();
}

// Signal handler
void TaskFileHandler::handleSignal(int signal) {
  instance->writeToFile();
  std::exit(signal);
}
