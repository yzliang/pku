#include <iostream>
#include <string>
using namespace std;

int mem[256];

void simulate() {
  int ip = 0, a = 0, b = 0, temp;
  bool halt = false;
  while (!halt) {
    switch (mem[ip]) {
      case 0:
        a = mem[mem[ip + 1] * 16 + mem[ip + 2]];
        ip += 3;
        break;
      case 1:
        mem[mem[ip + 1] * 16 + mem[ip + 2]] = a;
        ip += 3;
        break;
      case 2:
        temp = a;
        a = b;
        b = temp;
        ip += 1;
        break;
      case 3:
        a += b;
        b = (a & 0xf0) >> 4;
        a &= 0x0f;
        ip += 1;
        break;
      case 4:
        a = (a + 1) & 0x0f;
        ip += 1;
        break;
      case 5:
        a = (a - 1) & 0x0f;
        ip += 1;
        break;
      case 6:
        if (a == 0)
          ip = mem[ip + 1] * 16 + mem[ip + 2];
        else
          ip += 3;
        break;
      case 7:
        ip = mem[ip + 1] * 16 + mem[ip + 2];
        break;
      case 8:
        halt = true;
    }
  }
}

int main() {
  string s;
  while (getline(cin, s)) {
    if (s[0] == '8') break;
    for (int i = 0; i < 256; i++) {
      if (s[i] >= '0' && s[i] <= '9')
        mem[i] = s[i] - '0';
      else
        mem[i] = s[i] - 'A' + 10;
    }
    simulate();
    for (int i = 0; i < 256; i++) {
      if (mem[i] >= 10)
        cout << (char)(mem[i] - 10 + 'A');
      else
        cout << (char)(mem[i] - 0 + '0');
    }
    cout << endl;
  }
  return 0;
}
