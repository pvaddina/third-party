#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

int main()
{
  try
  {
    auto logger = spdlog::basic_logger_mt("fl", "test.log");
    spdlog::get("fl")->info("This is info log output");
    // The debug function does nothing, instead use warning ...
    spdlog::get("fl")->debug("This is debuglog output");
    spdlog::get("fl")->warn("This is warning log output");
    spdlog::get("fl")->error("This is error log output");
    spdlog::get("fl")->critical("This is critical log output");
  }
  catch (const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log init failed: " << ex.what() << std::endl;
  }

  return 0;
}
