import sys
import os
import shutil

args = sys.argv

def main():    

    if (len(args) != 3):
        print("invalid args")
        return

    src = str(args[1])
    dest = os.path.join(str(args[2]), os.path.split(src)[1]) 
    
    if (os.path.exists(dest)): shutil.rmtree(dest)
    
    shutil.copytree(src, dest)

main()