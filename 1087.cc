#include <iostream>
#include <string>
#include <map>
using namespace std;

int n, m, k;
int recepts[100];  // room receptacle ids.
int devices[100];  // device plug ids.
int adapters[100][2];  // 0: receptacle, 1: plug
bool adapt[400][400];  // adapt[i][j]: plug i to receptacle j
map<string, int> name_ids;
bool graph[202][202];

int get_id(string& name) {
  map<string, int>::iterator it = name_ids.find(name);
  int id;
  if (it == name_ids.end()) {
    id = name_ids.size();
    name_ids[name] = id;
  } else
    id = it->second;
  return id;
}

void floyd() {
  for (int i = 0; i < name_ids.size(); i++)
    adapt[i][i] = true;
  for (int i = 0; i < k; i++)
    adapt[adapters[i][0]][adapters[i][1]] = true;
  for (int mid = 0; mid < name_ids.size(); mid++)
    for (int i = 0; i < name_ids.size(); i++)
      for (int j = 0; j < name_ids.size(); j++)
        adapt[i][j] |= adapt[i][mid] && adapt[mid][j];
}

// 0: source; 1~n: receptacles; n+1~n+m: devices; n+m+1: sink.
void build_graph() {
  for (int i = 1; i <= n; i++)
    graph[0][i] = true;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      graph[i + 1][j + n + 1] = adapt[devices[j]][recepts[i]];
  for (int i = n + 1; i <= n + m; i++)
    graph[i][n + m + 1] = true;
}

int max_flow() {
  int total = 0;
  while (true) {
    bool visit[202] = {0};
    int pre[202];
    int q[202];
    int head = 0, tail = 0;
    q[0] = 0;
    visit[0] = true;
    while (head <= tail && !visit[n + m + 1]) {
      int from = q[head++];
      for (int i = 1; i <= n + m + 1; i++) {
        if (!visit[i] && graph[from][i]) {
          visit[i] = true;
          pre[i] = from;
          q[++tail] = i;
        }
      }
    }
    if (!visit[n + m + 1]) return total;
    total++;
    // Use the augmenting path.
    for (int i = n + m + 1; i > 0; i = pre[i]) {
      graph[pre[i]][i] = false;
      graph[i][pre[i]] = true;
    }
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    string name;
    cin >> name;
    recepts[i] = get_id(name);
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    string dummy, name;
    cin >> dummy >> name;
    devices[i] = get_id(name);
  }
  for (int i = 0; i < name_ids.size(); i++)
    adapt[i][i] = true;
  cin >> k;
  for (int i = 0; i < k; i++) {
    string name1, name2;
    cin >> name1 >> name2;
    adapters[i][0] = get_id(name1);
    adapters[i][1] = get_id(name2);
  }
  floyd();
  build_graph();
  cout << m - max_flow() << endl;
  return 0;
}
