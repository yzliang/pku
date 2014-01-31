#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

typedef char Face[25][25];

struct Cube {
  int x, y, z;
  Cube(int x, int y, int z) : x(x), y(y), z(z) {}
};

int n;
Face origin[3], face[3];
Face buffer;

const int dx[] = {1, 0, -1, 0, 0, 0};
const int dy[] = {0, 0, 0, 0, -1, 1};
const int dz[] = {0, -1, 0, 1, 0, 0};

void dump(Face face) {
  cout << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << face[i][j];
    cout << endl;
  }
  cout << endl;
}

void rotate(Face face) {
  memcpy(buffer, face, sizeof(buffer));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      face[j][n - i - 1] = buffer[i][j];
}

void v_flip(Face face) {
  memcpy(buffer, face, sizeof(buffer));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      face[i][j] = buffer[n - i - 1][j];
}

void h_flip(Face face) {
  memcpy(buffer, face, sizeof(buffer));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      face[i][j] = buffer[i][n - j - 1];
}

/* V/H Flip and rotate the face. */
void shape(Face face, int x) {
  if (x & 1) rotate(face);
  if (x & 2) v_flip(face);
  if (x & 4) h_flip(face);
}

bool test_combo() {
  static bool null[25][25][25];  // some cubics are doomed to be null.
  memset(null, 0, sizeof(null));
  for (int x = 0; x < n; x++) {
    for (int z = 0; z < n; z++) {
      if (face[0][x][z] == '-') {
        for (int y = 0; y < n; y++)
          null[x][y][z] = true;
      }
    }
  }
  for (int y = 0; y < n; y++) {
    for (int z = 0; z < n; z++) {
      if (face[1][y][z] == '-') {
        for (int x = 0; x < n; x++)
          null[x][y][z] = true;
      }
    }
  }
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (face[2][x][y] == '-') {
        for (int z = 0; z < n; z++)
          null[x][y][z] = true;
      }
    }
  }
  // Possibility of casting the shadows.
  bool ok;
  for (int x = 0; x < n; x++) {
    for (int z = 0; z < n; z++) {
      if (face[0][x][z] == 'X') {
        ok = false;
        for (int y = 0; y < n; y++) {
          if (!null[x][y][z]) {
            ok = true;
            break;
          }
        }
        if (!ok) return false;
      }
    }
  }
  for (int y = 0; y < n; y++) {
    for (int z = 0; z < n; z++) {
      if (face[1][y][z] == 'X') {
        ok = false;
        for (int x = 0; x < n; x++) {
          if (!null[x][y][z]) {
            ok = true;
            break;
            }
        }
        if (!ok) return false;
      }
    }
  }
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (face[2][x][y] == 'X') {
        ok = false;
        for (int z = 0; z < n; z++) {
          if (!null[x][y][z]) {
            ok = true;
            break;
          }
        }
        if (!ok) return false;
      }
    }
  }
  // Flood-fill non-empty cells.
  queue<Cube> q;
  for (int x = 0; x < n && q.empty(); x++) {
    for (int y = 0; y < n && q.empty(); y++) {
      for (int z = 0; z < n && q.empty(); z++) {
        if (!null[x][y][z]) {
          q.push(Cube(x, y, z));
          null[x][y][z] = true;
        }
      }
    }
  }
  while (!q.empty()) {
    Cube head = q.front();
    q.pop();
    for (int i = 0; i < 6; i++) {
      int nx = head.x + dx[i], ny = head.y + dy[i], nz = head.z + dz[i];
      if (nx < 0 || nx == n || ny < 0 || ny == n || nz < 0 || nz == n) continue;
      if (!null[nx][ny][nz]) {
        null[nx][ny][nz] = true;
        q.push(Cube(nx, ny, nz));
      }
    }
  }
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      for (int z = 0; z < n; z++) {
        if (!null[x][y][z]) return false;
      }
    }
  }
  return true;
}

bool judge() {
  for (int i = 0; i < 8; i++) {
    memcpy(face[0], origin[0], sizeof(face[0]));
    shape(face[0], i);
    for (int j = 0; j < 8; j++) {
      memcpy(face[1], origin[1], sizeof(face[1]));
      shape(face[1], j);
      for (int k = 0; k < 8; k++) {
        memcpy(face[2], origin[2], sizeof(face[2]));
        shape(face[2], k);
        if (test_combo()) {
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
  int t = 0;
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < n; j++)
        cin >> origin[i][j];
    cout << "Data set " << ++t << ": ";
    if (judge())
      cout << "Valid set of patterns" << endl;
    else
      cout << "Impossible combination" << endl;
  }
  return 0;
}
