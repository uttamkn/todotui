#include "TaskManager.h"
#include <csignal>

int main() {
  TaskManager myTasks;
  std::signal(SIGINT, TaskFileHandler::handleSignal);
  myTasks.console_ui();

  return 0;
}
