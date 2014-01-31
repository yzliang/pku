#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

string encode[256];
map<string, char> decode;

string codes[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
  "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...",
  "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

void preprocess() {
  for (int i = 0; i < 26; i++) {
    encode['A' + i] = codes[i];
    decode.insert(make_pair(codes[i], 'A' + i));
  }
  encode['_'] = "..--";
  decode.insert(make_pair("..--", '_'));
  encode['.'] = "---.";
  decode.insert(make_pair("---.", '.'));
  encode[','] = ".-.-";
  decode.insert(make_pair(".-.-", ','));
  encode['?'] = "----";
  decode.insert(make_pair("----", '?'));
}

int main() {
  preprocess();
  int t;
  cin >> t;
  for (int id = 1; id <= t; id++) {
    string a, b;
    cin >> a;
    vector<int> lens;
    for (int i = 0; i < a.size(); i++) {
      b.append(encode[a[i]]);
      lens.push_back(encode[a[i]].size());
    }
    reverse(lens.begin(), lens.end());
    a.clear();
    int i = 0, j = 0;
    while (j < lens.size()) {
      a.append(1, decode[b.substr(i, lens[j])]);
      i += lens[j++];
    }
    cout << id << ": " << a << endl;
  }
  return 0;
}
