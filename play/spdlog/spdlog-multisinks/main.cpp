#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"

int main()
{
  auto console = spdlog::stderr_color_st("console");
  spdlog::get("console")->info("This is info log output");
  // The debug function does nothing, instead use warning ...
  spdlog::get("console")->debug("This is debuglog output");
  spdlog::get("console")->warn("This is warning log output");
  spdlog::get("console")->error("This is error log output");
  spdlog::get("console")->critical("This is critical log output");
}
