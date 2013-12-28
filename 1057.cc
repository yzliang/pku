#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Directory {
  string name;
  vector<Directory> dirs;
  vector<string> files;

  Directory(const string& name) : name(name) {}
};

bool read_input(Directory& root) {
  string s;
  while (cin >> s) {
    if (s[0] == '#') return false;
    if (s[0] == 'f')
      root.files.push_back(s);
    else if (s[0] == 'd') {
      root.dirs.push_back(Directory(s));
      read_input(root.dirs.back());
    } else
      break;
  }
  return true;
}

void write_name(const string& name, int level) {
  for (int i = 0; i < level; i++)
    cout << "|     ";
  cout << name << endl;
}

void dump(Directory& root, int level) {
  write_name(root.name, level);
  for (int i = 0; i < root.dirs.size(); i++)
    dump(root.dirs[i], level + 1);
  sort(root.files.begin(), root.files.end());
  for (int i = 0; i < root.files.size(); i++)
    write_name(root.files[i], level);
}

int main() {
  int id = 0;
  while (true) {
    Directory root("ROOT");
    if (!read_input(root)) break;
    ++id;
    if (id > 1) cout << endl;
    cout << "DATA SET " << id << ':' << endl;
    dump(root, 0);
  }
  return 0;
}
