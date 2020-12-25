# Third-Party

A repository which simply is a collection of submodules. The included python script provides an easy way to build and install the submodules. They are installed in a directory with the name 'install' within the repo. Small projects which wrap the usage of the library, thereby providing convenient libraries to be readily used in other projects will also be part of this repository. 

The aim of this repository is to  a convenient way to identify, build and install the dependencies in one place. Consuming projects can therefore easily run on multiple platforms and devices without manual download, build and instal step of each dependency. 

**Usage**:
* Build and install all submodules and other wrapper projects: python3 build_and_install.py
* Build and install only a specific project/sub-module: python3 build_and_install.py g3log-wrapper
* Build all the consumer projects (usually no install is supported) under play directory: python3 build_and_install.py play
* Build all consumer projects related to one library(in this example play/g3log): python3 build_and_install.py play/g3log
* Build just one single project(in this example play/g3log/g3log-wrapper-1): python3 build_and_install.py play/g3log/g3log-wrapper-1

