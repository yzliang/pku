#include <cstring>
#include <iostream>
using namespace std;

struct Poly {
  int deg;
  bool x[2002];
};

Poly f, g, h;

void read(Poly& p) {
  cin >> p.deg;
  int x;
  for (int i = p.deg - 1; i >= 0; i--) {
    cin >> x;
    p.x[i] = x == 1;
  }
}

void multiply() {
  int deg = f.deg + g.deg - 1;
  bool x[2001] = {0};
  for (int i = 0; i < f.deg; i++) {
    for (int j = 0; j < g.deg; j++) {
      if (f.x[i] && g.x[j])
        x[i + j] = !x[i + j];
    }
  }
  f.deg = deg;
  memcpy(f.x, x, sizeof(x));
}

void modulo() {
  while (f.deg >= h.deg) {
    int q = f.deg - h.deg;
    for (int i = 0; i < h.deg; i++) {
      if (h.x[i])
        f.x[i + q] = !f.x[i + q];
    }
    while (f.deg > 0 && !f.x[f.deg - 1])
      f.deg--;
  }
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    read(f);
    read(g);
    read(h);
    multiply();
    modulo();
    cout << f.deg << ' ';
    for (int i = f.deg - 1; i >= 0; i--)
      cout << (int)(f.x[i]) << ' ';
    cout << endl;
  }
  return 0;
}
