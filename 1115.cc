#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Answer {
  char code;
  string desc;
};

struct Question {
  string name, code;
  int code_map[128];
  vector<Answer> answers;
};

const string EMPTY = "      ";
const string NA = "     -";

typedef vector<Answer>::iterator AnsIter;

string survey;
vector<Question> questions;
int num_results;
int results[10000][100];

void read_survey() {
  string line;
  while (true) {
    if (line.empty())
      getline(cin, line);
    if (line[0] == '#')
      break;
    questions.push_back(Question());
    Question& question = questions.back();
    question.code = line.substr(0, 3);
    question.name = line.substr(4);
    // Read answers.
    while (true) {
      getline(cin, line);
      if (line[0] != ' ')
        break;
      question.answers.push_back(Answer());
      Answer& answer = question.answers.back();
      answer.code = line[1];
      answer.desc = line.substr(3);
      question.code_map[line[1]] = question.answers.size() - 1;
    }
  }
}

void read_results() {
  string line;
  while (true) {
    getline(cin, line);
    if (line[0] == '#')
      break;
    for (int i = 0; i < questions.size(); i++)
      results[num_results][i] = questions[i].code_map[line[i]];
    num_results++;
  }
}

int find_question(const string& line, int pos) {
  for (int i = 0; i < questions.size(); i++) {
    const string& code = questions[i].code;
    if (code[0] == line[pos] && code[1] == line[pos + 1] &&
        code[2] == line[pos + 2])
      return i;
  }
  return -1;
}

void print_question(Question& q) {
  cout << q.code << ' ' << q.name << endl;
  for (AnsIter i = q.answers.begin(); i != q.answers.end(); i++)
    cout << ' ' << i->code << ' ' << i->desc << endl;
}

void process_tables() {
  bool first = true;
  string line;
  while (true) {
    getline(cin, line);
    if (line[0] == '#')
      break;
    if (first)
      first = false;
    else
      cout << endl;
    // Compute statistics.
    int id1 = find_question(line, 0);
    int id2 = find_question(line, 4);
    int stats[10][10] = {0}, sum1[10] = {0}, sum2[10] = {0};
    for (int i = 0; i < num_results; i++) {
      stats[results[i][id1]][results[i][id2]]++;
      sum1[results[i][id1]]++;
      sum2[results[i][id2]]++;
    }
    // Title.
    cout << survey << " - " << line.substr(8) << endl;
    // Questions.
    Question& q1 = questions[id1];
    Question& q2 = questions[id2];
    print_question(q1);
    print_question(q2);
    cout << endl;
    // Table header.
    cout << EMPTY;
    for (AnsIter i = q2.answers.begin(); i != q2.answers.end(); i++)
      cout << ' ' << q2.code << ':' << i->code;
    cout << " TOTAL" << endl;
    // Table contents.
    for (int i = 0; i < q1.answers.size(); i++) {
      // Values.
      cout << ' ' << q1.code << ':' << q1.answers[i].code;
      for (int j = 0; j < q2.answers.size(); j++)
        cout << setw(6) << stats[i][j];
      cout << setw(6) << sum1[i] << endl;
      // Percentages for the row.
      cout << EMPTY;
      if (sum1[i] == 0) {
        for (int j = 0; j < q2.answers.size() + 1; j++)
          cout << NA;
        cout << endl;
      } else {
        for (int j = 0; j < q2.answers.size(); j++) {
          int percent = round((double) stats[i][j] / sum1[i] * 100);
          cout << setw(5) << percent << '%';
        }
        cout << (sum1[i] == 0 ? NA : "  100%") << endl;
      }
      // Percentages for columns.
      cout << EMPTY;
      for (int j = 0; j < q2.answers.size(); j++) {
        if (sum2[j] == 0)
          cout << NA;
        else {
          int percent = round((double) stats[i][j] / sum2[j] * 100);
          cout << setw(5) << percent << '%';
        }
      }
      cout << setw(5) << round((double) sum1[i] / num_results * 100) << '%';
      cout << endl;
    }
    // The last row.
    cout << " TOTAL";
    for (int i = 0; i < q2.answers.size(); i++)
      cout << setw(6) << sum2[i];
    cout << setw(6) << num_results << endl;
    cout << EMPTY;
    for (int i = 0; i < q2.answers.size(); i++) {
      int percent = round((double) sum2[i] / num_results * 100);
      cout << setw(5) << percent << '%';
    }
    cout << "  100%" << endl;
    cout << EMPTY;
    for (int i = 0; i < q2.answers.size() + 1; i++)
      cout << "  100%";
    cout << endl;
  }
}

int main() {
  getline(cin, survey);
  read_survey();
  read_results();
  process_tables();
  return 0;
}
