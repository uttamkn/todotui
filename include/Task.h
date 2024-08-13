#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
  int id;
  std::string desc;
  bool completed;

public:
  Task();
  Task(int id, std::string desc, bool completed);

  int getTaskId() const;
  std::string getTaskDesc() const;
  bool isCompleted() const;

  void markAsCompleted();
  void updateDesc(std::string desc);
};

#endif
