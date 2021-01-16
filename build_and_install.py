import os
import subprocess
import shutil
import sys
import platform as pf

detectPlatform = pf.system()
seperator = " ; "
if detectPlatform == "Windows":
  seperator = " & "

curWorkingDir = os.path.dirname(os.path.realpath(__file__))

update_cmd = "git submodule update --remote"
gen_cmake_cmd = "cmake .. -DCMAKE_BUILD_TYPE={}"
build_cmd = "cmake --build ."
build_install_cmd = "cmake --build . --target install"

submodproj = {
          "g3log": {
                      "repo": "submods/g3log",
                      "installdir": "install/g3log",
                      "build-variants"  : [
                                      "cmake -DG3_SHARED_LIB=ON  -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_INSTALL_PREFIX={}/shared/Debug ..",
                                      "cmake -DG3_SHARED_LIB=ON  -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={}/shared/Release ..",
                                      "cmake -DG3_SHARED_LIB=OFF -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_INSTALL_PREFIX={}/static/Debug ..",
                                      "cmake -DG3_SHARED_LIB=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={}/static/Release ..",
                                    ]
                   },
          "g3log-wrapper": {
                      "repo": "g3log-wrapper",
                      "installdir": "install/g3log-wrapper",
                      "build-variants"  : [
                                      "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX={}/static/Debug ..",
                                      "cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={}/static/Release ..",
                                    ]
                   },
          "spdlog": {
                      "repo": "submods/spdlog",
                      "installdir": "install/spdlog",
                      "build-variants"  : [
#                                      "cmake -DG3_SHARED_LIB=ON  -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_INSTALL_PREFIX={}/shared/Debug ..",
#                                      "cmake -DG3_SHARED_LIB=ON  -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={}/shared/Release ..",
                                      "cmake -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_INSTALL_PREFIX={}/static/Debug ..",
                                      "cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={}/static/Release ..",
                                    ]
                   },
          "yaml-cpp": {
                      "repo": "submods/yaml-cpp",
                      "installdir": "install/yaml-cpp",
                      "build-variants"  : [
                                      "cmake -DYAML_BUILD_SHARED_LIBS=ON  -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_INSTALL_PREFIX={}/shared/Debug ..",
                                      "cmake -DYAML_BUILD_SHARED_LIBS=ON  -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={}/shared/Release ..",
                                      "cmake -DYAML_BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_INSTALL_PREFIX={}/static/Debug ..",
                                      "cmake -DYAML_BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={}/static/Release ..",
                                    ]
                   },
}

def DeleteDir(dir2Rem):
  result = True
  if os.path.exists(dir2Rem):
    try:
      print("Removing the directory {}".format(dir2Rem))
      shutil.rmtree(dir2Rem)
    except OSError as e:
      print("Error {} while removing the directory {}".format(e.strerror, dir2Rem))
      result = False
  return result

def CreateDir(dir2Create):
  result = True
  try:
    print("Creating the directory {}".format(dir2Create))
    os.mkdir(dir2Create)
  except OSError as e:
    print("Error {} while creating the directory {}".format(e.strerror, dir2Create))
    result = False
  return result


class SubModule(object):
  def __init__(self, inArgs):
    self.opt = inArgs
    self.buildDir = curWorkingDir + "/" + self.opt["repo"] + "/build"
    self.installDir = curWorkingDir + "/" + self.opt["installdir"]
    print("BuildDir={}\nInstallDir={}".format(self.buildDir, self.installDir))

  def InstallInit(self):
    return DeleteDir(self.installDir)

  def BuildInit(self):
    return DeleteDir(self.buildDir) and CreateDir(self.buildDir)

  def Build(self):
    buildDirCmd = "cd {}".format(self.buildDir)
    for cmd in self.opt["build-variants"]:
      # Delete the build directory
      self.BuildInit()
      # Command to change directory to the build directory
      allBuildCmds = buildDirCmd + seperator
      # Command to generate the build tree
      allBuildCmds += cmd.format(self.installDir) + seperator
      # Command to generate the build tree
      allBuildCmds += build_install_cmd
      print("Used command: {}".format(allBuildCmds))
      subprocess.call(allBuildCmds, shell=True)
    

def init():
  # 1. Update the submodues
  subprocess.call(update_cmd, shell=True)


def ExecSubMod(mod):
  sMod = SubModule(mod)
  if sMod.InstallInit():
    sMod.Build()
  else:
    print("Install pre initialization step failed")


def PHelp():
  print("Usage:")
  print("1. Update and compile all submodules: python3 build_and_install.py --a")
  print("2. Update all submodules but compile only one submodule(Note only name of the submodule/wrapper required): python3 build_and_install.py --s <submodule-wrapper-name>")
  print("2.1 Example: Build only yaml-cpp --> python3 build_and_install.py --s yaml-cpp")
  print("3. Build the consumer projects: python3 build_and_install.py --c <path-to-the-consumer-project>")
  print("3.1 Example: Build all examples under play directory --> python3 build_and_install.py --c play")
  print("3.2 Example: Build all examples of yaml-cpp project --> python3 build_and_install.py --c play/yaml-cpp")
  print("3.3 Example: Build only the example 'sequences' in the project yaml-cpp --> python3 build_and_install.py --c play/yaml-cpp/sequences")


if __name__ == '__main__':
  acceptableOpts = ['--a', '--s', '--c']
  if len(sys.argv) > 1:
    opt = sys.argv[1]
    if opt not in acceptableOpts:
      PHelp()
    elif opt == '--a':
      init()
      for proj in submodproj.keys():
        ExecSubMod(submodproj[proj])
    elif len(sys.argv) > 2:
      proj = sys.argv[2]
      if opt == '--s':
        ExecSubMod(submodproj[proj])
      else:
        projDir = "{}/{}/{}".format(curWorkingDir, proj, "build")
        DeleteDir(projDir)
        CreateDir(projDir)
        allBuildCmds = "cd {}".format(projDir) + seperator + gen_cmake_cmd.format("Debug") + seperator + build_cmd
        print("Used command: {}".format(allBuildCmds))
        subprocess.call(allBuildCmds, shell=True)
    else:
      PHelp()
  else:
    PHelp()





