#include <cmath>
#include <cstdio>
using namespace std;

struct Color {
  int r, g, b;
};

Color target[16];

double dis(Color& a, Color& b) {
  int dr = a.r - b.r;
  int dg = a.g - b.g;
  int db = a.b - b.b;
  return sqrt(dr * dr + dg * dg + db * db);
}

int main() {
  for (int i = 0; i < 16; i++)
    scanf("%d %d %d", &target[i].r, &target[i].g, &target[i].b);
  Color c;
  while (true) {
    scanf("%d %d %d", &c.r, &c.g, &c.b);
    if (c.r == -1) break;
    int ans = 0;
    double min_dis = dis(c, target[0]);
    for (int i = 1; i < 16; i++) {
      double new_dis = dis(c, target[i]);
      if (new_dis < min_dis) {
        ans = i;
        min_dis = new_dis;
      }
    }
    printf("(%d,%d,%d) maps to (%d,%d,%d)\n", c.r, c.g, c.b, target[ans].r,
        target[ans].g, target[ans].b);
  }
  return 0;
}
