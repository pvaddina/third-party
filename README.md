# Third-Party

A repository which simply is a collection of submodules. The included python script provides an easy way to build and install the submodules. They are installed in a directory with the name 'install' within the repo. Small projects which wrap the usage of the library, thereby providing convenient libraries to be readily used in other projects will also be part of this repository. 

The aim of this repository is to  a convenient way to identify, build and install the dependencies in one place. Consuming projects can therefore easily run on multiple platforms and devices without manual download, build and instal step of each dependency. 

Usage
___

* Update and compile all submodules: python3 build_and_install.py --a
* Update all submodules but compile only one submodule(Note only name of the submodule/wrapper required): python3 build_and_install.py --s <submodule-wrapper-name>
  * **Example**: Build only yaml-cpp --> python3 build_and_install.py --s yaml-cpp
* Build the consumer projects: python3 build_and_install.py --c <path-to-the-consumer-project>
  * **Example**: Build all examples under play directory --> python3 build_and_install.py --c play
  * **Example**: Build all examples of yaml-cpp project --> python3 build_and_install.py --c play/yaml-cpp
  * **Example**: Build only the example 'sequences' in the project yaml-cpp --> python3 build_and_install.py --c play/yaml-cpp/sequences
