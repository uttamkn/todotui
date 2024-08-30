#ifndef TASKUI_H
#define TASKUI_H

#include "TaskManager.h"

// TODO: Get started with FTXUI

class TaskUI {
  int id;
  TaskManager taskManager;

public:
  TaskUI();

  // User Interface for the console (only for testing)
  void consoleUI();
};
#endif
