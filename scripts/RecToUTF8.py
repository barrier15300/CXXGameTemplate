import sys
import os
import codecs
import cache

args = sys.argv

def main():

    print("RecToUTF8")

    if (len(args) != 2): return

    if (cache.cache_check(args[0], "RecToUTF8")): return

    src = args[1]

    for dirpath, dirs, filenames in os.walk(src):
        for filename in filenames:
            input_path = os.path.join(dirpath, filename)
            output_path = os.path.join(dirpath, filename)

            with codecs.open(input_path, "r", "Shift-JIS") as file:
                try:
                    content = file.read()
                except:
                    continue
            
            with codecs.open(output_path, "w", "UTF-8") as file:
                file.write(content)

main()