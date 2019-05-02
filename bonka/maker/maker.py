from subprocess import run, call
import sys
import os
class PathMaker:
    def __init__(self, path):
        dirs = path.split('/')
        res = []
        for el in dirs:
            if el == '.':
                if len(res) > 0:
                    continue
                else:
                    res.append('.')
                    continue
            elif el == '..':
                if len(res) > 0 and res[-1] != '..':
                    res = res[:-1]
                    continue
                else:
                    res.append(el)
                    continue
            else:
                res.append(el)
        self.ans = '/'.join(res) if len(res) > 0 else '.'
def concat(str1, str2):
    return PathMaker(str1 + '/' + str2).ans
class FileDependeces:
    def __init__(self, filename):
        try:
            file = open(filename)
            strings = file.read().split('\n')
            dep = []
            for string in strings:
                if string.find('#include "') == 0:
                    dep.append(string.split('"')[1])
            self.depends = dep
            file.close()
        except:
            self.depends = []
def get_direct_dep(filename):
    return FileDependeces(filename).depends
used = []
def get_directory(filename):
    return '/'.join(filename.split('/')[:-1])
def get_all_dep(filename):
    if filename in used:
        return []
    dir = get_directory(filename)
    used.append(filename)
    direct = get_direct_dep(filename)
    if filename.find('.h') != -1:
        filename = filename.split('.')[0] + '.cpp'
    else:
        filename = filename.split('.')[0] + '.h'
    direct += get_direct_dep(filename)
    ans = []
    for own in direct:
        ans += get_all_dep(concat(dir, own))
    for el in direct:
        ans.append(concat(dir, el))
    return ans
def get_obj_name(filename):
    pos = filename.rfind('.')
    filename = filename[:pos] + '.o'
    return filename
    
def create_maker(filename):
    used.clear()
    res = get_all_dep(filename)
    objects = []
    for el in res:
        cur_dir = os.getcwd()
        os.chdir(get_directory(el))
        run('make')
        os.chdir(cur_dir)
        oname = get_obj_name(el)
        if not oname in objects:
            objects.append(oname)
    call(['g++', '-c', filename])
    call(['g++', '-g', '-Wall', get_obj_name(filename).split('/')[-1]] + objects + ['-o', 'prog', '-lglut', '-lGLU', '-lGL'])
    print("run program")
    run('./prog')
    os.remove('prog')

if __name__ == '__main__':
    argv = sys.argv
    create_maker(argv[1])
