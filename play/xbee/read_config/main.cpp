#define POSIX
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "xbee/serial.h"

//#include "platform_config.h"

int main()
{
  YAML::Node config = YAML::LoadFile("config.yaml");

  for (const auto& dev : config["Devices"])
  {
    std::cout << dev["name"] << std::endl;
  }

  xbee_serial_t serport;

  return 0;
}
