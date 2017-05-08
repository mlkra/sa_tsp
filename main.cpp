#include "tsp.hpp"

#include <iostream>
#include <ctime>
#include <csignal>
#include <wait.h>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[]) {
  time_t start = time(NULL);
  loadCities();
  int limit;
  cin >> limit;
  pid_t ppid = getpid();
  pid_t pid = fork();
  if (pid == 0) {
    initializeSearch();
    setupHandler();
    search();
    kill(ppid, SIGINT);
  } else {
    time_t currentTime;
    while (1) {
      sleep(1);
      currentTime = time(NULL);
      if (currentTime - start - 1 >= limit) {
        kill(pid, SIGINT);
        break;
      }
    }
    wait(NULL);
  }
  return 0;
}
