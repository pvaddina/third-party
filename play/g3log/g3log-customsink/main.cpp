#include <iostream>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <g3log/logmessage.hpp>


struct CustomSink {
// Linux xterm color
// http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
  enum FG_Color {YELLOW = 33, RED = 31, GREEN=32, WHITE = 97};

  FG_Color GetColor(const LEVELS level) const {
     if (level.value == WARNING.value) { return YELLOW; }
     if (level.value == DEBUG.value) { return GREEN; }
     if (g3::internal::wasFatal(level)) { return RED; }

     return WHITE;
  }

  void ReceiveLogMessage(g3::LogMessageMover logEntry) {
     auto level = logEntry.get()._level;
     auto color = GetColor(level);

     std::cout << "\033[" << color << "m"
       << logEntry.get().toString() << "\033[m" << std::endl;
  }
};

int main()
{
  auto worker { g3::LogWorker::createLogWorker() };
  auto sinkHandle = worker->addSink(std::make_unique<CustomSink>(),
                                    &CustomSink::ReceiveLogMessage);

  // logger is initialized
  g3::initializeLogging(worker.get());

  LOG(INFO) << "This is an info log ..";
  LOG(DEBUG) << "This is a debug log ..";
  LOG(WARNING) << "This is a warning log ..";

  // this will also kill the current process
  LOG(FATAL) << "This is a fatal log ..";

  // shutdown the log
  g3::internal::shutDownLogging();
  return 0;
}
