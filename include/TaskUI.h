#ifndef TASKUI_H
#define TASKUI_H

#include "TaskManager.h"

class TaskUI {
  int id;
  TaskManager taskManager;

public:
  TaskUI();

  // User Interface for the console (only for testing)
  void console_ui();
};
#endif
