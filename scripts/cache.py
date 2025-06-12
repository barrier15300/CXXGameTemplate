import os

def cache_check(arg0, name):
    cache = os.path.join(os.path.split(arg0)[0], "./cache/" + name)
    if (os.path.exists(cache)): return bool(1)
    dir = os.path.dirname(cache)
    if not (os.path.exists(dir)): os.mkdir(dir)
    file = open(cache, "w")
    file.write("")
    file.close()
    return bool(0)
