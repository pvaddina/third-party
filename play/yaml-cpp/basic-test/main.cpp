#include <iostream>
#include "yaml-cpp/yaml.h"

int main()
{
  YAML::Node config = YAML::LoadFile("config.yaml");
  std::cout << config["name"] << " is a river in " << config["country"] << " and is known to flow through the following states:";
  for(YAML::const_iterator it=config["flowsthrough"].begin(); it != config["flowsthrough"].end(); ++it)
  {
    std::cout << it->as<std::string>() << "\n";
  }
  return 0;
}
