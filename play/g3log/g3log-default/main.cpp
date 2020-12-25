#include <iostream>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <g3log/logmessage.hpp>

int main()
{
  auto worker { g3::LogWorker::createLogWorker() };
  auto defaultHandler { worker->addDefaultLogger("test.log", ".") };

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
