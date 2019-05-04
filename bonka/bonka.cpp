#include <iostream>
#include <vector>
#include <stack>
#include <unistd.h>
#include <string>
#include <fstream>
#include <dirent.h>

using namespace std;

namespace PathMaker {
    string get_current_directory() {
        system("pwd > directory.t");
        ifstream fin("directory.t");
        string ans;
        fin >> ans;
        fin.close();
        unlink("directory.t");
        return ans;
    }
    void cd(const string& s) {
        chdir(s.c_str());
    }
};

int main(int argc, char **argv) {
    auto current_directory = PathMaker::get_current_directory();
        string bonka = string(argv[0]);
    size_t len = bonka.size();
    while (len > 0 && bonka[len - 1] != '/') --len;
    bonka.resize(len);
    PathMaker::cd(current_directory + "/" + bonka);
    if (argc == 1) { cout << "need more arguments\n"; return 1; }
    if ("make" == string(argv[1])) {
        if (argc != 3) { cout << "unright format\n"; return 1; }
        string filename = string(argv[2]);
        filename = current_directory + "/" + filename;
        execlp("python3", "python3", "./maker/maker.py", filename.c_str(), nullptr);
        cout << "error\n";
        return 1;
    }
    return 0;
} 