#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct Frame {
  int score;
  int type;  // strike = 0, spare = 1, other = 2
  bool complete;
  string marking;
  Frame(): score(0), complete(false) {}
};

vector<string> names;
vector<vector<int> > rest;

void update_bonus(Frame* frames, int i, int s1, int s2) {
  if (i == 0) return;
  if (frames[i - 1].type == 0) {
    frames[i - 1].score += s1;
    if (s2 >= 0) {
      frames[i - 1].score += s2;
      frames[i - 1].complete = true;
    }
    if (i > 1 && frames[i - 2].type == 0) {
      frames[i - 2].score += s1;
      frames[i - 2].complete = true;
    }
  } else if (frames[i - 1].type == 1) {
    frames[i - 1].score += s1;
    frames[i - 1].complete = true;
  }
}

char to_char(int from, int to, bool first) {
  if (first)
    return to == 0 ? 'X' : (to == 10 ? '-' : 10 - to + '0');
  else
    return to == 0 ? '/' : (to == from ? '-' : from - to + '0');
}

void process(int p) {
  Frame frames[12];
  int i = 0, j = 0;  // i: frame, j: throw result
  while (j < rest[p].size()) {
    if (rest[p][j] == 0) {
      frames[i].score = 10;
      frames[i].type = 0;
      frames[i].marking = 'X';
      update_bonus(frames, i, 10, -1);
      i++;
      j++;
    } else if (j + 1 < rest[p].size()) {
      frames[i].score = 10 - rest[p][j + 1];
      frames[i].type = frames[i].score == 10 ? 1 : 2;
      frames[i].complete = frames[i].score < 10;
      frames[i].marking = to_char(10, rest[p][j], true);
      frames[i].marking.append(1, to_char(rest[p][j], rest[p][j + 1], false));
      update_bonus(frames, i, 10 - rest[p][j], rest[p][j] - rest[p][j + 1]);
      i++;
      j += 2;
    } else {
      frames[i].score = 10 - rest[p][j + 1];
      frames[i].complete = false;
      frames[i].marking = to_char(10, rest[p][j], true);
      update_bonus(frames, i, 10 - rest[p][j], -1);
      i++;
      break;
    }
  }
  // Output.
  if (i == 0) {
    printf("%s\n\n", names[p].c_str());
    return;
  }
  printf("%-13s", names[p].c_str());
  for (int j = 0; j < i; j++) {
    if (j > 0 && j < 10)
      printf("%s", string(4 - frames[j - 1].marking.size(), ' ').c_str());
    printf("%s", frames[j].marking.c_str());
  }
  printf("\n");
  int sum = 0;
  for (int j = 0; j < i && j < 10; j++) {
    if (!frames[j].complete) break;
    sum += frames[j].score;
    if (j == 0)
      printf("%16d", sum);
    else
      printf("%4d", sum);
  }
  printf("\n");
}

int main() {
  string name;
  while (cin >> name) {
    names.push_back(name);
    rest.push_back(vector<int>());
    int r;
    while (cin >> r) {
      if (r == -1) break;
      rest.back().push_back(r);
    }
  }
  for (int i = 0; i < names.size(); i++) {
    if (i > 0)
      printf("\n");
    process(i);
  }
  return 0;
}
