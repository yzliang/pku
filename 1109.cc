#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct SecondaryEntry {
  string key;
  vector<int> pages;
};

struct PrimaryEntry {
  string key;
  vector<int> pages;
  vector<SecondaryEntry> entries;
};

string doc;
vector<PrimaryEntry> ind;

string trim(string& s) {
  int i = 0;
  while (i < s.size() && isspace(s[i]))
    i++;
  if (i == s.size())
    return "";
  int j = s.size() - 1;
  while (isspace(s[j]))
    j--;
  return s.substr(i, j - i + 1);
}

void put_primary(string s, int page) {
  s = trim(s);
  PrimaryEntry* entry = NULL;
  for (int i = 0; i < ind.size(); i++) {
    if (ind[i].key == s) {
      entry = &ind[i];
      break;
    }
  }
  if (!entry) {
    ind.push_back(PrimaryEntry());
    ind.back().key = s;
    entry = &ind.back();
  }
  if (entry->pages.empty() || entry->pages.back() != page)
    entry->pages.push_back(page);
}

void put_secondary(string a, string b, int page) {
  a = trim(a);
  b = trim(b);
  PrimaryEntry* entry = NULL;
  for (int i = 0; i < ind.size(); i++) {
    if (ind[i].key == a) {
      entry = &ind[i];
      break;
    }
  }
  if (!entry) {
    ind.push_back(PrimaryEntry());
    entry = &ind.back();
    entry->key = a;
  }
  SecondaryEntry* second = NULL;
  for (int i = 0; i < entry->entries.size(); i++) {
    if (entry->entries[i].key == b) {
      second = &entry->entries[i];
      break;
    }
  }
  if (!second) {
    entry->entries.push_back(SecondaryEntry());
    entry->entries.back().key = b;
    second = &entry->entries.back();
  }
  if (second->pages.empty() || second->pages.back() != page)
    second->pages.push_back(page);
}

void analyze(string s, int page) {
  int i = s.find('%'), j = s.find('$');
  if (i == -1) {
    if (j == -1)
      put_primary(s, page);
    else
      put_secondary(s.substr(0, j), s.substr(j + 1), page);
  } else {
    if (j == -1)
      put_primary(s.substr(i + 1), page);
    else
      put_secondary(s.substr(i + 1, j - i - 2), s.substr(j + 1), page);
  }
}

void sort_keys(int ord[], string key[], int n) {
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (key[ord[i]] > key[ord[j]]) {
        int temp = ord[i];
        ord[i] = ord[j];
        ord[j] = temp;
      }
}

string lower(const string& s) {
  string ret;
  ret.reserve(s.size());
  for (int i = 0; i < s.size(); i++)
    ret += tolower(s[i]);
  return ret;
}

int main() {
  int id = 1;
  doc.resize(10000);
  string line;
  while (cin >> line) {
    if (line == "**") break;
    doc = line;
    while (cin >> line) {
      if (line == "*") break;
      doc += ' ';
      doc += line;
    }
    // Build index.
    ind.clear();
    int i = 0, page = 1;
    while (i < doc.size()) {
      if (doc[i] == '&') {
        page++;
        i++;
      } else if (doc[i] == '{') {
        int j = i + 1;
        while (doc[j] != '}')
          j++;
        analyze(doc.substr(i + 1, j - i - 1), page);
        i = j + 1;
      } else
        i++;
    }
    // Output.
    cout << "DOCUMENT " << id++ << endl;
    int ord[20];
    string key[20];
    for (int i = 0; i < ind.size(); i++) {
      ord[i] = i;
      key[i] = lower(ind[i].key);
    }
    sort_keys(ord, key, ind.size());
    for (int i = 0; i < ind.size(); i++) {
      const PrimaryEntry& first = ind[ord[i]];
      // Dump primary.
      cout << first.key;
      for (int j = 0; j < first.pages.size(); j++)
        cout << ", " << first.pages[j];
      cout << endl;
      // Dump secondary.
      int ord2[5];
      string key2[5]; 
      for (int j = 0; j < first.entries.size(); j++) {
        ord2[j] = j;
        key2[j] = lower(first.entries[j].key);
      }
      sort_keys(ord2, key2, first.entries.size());
      for (int j = 0; j < first.entries.size(); j++) {
        const SecondaryEntry& second = first.entries[ord2[j]];
        cout << "+ " << second.key;
        for (int k = 0; k < second.pages.size(); k++)
          cout << ", " << second.pages[k];
        cout << endl;
      }
    }
  }
  return 0;
}
