#include <iostream>
#include "yaml-cpp/yaml.h"

int main()
{
  try {
    YAML::Node config = YAML::LoadFile("config.yaml");
    // Output sequence1
    for(YAML::const_iterator it=config["sequence1"].begin(); it != config["sequence1"].end(); ++it)
    {
      std::cout << it->as<std::string>() << "\n";
    }

    std::cout << "1************************************************\n";
    // Output sequence2
    for(YAML::const_iterator it=config["sequence2"].begin(); it != config["sequence2"].end(); ++it)
    {
      std::cout << it->as<std::string>() << "\n";
    }

    std::cout << "2************************************************\n";
    // Output sequence3
    for(YAML::const_iterator it=config["sequence3"].begin(); it != config["sequence3"].end(); ++it)
    {
      std::cout << it->as<std::string>() << "\n";
    }

    // Output sequence3 again, a bit differently
    std::cout << "3************************************************\n";
    for(YAML::const_iterator it=config["sequence3"].begin(); it != config["sequence3"].end(); ++it)
    {
      const YAML::Node& nd = *it;
      if(nd.IsSequence())
      {
        for(YAML::const_iterator mit=nd.begin(); mit != nd.end(); ++mit)
        {
          std::cout << mit->as<double>() << "-";
        }
      }
      else if (nd.IsScalar())
      {
        std::cout << it->as<std::string>() << "\n";
      }
    }

    // Output sequence4 again, a bit differently
    std::cout << "4************************************************\n";
    // The following will result in an exception
    for(const auto& it : config["sequence4"])
    {
      for (const auto& mit: it) // Note 'it' is a map and not a pair
      {
        std::cout << mit.first.as<std::string>() << ":\n";
        const YAML::Node& nd = mit.second;
        if(nd.IsMap())
        {
          for(const auto& intMIt: nd)
          {
            std::cout << "     " << intMIt.first.as<std::string>() << "-->" << intMIt.second.as<double>() << "\n";
          }
        }
        else
        {
          std::cout << "     " << mit.second.as<std::string>() << "\n";
        }
      }
    }

    std::cout << "5************************************************\n";
    for(YAML::const_iterator it=config["sequence4"].begin(); it != config["sequence4"].end(); ++it)
    {
      for (const auto& mit: *it) // Note 'it' is a map and not a pair
      {
        std::cout << mit.first.as<std::string>() << ":\n";
        const YAML::Node& nd = mit.second;
        if(nd.IsMap())
        {
          for(const auto& intMIt: nd)
          {
            std::cout << "     " << intMIt.first.as<std::string>() << "-->" << intMIt.second.as<double>() << "\n";
          }
        }
        else
        {
          std::cout << "     " << mit.second.as<std::string>() << "\n";
        }
      }
    }

    std::cout << "6************************************************\n";
    for(const auto& it : config["sequence5"])
    {
      for (const auto& mit: it) // Note 'it' is a map and not a pair
      {
        std::cout << mit.first.as<std::string>() << ":\n";
        const YAML::Node& nd = mit.second;
        if(nd.IsMap())
        {
          for(const auto& intMIt: nd)
          {
            std::cout << "     " << intMIt.first.as<std::string>() << "-->" << intMIt.second.as<double>() << "\n";
          }
        }
        else if (nd.IsScalar())
        {
          std::cout << "     " << mit.second.as<std::string>() << "\n";
        }
      }
    }

    std::cout << "7************************************************\n";
    for(const auto& it : config["sequence5"])
    {
      if (it.IsMap())
      {
        for (const auto& mit: it) // Note 'it' is a map and not a pair
        {
          std::cout << mit.first.as<std::string>() << ":\n";
          const YAML::Node& nd = mit.second;
          if(nd.IsMap())
          {
            for(const auto& intMIt: nd)
            {
              std::cout << "     " << intMIt.first.as<std::string>() << "-->" << intMIt.second.as<double>() << "\n";
            }
          }
          else
          {
            std::cout << "     " << mit.second.as<std::string>() << "\n";
          }
        }
      }
      else
      {
        std::cout << it.as<std::string>() << "\n";
      }

    }
  } catch (const YAML::Exception& exp) {
    std::cout << exp.what() << std::endl;
  }

  return 0;
}
