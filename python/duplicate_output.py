import os
import subprocess
import sys

# https://stackoverflow.com/questions/616645/how-do-i-duplicate-sys-stdout-to-a-log-file-in-python/2216517
tee = subprocess.Popen(["tee", "/storage/emulated/0/qpython/projects3/cc3100/log.txt"],
                       stdin=subprocess.PIPE)
os.dup2(tee.stdin.fileno(), sys.stdout.fileno())
