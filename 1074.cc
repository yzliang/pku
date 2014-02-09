#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
using namespace std;

struct Instruction {
  // 0: move const->reg
  // 1: move var->reg
  // 2: move reg->var
  // 3: add
  // 4: sub
  int type;
  int op1, op2;
  Instruction() {}
  Instruction(int type, int op1, int op2): type(type), op1(op1), op2(op2) {}
};

struct State {
  double reg[2][2];
  double var[10];
};

map<string, int> name_ids;
int len[2];
Instruction ins[2][100];
double g[101][101];
State f[101][101];

int name_to_id(string& name) {
  int l = 0, r = name.size() - 1;
  while (name[l] == ' ' || name[l] == '\t' || name[l] == '\r') l++;
  while (name[r] == ' ' || name[r] == '\t' || name[r] == '\r') r--;
  name = name.substr(l, r - l + 1);
  if (name.find_first_not_of("0123456789") == string::npos)
    return -1;
  for (int i = 0; i < name.size(); i++)
    name[i] = tolower(name[i]);
  if (name_ids.find(name) == name_ids.end()) {
    int size = name_ids.size();
    name_ids[name] = size;
    return size;
  } else
    return name_ids[name];
}

void load_program(int p) {
  len[p] = 0;
  string line;
  string x, y, z;
  while (getline(cin, line)) {
    if (line.find("END") == 0) break;
    int i = line.find(':');
    if (i == string::npos) continue;  // Skip empty lines.
    x = line.substr(0, i);
    int j = line.find('+');
    if (j == string::npos)
      j = line.find('-');
    y = line.substr(i + 2, j - i - 2);
    z = line.substr(j + 1);
    // Generate instructions.
    int id = name_to_id(y);
    if (id == -1)
      ins[p][len[p]] = Instruction(0, 0, atoi(y.c_str()));
    else
      ins[p][len[p]] = Instruction(1, 0, id);
    id = name_to_id(z);
    if (id == -1)
      ins[p][len[p] + 1] = Instruction(0, 1, atoi(z.c_str()));
    else
      ins[p][len[p] + 1] = Instruction(1, 1, id);
    ins[p][len[p] + 2] = Instruction(line[j] == '+' ? 3 : 4, 0, 1);
    ins[p][len[p] + 3] = Instruction(2, name_to_id(x), 0);
    len[p] += 4;
  }
}

void execute(int m, int i, int j) {
  State temp = f[i][j];
  State* target;
  int off = m == 0 ? i : j;
  int steps;
  double ratio;
  // Initialize.
  if (i == len[0] || j == len[1]) {
    steps = (i == len[0]) ? (len[1] - j) : (len[0] - i);
    ratio = 1;
    target = &f[len[0]][len[1]];
  } else {
    steps = 1;
    ratio = 0.5;
    target = (m == 0) ? &f[i + 1][j] : &f[i][j + 1];
  }
  for (int k = off; k < off + steps; k++) {
    Instruction& ip = ins[m][k];
    switch (ip.type) {
      case 0:
        temp.reg[m][ip.op1] = ip.op2 * g[i][j];
        break;
      case 1:
        temp.reg[m][ip.op1] = temp.var[ip.op2];
        break;
      case 2:
        temp.var[ip.op1] = temp.reg[m][0];
        break;
      case 3:
        temp.reg[m][0] += temp.reg[m][1];
        break;
      case 4:
        temp.reg[m][0] -= temp.reg[m][1];
        break;
    }
  }
  // Forward update.
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      target->reg[i][j] += temp.reg[i][j] * ratio;
  for (int i = 0; i < 10; i++)
    target->var[i] += temp.var[i] * ratio;
}

void compute() {
  memset(g, 0, sizeof(g));
  g[0][0] = 1;
  memset(f, 0, sizeof(f));
  for (int i = 0; i <= len[0]; i++) {
    for (int j = 0; j <= len[1]; j++) {
      if (i < len[0] && j < len[1]) {
        g[i + 1][j] += g[i][j] / 2;
        g[i][j + 1] += g[i][j] / 2;
      }
      if (i < len[0]) execute(0, i, j);
      if (j < len[1]) execute(1, i, j);
    }
  }
}

int main() {
  int t;
  string line;
  cin >> t;
  getline(cin, line);
  for (; t > 0; t--) {
    name_ids.clear();
    load_program(0);
    load_program(1);
    compute();
    for (map<string, int>::iterator it = name_ids.begin(); it != name_ids.end();
        it++) {
      cout << fixed << setprecision(4) << f[len[0]][len[1]].var[it->second];
      cout << endl;
    }
    if (t > 1) cout << endl;
  }
  return 0;
}
