#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int k, n;
int s[10000], base[10001], file_id[10000];
bool filled[10000];
vector<vector<int> > pos;  // position of file i's j-th block.
bool perfect;

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
  int wrong_id, wrong_offset, hole = -1, target;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < s[j]; j++) {
      if (pos[i][j] != base[i] + j) {
        wrong_id = i;
        wrong_offset = j;
        hole = pos[i][j];
        target = base[i] + j;
        break;
      }
    }
    if (hole != -1) break;
  }
  if (hole == -1) return;
  perfect = false;
  cout << hole + 1 << ' ' << free + 1 << endl;
  // Chain reaction.
  while (hole != target) {
    int id = file_id[hole];
    int offset = hole - base[id];
    cout << pos[id][offset] + 1 << ' ' << hole + 1 << endl;
    hole = pos[id][offset];
  }
  cout << free + 1 << ' ' << hole + 1 << endl;
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
