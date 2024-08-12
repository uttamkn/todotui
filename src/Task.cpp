#include "Task.h"

Task::Task() : id(0), desc(""), completed(false) {}

Task::Task(int id, std::string desc, bool completed)
    : id(id), desc(desc), completed(completed) {}

int Task::getTaskId() const { return id; }
std::string Task::getTaskDesc() const { return desc; }
bool Task::isCompleted() const { return completed; }
std::string Task::getTaskCsv() const {
  return std::to_string(id) + "," + desc + "," + std::to_string(int(completed));
}

void Task::markAsCompleted() { this->completed = true; }
void Task::updateDesc(std::string desc) { this->desc = desc; }