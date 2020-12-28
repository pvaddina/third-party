#include <iostream>
#include <yaml-cpp/yaml.h>

int main()
{
  YAML::Node config = YAML::LoadFile("config.yaml");

  for (const auto& dev : config["Devices"])
  {
    std::cout << dev["name"] << std::endl;
  }
  return 0;
}
