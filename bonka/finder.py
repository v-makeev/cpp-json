from os.path import isdir
import os
extensions = ['h', 'py', 'cpp', 'md']

def get_files(dir):
    files = os.listdir(dir)
    return [file for file in files if isdir('{}/{}'.format(dir, file))], [file for file in files if file.split('.')[-1] in extensions]
def find_text(text, path = '.'):
    dirs, files = get_files(path)
    for file in files:
        fp = open('{}/{}'.format(path, file), 'r')
        strings = fp.read().split('\n')
        lst = []
        for num, string in enumerate(strings):
            if string.find(text) >= 0:
                lst.append(num + 1)
        if len(lst) > 0:
            print('{}/{}'.format(path, file))
            for string in lst:
                print(string)
        fp.close()
    for dir in dirs:
        find_text(text, '{}/{}'.format(path, dir))
