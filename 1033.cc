#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int k, n;
int s[10000], base[10001], file_id[10000];
bool filled[10000];
vector<vector<int> > pos;  // position of file i's j-th block.
bool perfect = true;

void fill_empty() {
  queue<int> holes;  // empty holes.
  for (int i = 0; i < k; i++)
    for (int j = 0; j < s[i]; j++)
      if (!filled[base[i] + j])
        holes.push(base[i] + j);
  perfect = holes.empty();
  while (!holes.empty()) {
    int head = holes.front();
    holes.pop();
    int id = file_id[head];
    int offset = head - base[id];
    int from = pos[id][offset];
    cout << from + 1 << ' ' << head + 1 << endl;
    filled[head] = true;
    filled[from] = false;
    pos[id][offset] = head;
    if (from < base[k])
      holes.push(from);  // also an empty hole in the optimal area.
  }
}

void swap_wrong() {
  int free = base[k];
  queue<int> holes;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < s[i]; j++) {
      if (pos[i][j] != base[i] + j)
        holes.push(base[i] + j);
    }
  }
  perfect = perfect && holes.empty();
  while (!holes.empty()) {
    int target = holes.front();
    holes.pop();
    int id = file_id[target];
    int offset = target - base[id];
    if (pos[id][offset] == target) continue;  // already fixed.
    cout << pos[id][offset] + 1 << ' ' << free + 1 << endl;
    int hole = pos[id][offset];
    while (hole != target) {
      id = file_id[hole];
      offset = hole - base[id];
      cout << pos[id][offset] + 1 << ' ' << hole + 1 << endl;
      hole = pos[id][offset];
      pos[id][offset] = base[id] + offset;
    }
    cout << free + 1 << ' ' << target + 1 << endl;
  }
}

int main() {
  cin >> n >> k;
  pos.resize(k);
  for (int i = 0; i < k; i++) {
    cin >> s[i];
    base[i + 1] = base[i] + s[i];
    pos[i].resize(s[i]);
    for (int j = 0; j < s[i]; j++) {
      file_id[base[i] + j] = i;
      cin >> pos[i][j];
      pos[i][j]--;
      filled[pos[i][j]] = true;
    }
  }
  // Fill empty holes in the optimal area.
  fill_empty();
  // Swap the wrong holes.
  swap_wrong();
  if (perfect)
    cout << "No optimization needed" << endl;
  return 0;
}
