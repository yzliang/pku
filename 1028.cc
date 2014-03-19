// 2010-04-23 17:50:04
#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<string> forward, backward;

int main()
{
  string command;
  string currentPage = "http://www.acm.org/";
  string ignore = "Ignored\n";
  while (true)
  {
    getline(cin, command);
    if (command == "QUIT")
      break;
    else if (command == "FORWARD")
    {
      if (forward.empty())
      {
        cout << ignore;
        continue;
      }
      else
      {
        backward.push(currentPage);
        currentPage = forward.top();
        forward.pop();
      }
    }
    else if (command == "BACK")
    {
      if (backward.empty())
      {
        cout << ignore;
        continue;
      }
      else
      {
        forward.push(currentPage);
        currentPage = backward.top();
        backward.pop();
      }
    }
    else
    {
      /* process the 'VISIT' command */
      while (!forward.empty())
        forward.pop();
      backward.push(currentPage);
      currentPage = command.substr(6);
    }
    cout << currentPage << '\n';
  }
  return 0;
}
