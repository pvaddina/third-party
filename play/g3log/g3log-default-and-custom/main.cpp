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

struct StdOutSink {
  void ReceiveLogMessage(g3::LogMessageMover logEntry) {
     auto level = logEntry.get()._level;

     std::cout << logEntry.get().toString() << std::endl;
  }
};

int main()
{
  auto worker { g3::LogWorker::createLogWorker() };
  auto defaultHandler { worker->addDefaultLogger("test.log", ".") };

  // logger is initialized
  g3::initializeLogging(worker.get());

  LOG(INFO) << "FileSink: This is an info log ..";
  LOG(DEBUG) << "FileSink: This is a debug log ..";
  LOG(WARNING) << "FileSink: This is a warning log ..";

  // Now replace the sink from file to the custom sink
  auto sinkHandle = worker->addSink(std::make_unique<CustomSink>(),
                                    &CustomSink::ReceiveLogMessage);
  LOG(INFO) << "CustomSink: This is an info log ..";
  LOG(DEBUG) << "CustomSink: This is a debug log ..";
  LOG(WARNING) << "CustomSink: This is a warning log ..";

  //remove all the sinks and add only one default sink
  worker->removeAllSinks();
  auto stdOutHandle = worker->addSink(std::make_unique<StdOutSink>(),
                                    &StdOutSink::ReceiveLogMessage);
  LOG(INFO) << "StdoutSink: This is an info log ..";
  LOG(DEBUG) << "StdoutSink: This is a debug log ..";
  LOG(WARNING) << "StdoutSink: This is a warning log ..";

  // shutdown the log
  g3::internal::shutDownLogging();
  return 0;
}
