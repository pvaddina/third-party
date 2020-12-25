#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"

int main()
{
  auto console = spdlog::stderr_color_st("console");
  spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
}
