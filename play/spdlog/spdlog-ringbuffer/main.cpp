#include "spdlog/spdlog.h"
#include "spdlog/sinks/ringbuffer_sink.h"

int main()
{
  //auto logger = spdlog::sinks::ringbuffer_sink_mt(20);
  spdlog::enable_backtrace(20);

  // application logged around 200 messages but not all are interesting ..
  for (int i=1; i<=200; ++i)
  {
    spdlog::debug("A log event {}", i);
  }

  // but something happened and we want to analyze this error ...
  // so dump the last 10 messages to see what exactly went wrong ...
  spdlog::dump_backtrace();
}
