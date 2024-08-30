#include "TaskFileHandler.h"
#include "TaskRepository.h"
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Singleton
TaskFileHandler *TaskFileHandler::getInstance() {
  static TaskFileHandler instance;
  return &instance;
}

TaskFileHandler::TaskFileHandler() {}

int TaskFileHandler::readFromFile() {
  todo_data.open(filepath, std::ios::in);
  json json_data;

  if (!todo_data) {
    throw std::runtime_error("Error opening file while reading");
  }

  todo_data >> json_data;

  int id = 0;
  // Read json file
  for (const auto &[id_str, task] : json_data.items()) {
    id = std::stoi(id_str);
    std::string desc = task["desc"];
    bool completed = task["completed"];

    TaskRepository::getInstance()->addTask(Task(id, desc, completed));
  }

  todo_data.close();

  // return the last id
  return id;
}

void TaskFileHandler::writeToFile() {
  // Replace old file
  json json_data;
  todo_data.open(filepath, std::ios::out | std::ios::trunc);

  if (!todo_data) {
    throw std::runtime_error("Error opening file while writing");
  }

  // Convert tasks to json
  for (const auto &[id, task] : TaskRepository::getInstance()->getTasks()) {
    json_data[std::to_string(id)] = {{"desc", task.getTaskDesc()},
                                     {"completed", task.isCompleted()}};
  }

  todo_data << json_data.dump(4);

  todo_data.close();
}
