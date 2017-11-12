// Simplified question of SGU 103. No need to output the entire path.
#include <iostream>
#include <vector>
using namespace std;

int src, dst, n, m;

struct Node {
  char init;
  int remain;
  int blue_time, purple_time;
} nodes[301];

int g[301][301];

void ReadData() {
  cin >> src >> dst;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> nodes[i].init >> nodes[i].remain >> nodes[i].blue_time
        >> nodes[i].purple_time;
  }
  int x, y, time;
  for (int i = 0; i < m; i++) {
    cin >> x >> y >> time;
    if (g[x][y] != 0) {
      while(1);
    }
    g[x][y] = g[y][x] = time;
  }
}

void GetState(const Node& node, int time, char* c, int* r) {
  if (time < node.remain) {
    *c = node.init;
    *r = node.remain - time;
    return;
  }
  time = (time - node.remain) % (node.blue_time + node.purple_time);
  if (node.init == 'B') {
    if (time < node.purple_time) {
      *c = 'P';
      *r = node.purple_time - time;
    } else {
      *c = 'B';
      *r = node.blue_time + node.purple_time - time;
    }
  } else {
    if (time < node.blue_time) {
      *c = 'B';
      *r = node.blue_time - time;
    } else {
      *c = 'P';
      *r = node.blue_time + node.purple_time - time;
    }
  }
}

int ComputeArrival(int from, int to, int time) {
  char c1, c2;
  int r1, r2;
  GetState(nodes[from], time, &c1, &r1);
  GetState(nodes[to], time, &c2, &r2);
  if (c1 == c2)
    return time + g[from][to];
  int arrival = time;
  int counter = 0;
  while (c1 != c2 && counter++ < 3) {
    if (r1 < r2) {
      arrival += r1 + g[from][to];
      return arrival;
    }
    if (r1 > r2) {
      arrival += r2 + g[from][to];
      return arrival;
    }
    arrival += r1;
    r1 = c1 == 'B' ? nodes[from].purple_time : nodes[from].blue_time;
    c1 = c1 == 'B' ? 'P' : 'B';
    r2 = c2 == 'B' ? nodes[to].purple_time : nodes[to].blue_time;
    c2 = c2 == 'B' ? 'P' : 'B';
  }
  return -1;
}

int main() {
  ReadData();
  
  // Dijkstra.
  int dis[301], prev[301];
  bool go[301] = {0};
  for (int i = 1; i <= n; i++)
    dis[i] = i == src ? 0 : -1;
  while (true) {
    int choice = -1;
    int min_dis = -1;
    for (int i = 1; i <= n; i++) {
      if (dis[i] != -1 && !go[i] && (min_dis == -1 || dis[i] < min_dis)) {
        min_dis = dis[i];
        choice = i;
      }
    }
    if (choice == -1 || choice == dst)
      break;
    go[choice] = true;
    // Relax.
    for (int i = 1; i <= n; i++) {
      if (go[i] || g[choice][i] == 0)
        continue;
      int arrival = ComputeArrival(choice, i, dis[choice]);
      if (arrival != -1 && (dis[i] == -1 || arrival < dis[i])) {
        prev[i] = choice;
        dis[i] = arrival;
      }
    }
  }

  if (dis[dst] == -1) {
    cout << 0 << endl;
    return 0;
  }
  cout << dis[dst] << endl;
  return 0;
}
