#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
  char type;  // 0: and, 1: or, 2: not, 3: id
  int l, r;
};

int w, h;
char map[200][200];
vector<Node> nodes;

bool read_input() {
  memset(map, 0, sizeof(map));
  h = 0;
  w = 0;
  while (cin.getline(map[h], 200)) {
    if (map[h][0] == '*') break;
    int len = strlen(map[h]);
    if (map[h][len - 1] == '\r') {
      len--;
      map[h][len] = '\0';
    }
    if (len > w) w = len;
    h++;
  }
  return h != 0;
}

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

void traverse(int& x, int& y) {
  int dir = -1;  // 0: left, -1: up, 1: down.
  if (map[x][y] >= 'A' && map[x][y] <= 'Z') return;
  if (map[x][y] == ':' || map[x][y] == 'o') {
    y--;
    dir = 2;
  } else if (map[x][y] == '?') {
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx == h || ny < 0 || ny == w) continue;
      if (i % 2 == 0 && map[nx][ny] == '-') {
        dir = i;
        break;
      } else if (i % 2 == 1 && map[nx][ny] == '|') {
        dir = i;
        break;
      }
    }
    x += dx[dir];
    y += dy[dir];
  }
  while (true) {
    if (map[x][y] == '-' || map[x][y] == '|') {
      x += dx[dir];
      y += dy[dir];
    } else if (map[x][y] == '+') {
      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx == h || ny < 0 || ny == w) continue;
        if ((i + dir) % 2 == 0) continue;
        if (i % 2 == 0 && map[nx][ny] == '-') {
          dir = i;
          break;
        } else if (i % 2 == 1 && map[nx][ny] == '|') {
          dir = i;
          break;
        }
      }
      x += dx[dir];
      y += dy[dir];
    } else
      break;
  }
}

void find_type(int i, int x, int y) {
  traverse(x, y);
  if (map[x][y] >= 'A' && map[x][y] <= 'Z') {
    nodes[i].type = 3;
    nodes[i].l = map[x][y] - 'A';
  } else if (map[x][y] == 'o') {
    nodes[i].type = 2;
    nodes.push_back(Node());
    nodes[i].l = nodes.size() - 1;
    find_type(nodes[i].l, x, y);
  } else {
    nodes[i].type = map[x][y] == '>';
    nodes.push_back(Node());
    nodes.push_back(Node());
    nodes[i].l = nodes.size() - 2;
    nodes[i].r = nodes.size() - 1;
    find_type(nodes[i].l, x - 1, y - 2);
    find_type(nodes[i].r, x + 1, y - 2);
  }
}

void get_nodes() {
  for (int i = 0; i < h; i++) {
    if (map[i][w - 1] == '?') {
      nodes.push_back(Node());
      find_type(0, i, w - 1);
      break;
    }
  }
}

bool eval(string& s, int i) {
  if (nodes[i].type == 0)
    return eval(s, nodes[i].l) && eval(s, nodes[i].r);
  else if (nodes[i].type == 1)
    return eval(s, nodes[i].l) || eval(s, nodes[i].r);
  else if (nodes[i].type == 2)
    return !eval(s, nodes[i].l);
  else
    return s[nodes[i].l] == '1';
}

int main() {
  bool first = true;
  while (true) {
    if (!read_input()) break;
    get_nodes();
    if (first)
      first = false;
    else
      cout << endl;
    string s;
    while (getline(cin, s)) {
      if (s[0] == '*') break;
      cout << eval(s, 0) << endl;
    }
  }
  return 0;
}
