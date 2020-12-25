#include "spdlog/spdlog.h"
#include "spdlog/sinks/file_sinks.h"

int main()
{
  // Max 10240 bytes (10KB) per file and a maximum of 4 files.
  auto console = spdlog::rotating_logger_mt("fl", "test.log", 10240, 4);

  for (int i=0; i<50000; ++i)
  {
    spdlog::get("fl")->info("This is info log output");
    // The debug function does nothing, instead use warning ...
    spdlog::get("fl")->debug("This is debuglog output");
    spdlog::get("fl")->warn("This is warning log output");
    spdlog::get("fl")->error("This is error log output");
    spdlog::get("fl")->critical("This is critical log output");
  }
}
