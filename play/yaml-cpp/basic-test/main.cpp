#include <iostream>
#include "yaml-cpp/yaml.h"

int main()
{
  YAML::Node config = YAML::LoadFile("config.yaml");
  std::cout << config["name"] << " is river in " << config["country"] << " and is approximately " << config["length"]["len"].as<std::string>() << "\n";
  std::cout << config["length"]["units"] << " long\n";
  return 0;
}
