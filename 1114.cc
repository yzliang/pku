#include <cctype>
#include <iostream>
#include <map>
#include <string>
using namespace std;

typedef map<string, int> Map;

struct Parser {
  void parse_element(const char* p, const char* q, int factor) {
    if (isalpha(*p))
      elem_map[string(p, q - p)] += factor;
    else
      parse_sequence(p + 1, q - 1, factor);
  }

  // <sequence> := <element>[<number>] {<element>[<number>]}
  void parse_sequence(const char* p, const char* q, int factor) {
    while (p != q) {
      // Grab <element>: [p, i)
      const char* i = p;
      if (*p == '(') {
        int bra = 0;
        do {
          if (*i == '(')
            bra++;
          else if (*i == ')') {
            bra--;
          }
          i++;
        } while (bra != 0);
      } else {
        i++;
        if (islower(*i))
          i++;
      }
      // Grab optional <number>.
      int num = 0;
      const char* j = i;
      while (isdigit(*j))
        num = num * 10 + (*j++ - '0');
      if (num == 0)
        num = 1;
      // Parse element.
      parse_element(p, i, factor * num);
      p = j;
    }
  }

  // <term> := [<number>]<sequence>
  void parse_term(const char* p, const char* q) {
    int factor = 0;
    while (isdigit(*p))
      factor = 10 * factor + (*p++ - '0');
    if (factor == 0)
      factor = 1;
    parse_sequence(p, q, factor);
  }

  void parse_formula(const char* p) {
    elem_map.clear();
    while (true) {
      const char* q = p + 1;
      while (*q && *q != '+')
        q++;
      parse_term(p, q);
      if (*q == '+')
        p = q + 1;
      else
        break;
    }
  }

  void dump() {
    for (Map::iterator i = elem_map.begin(); i != elem_map.end(); i++)
      cout << i->first << ' ' << i->second << endl;
  }

  Map elem_map;
} left_parser, right_parser;

string left_str, right_str;

int main() {
  int n;
  cin >> left_str;
  left_parser.parse_formula(left_str.c_str());
  cin >> n;
  for (; n > 0; n--) {
    cin >> right_str;
    right_parser.parse_formula(right_str.c_str());
    bool equal = left_parser.elem_map == right_parser.elem_map;
    cout << left_str << (equal ? "==" : "!=") << right_str << endl;
  }
  return 0;
}
