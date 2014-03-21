#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

struct Tree {
  char c;
  int w, h;
  Tree* lc, *rc;
};

int pos;
string code;
char canvas[100][100];

void stretch_h(Tree* tree, int new_h) {
  if (tree->c == '|') {
    stretch_h(tree->lc, new_h);
    stretch_h(tree->rc, new_h);
  } else if (tree->c == '-') {
    double d1 = (double) tree->lc->h * new_h / tree->h;
    double d2 = (double) tree->rc->h * new_h / tree->h;
    d1 = ceil(d1);
    d2 = floor(d2);
    stretch_h(tree->lc, d1);
    stretch_h(tree->rc, d2);
  }
  tree->h = new_h;
}

void stretch_w(Tree* tree, int new_w) {
  if (tree->c == '-') {
    stretch_w(tree->lc, new_w);
    stretch_w(tree->rc, new_w);
  } else if (tree->c == '|') {
    double d1 = (double) tree->lc->w * new_w / tree->w;
    double d2 = (double) tree->rc->w * new_w / tree->w;
    d1 = ceil(d1);
    d2 = floor(d2);
    stretch_w(tree->lc, d1);
    stretch_w(tree->rc, d2);
  }
  tree->w = new_w;
}

Tree* make_tree() {
  Tree* tree = new Tree;
  tree->c = code[pos++];
  if (tree->c == '|') {
    tree->lc = make_tree();
    tree->rc = make_tree();
    tree->w = tree->lc->w + tree->rc->w;
    tree->h = max(tree->lc->h, tree->rc->h);
    if (tree->lc->h < tree->h)
      stretch_h(tree->lc, tree->h);
    if (tree->rc->h < tree->h)
      stretch_h(tree->rc, tree->h);
  } else if (tree->c == '-') {
    tree->lc = make_tree();
    tree->rc = make_tree();
    tree->h = tree->lc->h + tree->rc->h;
    tree->w = max(tree->lc->w, tree->rc->w);
    if (tree->lc->w < tree->w)
      stretch_w(tree->lc, tree->w);
    if (tree->rc->h < tree->h)
      stretch_w(tree->rc, tree->w);
  } else {
    tree->lc = tree->rc = NULL;
    tree->w = tree->h = 2;
  }
  return tree;
}

void draw(int x, int y, char c) {
  if (c == '-' || c == '|') {
    if (canvas[x][y] == 0)
      canvas[x][y] = c;
  } else {
    if (canvas[x][y] < 'A' || canvas[x][y] > 'Z')
      canvas[x][y] = c;
  }
}

void draw(Tree* tree, int sx, int sy) {
  if (tree->c == '|') {
    draw(tree->lc, sx, sy);
    draw(tree->rc, sx, sy + tree->lc->w);
  } else if (tree->c == '-') {
    draw(tree->lc, sx, sy);
    draw(tree->rc, sx + tree->lc->h, sy);
  } else {
    canvas[sx][sy] = tree->c;
    draw(sx + tree->h, sy, '*');
    draw(sx, sy + tree->w, '*');
    draw(sx + tree->h, sy + tree->w, '*');
    for (int i = 1; i < tree->w; i++) {
      draw(sx, sy + i, '-');
      draw(sx + tree->h, sy + i, '-');
    }
    for (int i = 1; i < tree->h; i++) {
      draw(sx + i, sy, '|');
      draw(sx + i, sy + tree->w, '|');
    }
  }
}

void release(Tree* tree) {
  if (tree->c == '-' || tree->c == '|') {
    release(tree->lc);
    release(tree->rc);
  }
  delete tree;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> code;
    pos = 0;
    Tree* tree = make_tree();
    memset(canvas, 0, sizeof(canvas));
    draw(tree, 0, 0);
    cout << i << endl;
    for (int j = 0; j < tree->h + 1; j++) {
      for (int k = 0; k < tree->w + 1; k++)
        cout << (canvas[j][k] == 0 ? ' ' : canvas[j][k]);
      cout << endl;
    }
    release(tree);
  }
  return 0;
}
