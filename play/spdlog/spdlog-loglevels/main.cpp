#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main()
{
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  console_sink->set_level(spdlog::level::warn);
  spdlog::logger logger("console", {console_sink});
  logger.debug("1.This is debug log");
  logger.info("1.This is info log");
  logger.warn("1.This is warn log");
  logger.critical("1.This is critical log");

  console_sink->set_level(spdlog::level::info);
  logger.debug("2.This is debug log");
  logger.info("2.This is info log");
  logger.warn("2.This is warn log");
  logger.critical("2.This is critical log");

  logger.set_level(spdlog::level::warn);
  logger.debug("3.This is debug log");
  logger.info("3.This is info log");
  logger.warn("3.This is warn log");
  logger.critical("3.This is critical log");

  // Still no debug level set. How to turn it on ??
  logger.set_level(spdlog::level::debug);
  logger.debug("4.This is debug log");
  logger.info("4.This is info log");
  logger.warn("4.This is warn log");
  logger.critical("4.This is critical log");

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  logger.debug("5.This is debug log");
  logger.info("5.This is info log");
  logger.warn("5.This is warn log");
  logger.critical("5.This is critical log");
}
