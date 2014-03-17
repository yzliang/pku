#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;

int w, n;
vector<string> words;
int f[10001], g[10001], len[10001];

void add_words(string& line) {
  int i = 0;
  while (i < line.size()) {
    while (i < line.size() && (line[i] < 33 || line[i] > 126))
      i++;
    if (i == line.size())
      break;
    int j = i + 1;
    while (j < line.size() && line[j] >= 33 && line[j] <= 126)
      j++;
    words.push_back(line.substr(i, j - i));
    i = j;
  }
}

int get_badness(int num_words, int sum_len) {
  if (num_words == 1)
    return sum_len == w ? 0 : 500;
  if (sum_len + num_words - 1 > w)
    return -1;
  int space = w - sum_len;
  int gaps = num_words - 1;
  int num_big = space % gaps, num_small = gaps - num_big;
  int size = space / gaps;
  int bad = num_big * size * size + num_small * (size - 1) * (size - 1);
  return bad;
}

void fill_gap(queue<int>& q, pair<int, int>& t) {
  int num = t.second - t.first - 1;
  if (num == 0) return;
  int space = w - (len[t.second] - len[t.first]);
  int num_big = space % num, num_small = num - num_big;
  int size = space / num;
  for (int i = 0; i < num_small; i++)
    q.push(size);
  for (int i = 0; i < num_big; i++)
    q.push(size + 1);
}

void compute() {
  n = words.size() - 1;
  for (int i = 1; i <= n; i++)
    len[i] = len[i - 1] + words[i].size();
  f[0] = 0;
  for (int i = 1; i <= n; i++) {
    // f[i]: best score for words[0, ..., i-1].
    f[i] = 1000000000;
    for (int j = i - 1; j >= 0; j--) {
      // put words[j+1, ..., i] into one line.
      int bad = get_badness(i - j, len[i] - len[j]);
      if (bad == -1)
        break;  // words are too long!
      if (f[j] + bad < f[i]) {
        f[i] = f[j] + bad;
        g[i] = j;
      } else if (f[j] + bad == f[i]) {
        // Grab the whole solutions.
        stack<pair<int, int> > s1, s2;
        for (int k = i; k > 0; k = g[k])
          s1.push(make_pair(g[k], k));
        s2.push(make_pair(j, i));
        for (int k = j; k > 0; k = g[k])
          s2.push(make_pair(g[k], k));
        // Locate the first different line.
        pair<int, int> p1, p2;
        do {
          p1 = s1.top();
          s1.pop();
          p2 = s2.top();
          s2.pop();
        } while (p1 == p2);
        // Examine gaps.
        queue<int> q1, q2;
        fill_gap(q1, p1);
        fill_gap(q2, p2);
        while (true) {
          while (q1.empty() && !s1.empty()) {
            fill_gap(q1, s1.top());
            s1.pop();
          }
          while (q2.empty() && !s2.empty()) {
            fill_gap(q2, s2.top());
            s2.pop();
          }
          if (q1.empty() || q2.empty() || q1.front() != q2.front())
            break;
          q1.pop();
          q2.pop();
        }
        if (!q1.empty() && !q2.empty() && q1.front() > q2.front())
          g[i] = j;
      }
    }
  }
}

void pretty() {
  stack<pair<int, int> > s;
  for (int i = n; i > 0; i = g[i])
    s.push(make_pair(g[i], i));
  while (!s.empty()) {
    pair<int, int> t = s.top();
    s.pop();
    int gaps = t.second - t.first - 1;
    if (gaps == 0) {
      cout << words[t.second] << endl;
      continue;
    }
    int space = w - (len[t.second] - len[t.first]);
    int num_big = space % gaps, num_small = gaps - num_big;
    int size = space / gaps;
    int next = t.first + 1;
    cout << words[next++];
    for (int i = 0; i < num_small; i++) {
      for (int j = 0; j < size; j++)
        cout << ' ';
      cout << words[next++];
    }
    for (int i = 0; i < num_big; i++) {
      for (int j = 0; j < size + 1; j++)
        cout << ' ';
      cout << words[next++];
    }
    cout << endl;
  }
}

int main() {
  while (true) {
    cin >> w;
    if (w == 0) break;
    words.clear();
    words.push_back("");  // Placeholder.
    string line;
    getline(cin, line);
    while (getline(cin, line)) {
      if (line.empty() || line[0] == '\r')
        break;
      add_words(line);
    }
    compute();
    pretty();
    cout << endl;
  }
  return 0;
}
