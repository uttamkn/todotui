#include <TaskRepository.h>
#include <stdexcept>

TaskRepository::TaskRepository() {}

int TaskRepository::getSize() { return tasks.size(); }

void TaskRepository::addTask(Task task) {
  this->tasks[task.getTaskId()] = task;
}

std::unordered_map<int, Task> &TaskRepository::getTasks() { return tasks; }

Task &TaskRepository::getTaskById(int id) {
  auto it = tasks.find(id);
  if (it == tasks.end()) {
    throw std::out_of_range("Task not found");
  }

  return it->second;
}

void TaskRepository::deleteTaskById(int id) {
  auto it = tasks.find(id);
  if (it == tasks.end()) {
    throw std::out_of_range("Task not found");
  }

  tasks.erase(it);
}
