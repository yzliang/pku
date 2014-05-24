#include <cstring>
#include <iostream>
using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
const char ch[4] = {'.', '!', 'X', '#'};

int n;
int d[16];
int a[20][20], b[20][20];

int main() {
  cin >> n;
  for (int i = 0; i < 16; i++)
    cin >> d[i];
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 20; j++)
      cin >> a[i][j];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 20; j++) {
      for (int k = 0; k < 20; k++) {
        int sum = a[j][k];
        for (int l = 0; l < 4; l++) {
          int nx = j + dx[l], ny = k + dy[l];
          if (nx >= 0 && nx < 20 && ny >= 0 && ny < 20)
            sum += a[nx][ny];
        }
        b[j][k] = a[j][k] + d[sum];
        if (b[j][k] < 0)
          b[j][k] = 0;
        else if (b[j][k] > 3)
          b[j][k] = 3;
      }
    }
    memcpy(a, b, sizeof(a));
  }
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++)
      cout << ch[a[i][j]];
    cout << endl;
  }
  return 0;
}
