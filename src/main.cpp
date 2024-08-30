#include "TaskUI.h"
#include <csignal>

int main() {
  TaskUI taskUI;
  std::signal(SIGINT, TaskManager::handleSignal);
  taskUI.consoleUI();
}
