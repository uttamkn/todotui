#include "TaskUI.h"
#include <csignal>

int main() {
  TaskUI taskUI;
  std::signal(SIGINT, TaskFileHandler::handleSignal);
  taskUI.console_ui();

  return 0;
}
