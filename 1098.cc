#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Cell {
  int x, y;
  Cell() {}
  Cell(int x, int y) : x(x), y(y) {}
};

// Normal moves.
const int dx[] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
const int dy[] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

inline bool in_bound(int x, int y) {
  return x >= 0 && x < 31 && y >= 0 && y < 31;
}

inline int abs(int x) {
  return x >= 0 ? x : -x;
}

typedef vector<Cell>::iterator CellIter;

struct Scene {
  int x, y;
  int map[31][31]; // 0: clear, 1: robot, -1: debris
  vector<Cell> robots;

  Scene& operator=(const Scene& that) {
    x = that.x;
    y = that.y;
    memcpy(map, that.map, sizeof(map));
    robots = that.robots;
    return *this;
  }

  void dump() {
    printf("I=(%d,%d)\n", x + 1, y + 1);
    for (int i = 0; i < 31; i++) {
      for (int j = 0; j < 31; j++)
        if (i == x && j == y)
          cout << 'I';
        else if (map[i][j] == 0)
          cout << '.';
        else if (map[i][j] == 1)
          cout << 'R';
        else if (map[i][j] == -1)
          cout << 'D';
      cout << endl;
    }
    cout << endl;
  }

  void init() {
    x = y = 14;
    memset(map, 0, sizeof(map));
    robots.clear();
  }

  void add_robot(int x, int y) {
    map[x][y] = 1;
    robots.push_back(Cell(x, y));
  }

  int count_debris() {
    int num = 0;
    for (int i = 0; i < 31; i++)
      for (int j = 0; j < 31; j++)
        num += map[i][j] == -1;
    return num;
  }

  int min_distance() {
    int dis = 1000;
    for (CellIter i = robots.begin(); i != robots.end(); i++) {
      int val = abs(i->x - x) + abs(i->y - y);
      if (val < dis)
        dis = val;
    } 
    return dis;
  }

  void move_robots() {
    static bool dead[50];
    static int nmap[31][31];
    memset(dead, 0, sizeof(dead));
    // Copy the debris only.
    memcpy(nmap, map, sizeof(map));
    for (CellIter i = robots.begin(); i != robots.end(); i++)
      nmap[i->x][i->y] = 0;
    // Move each.
    for (int i = 0; i < robots.size(); i++) {
      int nx = robots[i].x, ny = robots[i].y;
      if (nx > x)
        nx--;
      else if (nx < x)
        nx++;
      if (ny > y)
        ny--;
      else if (ny < y)
        ny++;
      // Run into debris?
      if (nmap[nx][ny] == -1) {
        dead[i] = true;
        continue;
      }
      // Crash?
      if (nmap[nx][ny] == 1) {
        dead[i] = true;
        for (int j = 0; j < robots.size(); j++) {
          if (robots[j].x == nx && robots[j].y == ny) {
            dead[j] = true;
            break;
          }
        }
        nmap[nx][ny] = -1;  // Set debris.
        continue;
      }
      nmap[nx][ny] = 1;
      robots[i].x = nx;
      robots[i].y = ny;
    }
    // Clear deads.
    int total = 0;
    for (int i = 0; i < robots.size(); i++) {
      if (!dead[i])
        robots[total++] = robots[i];
    }
    robots.resize(total);
    // Update map.
    memcpy(map, nmap, sizeof(map));
  }

  bool immediate_loss() {
    for (int i = 1; i < 9; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (in_bound(nx, ny) && map[nx][ny] == 1)
        return true;
    }
    return false;
  }

  bool move_me(int i) {
    if (i == 0)
      return true;  // Stand still.
    int nx = x + dx[i], ny = y + dy[i];
    if (!in_bound(nx, ny))
      return false;
    if (map[nx][ny] == 1)
      return false;
    if (map[nx][ny] == -1) {
      // Find the first cell without debris.
      int ex = nx + dx[i], ey = ny + dy[i];
      while (in_bound(ex, ey) && map[ex][ey] == -1) {
        ex += dx[i];
        ey += dy[i];
      }
      if (!in_bound(ex, ey))
        return false;  // Debris hits the boundary.
      if (map[ex][ey] == 1)
        remove_robot(ex, ey);  // Robot crushed by debris.
      // Shift debris.
      while (ex != nx || ey != ny) {
        map[ex][ey] = -1;
        ex -= dx[i];
        ey -= dy[i];
      }
      map[nx][ny] = 0;
    }
    x = nx;
    y = ny;
    return true;
  }

  void remove_robot(int x, int y) {
    map[x][y] = 0;
    for (CellIter i = robots.begin(); i != robots.end(); i++) {
      if (i->x == x && i->y == y) {
        robots.erase(i);
        break;
      }
    }
  }
};


int r, t, moves;
vector<Cell> teleports;
bool used[20];
Scene current;
Scene trial[9];

void simulate() {
  moves = 0;
  memset(used, 0, sizeof(used));
  while (current.robots.size() > 0) {
    int pick = -1, min_left, best_dis;
    for (int i = 0; i < 9; i++) {
      // Compute trial move.
      trial[i] = current;
      if (!trial[i].move_me(i))
        continue;
      if (trial[i].immediate_loss())
        continue;
      trial[i].move_robots();
      int num_left = trial[i].robots.size();
      int min_dis = trial[i].min_distance();
      bool update = false;
      if (pick == -1)
        update = true;
      else if (num_left < min_left)
        update = true;
      else if (num_left == min_left) {
        if (min_dis > best_dis)
          update = true;
        else if (min_dis == best_dis) {
          update = trial[i].x < trial[pick].x ||
            (trial[i].x == trial[pick].x &&
             trial[i].y < trial[pick].y);
        }
      }
      if (update) {
        pick = i;
        min_left = num_left;
        best_dis = min_dis;
      }
    }
    if (pick != -1) {
      // Take normal move.
      current = trial[pick];
      moves++;
      continue;
    }
    // Try teleporting.
    bool found = false;
    for (int i = 0; i < t; i++) {
      int nx = teleports[i].x, ny = teleports[i].y;
      if (used[i] || current.map[nx][ny] != 0)
        continue;
      trial[0] = current;
      trial[0].x = nx;
      trial[0].y = ny;
      if (trial[0].immediate_loss())
        continue;
      found = true;
      used[i] = true;
      trial[0].move_robots();
      current = trial[0];
      moves++;
      printf("Move %d: teleport to (%d,%d)\n", moves, current.x + 1,
          current.y + 1);
      break;
    }
    if (!found) {
      // We're done.
      current.move_robots();
      moves++;
      printf("Lost game after making %d moves.\n", moves);
      printf("Final position: (%d,%d)\n", current.x + 1, current.y + 1);
      printf("Number of cells with debris: %d\n", current.count_debris());
      printf("Number of robots remaining: %lu\n", current.robots.size());
      return;
    }
  }
  printf("Won game after making %d moves.\n", moves);
  printf("Final position: (%d,%d)\n", current.x + 1, current.y + 1);
  printf("Number of cells with debris: %d\n", current.count_debris());
}

int main() {
  int case_id = 0;
  while (cin >> r >> t) {
    if (r == 0 && t == 0)
      break;
    current.init();
    for (int i = 0; i < r; i++) {
      int x, y;
      cin >> x >> y;
      current.add_robot(x - 1, y - 1);
    }
    teleports.clear();
    for (int i = 0; i < t; i++) {
      int x, y;
      cin >> x >> y;
      teleports.push_back(Cell(x - 1, y - 1));
    }
    ++case_id;
    if (case_id > 1)
      printf("\n");
    printf("Case %d:\n", case_id);
    simulate();
  }
  return 0;
}
