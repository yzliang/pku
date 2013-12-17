#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

typedef list<vector<int> > Final;

char buffer[300];
int rank[101][2];
Final final;
vector<vector<int> > slots;

void get_rank(int contest) {
  int n;
  cin.getline(buffer, 300);
  n = atoi(buffer);
  int r = 1;
  for (int i = 1; i <= n; i++) {
    cin.getline(buffer, 300);
    char* pc = strtok(buffer, " \n");
    int id, total = 0;
    while (pc != NULL) {
      total++;
      id = atoi(pc);
      rank[id][contest] = r;
      pc = strtok(NULL, " \n");
    }
    r += total;
  }
}

bool compare_rank(int i, int j) {
  int r1 = max(rank[i][0], rank[i][1]);
  int r2 = max(rank[j][0], rank[j][1]);
  if (r1 != r2)
    return r1 < r2;
  else
    return i < j;
}

void sort_and_output(vector<int> v) {
  sort(v.begin(), v.end(), compare_rank);
  cout << v[0];
  for (int i = 1; i < v.size(); i++) {
    if (max(rank[v[i]][0], rank[v[i]][1]) ==
        max(rank[v[i - 1]][0], rank[v[i - 1]][1]))
      cout << ' ' << v[i];
    else
      cout << endl << v[i];
  }
  cout << endl;
}

int main() {
  get_rank(0);
  cin.getline(buffer, 200);
  get_rank(1);
  // Sort contesters of both.
  for (int i = 1; i <= 100; i++) {
    if (rank[i][0] == 0 || rank[i][1] == 0) continue;
    bool inserted = false;
    int val1 = rank[i][0] + rank[i][1];
    for (Final::iterator it = final.begin(); it != final.end(); it++) {
      int val2 = rank[it->front()][0] + rank[it->front()][1];
      if (val1 <= val2) {
        inserted = true;
        if (val1 < val2)
          final.insert(it, vector<int>(1, i));
        else
          it->push_back(i);
        break;
      }
    }
    if (!inserted)
      final.push_back(vector<int>(1, i));
  }
  // Insert single contesters.
  slots.resize(final.size() * 2 + 1);
  for (int i = 1; i <= 100; i++) {
    if (!((rank[i][0] == 0) ^ (rank[i][1] == 0))) continue;
    int contest = rank[i][0] != 0 ? 0 : 1;
    int same = -1, max_top = -1, min_down = -1;
    int index = 0;
    for (Final::iterator it1 = final.begin(); it1 != final.end(); it1++) {
      for (vector<int>::iterator it2 = it1->begin(); it2 != it1->end(); it2++) {
        if (rank[i][contest] == rank[*it2][contest]) {
          if (same == -1)
            same = index;
          else if (same >= 0 && same != index)
            same = -2;
        } else if (rank[i][contest] < rank[*it2][contest]) {
          if (min_down == -1) min_down = index;
        } else {
          max_top = index;
        }
      }
      index++;
      if (same == -2) break;
    }
    if (same == -2) continue;
    if (same >= 0) {
      slots[same * 2 + 1].push_back(i);
      continue;
    }
    if (max_top == -1)
      slots.front().push_back(i);
    else if (min_down == -1)
      slots.back().push_back(i);
    else if (max_top < min_down)
      slots[(max_top + 1) * 2].push_back(i);
  }
  // Output.
  int index = 0;
  for (Final::iterator it = final.begin(); it != final.end(); it++) {
    if (!slots[index * 2].empty())
      sort_and_output(slots[index * 2]);
    it->insert(it->end(), slots[index * 2 + 1].begin(),
               slots[index * 2 + 1].end());
    sort(it->begin(), it->end());
    cout << it->front();
    for (int i = 1; i < it->size(); i++)
      cout << ' ' << (*it)[i];
    cout << endl;
    index++;
  }
  if (!slots.empty() && !slots.back().empty())
    sort_and_output(slots.back());
  return 0;
}
