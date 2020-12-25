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
build_install_cmd = "cmake --build . --target install"

cmds = {
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

class SubModule(object):
  def __init__(self, inArgs):
    self.opt = inArgs
    self.buildDir = curWorkingDir + "/" + self.opt["repo"] + "/build"
    self.installDir = curWorkingDir + "/" + self.opt["installdir"]

  def InstallInit(self):
    result = True
    if os.path.exists(self.installDir):
      try:
        print("Removing the install directory {}".format(self.installDir))
        shutil.rmtree(self.installDir)
      except OSError as e:
        print("Error {} while removing the install directory {}".format(e.strerror, self.installDir))
        result = False

    return result

  def BuildInit(self):
    result = True
    if os.path.exists(self.buildDir):
      try:
        print("Removing the build directory {}".format(self.buildDir))
        shutil.rmtree(self.buildDir)
      except OSError as e:
        print("Error {} while removing the build directory {}".format(e.strerror, self.buildDir))
        result = False
    
    if result:
      try:
        print("Creating the build directory {}".format(self.installDir))
        os.mkdir(self.buildDir)
      except OSError as e:
        print("Error {} while creating the directory {}".format(e.strerror, self.buildDir))
        result = False

    return result

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
  # 1. Remove the install directory
  installDir = curWorkingDir + "/install"
  try:
    os.rmdir(installDir)
  except OSError as e:
    print("Cannot remove directory: \"{}\". Error: {}. Ignoring the error ...".format(installDir, e.strerror))

  # 2. Update the submodues
  subprocess.call(update_cmd, shell=True)


def ExecSubMod(mod):
  sMod = SubModule(mod)
  if sMod.InstallInit():
    sMod.Build()
  else:
    print("Install pre initialization step failed")


if __name__ == '__main__':
  init()
  if len(sys.argv) > 1:
    proj = sys.argv[1]
    if proj in cmds.keys():
      ExecSubMod(cmds[proj])
    else:
      print("Project not declared. Aborting ...")
  else:
    for proj in cmds.keys():
      ExecSubMod(cmds[proj])





