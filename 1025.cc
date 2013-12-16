#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Visit {
  int id, time;
  Visit(int id, int time) : id(id), time(time) {}
};

struct Agent {
  char id;
  int stime; // time the agent is ready to act
  queue<Visit> visits;
  int type;  // -1: room, 0: going down, 1: going up
  int floor; // current floor id
  bool finished;
  bool operator<(const Agent& that) const {
    return id < that.id;
  }
};

vector<Agent> agents;
vector<vector<string> > logs;
char buffer[100];
int r_free[1011];  // next available time for rooms
int e_free[11][2];   // for elevators.

int free_time(Agent& a) {
  if (a.type >= 0)
    return e_free[a.floor][a.type];
  else
    return r_free[a.visits.front().id];
}

int get_time() {
  string s;
  cin >> s;
  int hh, mm, ss;
  sscanf(s.c_str(), "%d:%d:%d", &hh, &mm, &ss);
  return hh * 3600 + mm * 60 + ss;
}

string make_time(int t) {
  int hh = t / 3600;
  t %= 3600;
  int mm = t / 60;
  t %= 60;
  sprintf(buffer, "2d:2d:2d", hh, mm, t);
  return string(buffer);
}

void log_info(int i, int t1, int t2, const string& info) {
  logs[i].push_back(string());
  string& s = logs[i].back();
  s += make_time(t1);
  s += ' ';
  s += make_time(t2);
  s += ' ';
  s += info;
}

int main() {
  char id;
  while (cin >> id) {
    if (id == '.') break;
    agents.push_back(Agent());
    Agent& agent = agents.back();
    agent.stime = get_time();
    while (true) {
      int id, time;
      cin >> id;
      if (id == 0) break;
      cin >> time;
      if (id != agent.visits.back().id)
        agent.visits.push(Visit(id, time));
      else
        agent.visits.back().time += time;
    }
  }
  sort(agents.begin(), agents.end());
  // Everybody enters the building.
  logs.resize(agents.size());
  for (int i = 0; i < agents.size(); i++) {
    log_info(i, agents[i].stime, agents[i].stime + 30, "Entry");
    agents[i].stime += 30;
    agents[i].floor = 1;
    agents[i].finished = false;
    int id = agents[i].visits.front().id;
    agents[i].type = (id / 100 == 1) ? -1 : 1;  // to a room or up?
  }
  // Process events.
  while (true) {
    // Pick the next action.
    int min_time = INT_MAX;
    int j, type, room_id;
    char code;
    for (int i = 0; i < agents.size(); i++) {
      if (agents[i].finished) continue;
      int free = free_time(agents[i]);
      if (max(free, agents[i].stime) < min_time) {
        min_time = max(free, agents[i].stime);
        j = i;
        type = agents[i].type;
        if (agents[i].visits.empty())
          room_id = -1;
        else
          room_id = agents[i].visits.front().id;
      }
    }
    if (min_time == INT_MAX) break;
    // Process the event.
    if (agents[j].stime < min_time) {  // Has to wait?
      if (type >= 0) {
        log_info(j, agents[j].stime, min_time, "Waiting in elevator queue");
      } else {
        sprintf(buffer, "Waiting in front of room %04d", room_id);
        log_info(j, agents[j].stime, min_time, buffer);
      }
      agents[j].stime = min_time;
    }
    if (type >= 0) {
      // Use elevator.
      int target = (room_id == -1) ? 1 : room_id / 100;
      e_free[agents[j].floor][agents[j].type] = agents[j].stime + 5;
      log_info(j, agents[j].stime, 30 * abs(target - agents[j].floor),
               "Stay in elevator");
      agents[j].stime += 30 * abs(target - agents[j].floor);
      agents[j].floor = target;
      // Walk and set next action.
      if (room_id == -1) {
        log_info(j, agents[j].stime, agents[j].stime + 30, "Exit");
        agents[j].finished = true;
      } else {
        sprintf(buffer, "Transfer from elevator to room %04d", room_id);
        log_info(j, agents[j].stime, agents[j].stime + 10, buffer);
        agents[j].stime += 10;
        agents[j].type = -1;
      }
    } else {
      // Use room.
      int elapsed = agents[j].visits.front().time;
      r_free[room_id] = agents[j].stime + elapsed;
      sprintf(buffer, "Stay in room %04d", room_id);
      log_info(j, agents[j].stime, agents[j].stime + elapsed, buffer);
      agents[j].stime += elapsed;
      agents[j].visits.pop();
      // Set next action.
      if (agents[j].visits.empty()) {
        if (agents[j].floor == 1) {
          log_info(j, agents[j].stime, agents[j].stime + 30, "Exit");
        } else {
          sprintf(buffer, "Transfer from room %04d to elevator", room_id);
          log_info(j, agents[j].stime, agents[j].stime + 10, buffer);
          agents[j].stime += 10;
          agents[j].type = 0;
        }
      } else {
        int new_room_id = agents[j].visits.front().id;
        if (new_room_id / 100 == agents[j].floor) {
          sprintf(buffer, "Transfer from room %04d to room %04d", room_id,
                  new_room_id);
          log_info(j, agents[j].stime, agents[j].stime + 10, buffer);
          agents[j].stime += 10;
          agents[j].type = 0;
        } else {
          sprintf(buffer, "Transfer from room %04d to elevator", room_id);
          log_info(j, agents[j].stime, agents[j].stime + 10, buffer);
          agents[j].stime += 10;
          agents[j].type = (new_room_id / 100 < agents[j].floor) ? 0 : 1;
        }
      }
    }
  }
  // Output.
  for (int i = 0; i < agents.size(); i++) {
    cout << agents[i].id << endl;
    for (int j = 0; j < logs[i].size(); j++)
      cout << logs[i][j] << endl;
    cout << endl;
  }
  return 0;
}
