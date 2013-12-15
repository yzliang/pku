#include <algorithm>
#include <cstring>
#include <list>
#include <iostream>
#include <vector>
using namespace std;

struct Piece {
  int x, y;
  Piece(int x, int y) : x(x), y(y) {}
};

struct Block {
  int w, h;
  vector<Piece> pieces;
  bool operator<(const Block& that) const {
    return pieces.size() < that.pieces.size();
  }
  void dump() {
    cout << "size = " << pieces.size() << endl;
    cout << w << ' ' << h << endl;
    bool map[100][100] = {0};
    for (int i = 0; i < pieces.size(); i++) {
      map[pieces[i].x][pieces[i].y] = true;
    }
    for (int i = h - 1; i >= 0; i--) {
      for (int j = 0; j < w; j++)
        cout << (map[j][i] ? '#' : '.');
      cout << endl;
    }
  }
};

int w, h, n;
bool a[100][100], b[100][100];

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

void get_blocks(bool map[][100], list<Block>& l) {
  bool go[100][100] = {0};
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if (!map[i][j] || go[i][j]) continue;
      l.push_back(Block());
      Block& block = l.back();
      go[i][j] = true;
      block.pieces.push_back(Piece(i, j));
      int head = 0, min_x = i, min_y = j, max_x = i, max_y = j;
      while (head < block.pieces.size()) {
        Piece hp = block.pieces[head];
        for (int k = 0; k < 4; k++) {
          int nx = hp.x + dx[k], ny = hp.y + dy[k];
          if (nx >= 0 && nx < w && ny >= 0 && ny < h && map[nx][ny] &&
              !go[nx][ny]) {
            go[nx][ny] = true;
            block.pieces.push_back(Piece(nx, ny));
            min_x = min(min_x, nx);
            min_y = min(min_y, ny);
            max_x = max(max_x, nx);
            max_y = max(max_y, ny);
          }
        }
        head++;
      }
      block.w = max_x - min_x + 1;
      block.h = max_y - min_y + 1;
      for (int k = 0; k < block.pieces.size(); k++) {
        block.pieces[k].x -= min_x;
        block.pieces[k].y -= min_y;
      }
    }
  }
}

void swap(int& a, int&b) {
  int temp = a;
  a = b;
  b = temp;
}

void transpose(Block& b) {
  swap(b.h, b.w);
  for (vector<Piece>::iterator it = b.pieces.begin(); it != b.pieces.end();
      it++)
    swap(it->x, it->y);
}

bool cover(vector<Piece>& a, vector<Piece>& b) {
  bool map[100][100] = {0};
  for (vector<Piece>::iterator it = a.begin(); it != a.end(); it++)
    map[it->x][it->y] = true;
  for (vector<Piece>::iterator it = b.begin(); it != b.end(); it++)
    if (!map[it->x][it->y])
      return false;
  return true;
}

void h_flip(Block& b) {
  for (vector<Piece>::iterator it = b.pieces.begin(); it != b.pieces.end();
      it++)
    it->y = b.h - 1 - it->y;
}

void v_flip(Block& b) {
  for (vector<Piece>::iterator it = b.pieces.begin(); it != b.pieces.end();
      it++)
    it->x = b.w - 1 - it->x;
}

bool same(Block& a, Block& b) {
  // Given: a and b have the same number of pieces.
  if (a.w > a.h) transpose(a);
  if (b.w > b.h) transpose(b);
  if (a.w != b.w || a.h != b.h) return false;
  if (a.w == 1) return true;
  if (cover(a.pieces, b.pieces)) return true;
  h_flip(b);
  if (cover(a.pieces, b.pieces)) return true;
  v_flip(b);
  if (cover(a.pieces, b.pieces)) return true;
  h_flip(b);
  if (cover(a.pieces, b.pieces)) return true;
  if (a.w != a.h) return false;
  // If the shape is in square.
  transpose(b);
  if (cover(a.pieces, b.pieces)) return true;
  h_flip(b);
  if (cover(a.pieces, b.pieces)) return true;
  v_flip(b);
  if (cover(a.pieces, b.pieces)) return true;
  h_flip(b);
  if (cover(a.pieces, b.pieces)) return true;
  return false;
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> w >> h >> n;
    memset(a, 0, sizeof(a));
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      a[x][y] = true;
    }
    memset(b, 0, sizeof(b));
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      b[x][y] = true;
    }
    list<Block> list1, list2;
    get_blocks(a, list1);
    get_blocks(b, list2);
    if (list1.size() != list2.size()) {
      cout << "NO" << endl;
      continue;
    }
    list1.sort();
    list2.sort();
    /*
    for (list<Block>::iterator i = list1.begin(); i != list1.end(); i++)
      i->dump();
    for (list<Block>::iterator i = list2.begin(); i != list2.end(); i++)
      i->dump();
      */
    while (!list1.empty()) {
      int head_size = list1.front().pieces.size();
      list<Block>::iterator it = list2.begin();
      bool found = false;
      while (it != list2.end() && it->pieces.size() == head_size) {
        if (same(list1.front(), *it)) {
          list1.pop_front();
          list2.erase(it);
          found = true;
          break;
        }
        it++;
      }
      if (!found) break;
    }
    cout << (list1.empty() ? "YES" : "NO") << endl;
  }
  return 0;
}
