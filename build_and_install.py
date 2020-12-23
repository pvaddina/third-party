import os
import subprocess

cmds = {
          "update": "git submodule update --remote",
          "g3log": {
                      "repo": "submods/g3log",
                   }
}

class SubModule(object):
  def __init__(self, inArgs):
    self.opt = inArgs
  
  def Update(self):
    pass
    


def init():
  # 1. Remove the install directory
  cleanDir = "install"
  try:
    os.rmdir(cleanDir)
  except OSError as e:
    print("There was an error:{} while removing the directory {}".format(e.strerror, cleanDir))

  # 2. Update the submodues
  subprocess.call(cmds["update"])
  


if __name__ == '__main__':
  init()

