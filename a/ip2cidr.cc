#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

long ipToLong(string ip) {
  long ret = 0;
  istringstream in(ip);
  in >> ret;
  while (!in.eof()) {
    int i;
    char c;
    in >> c;
    in >> i;
    ret = (ret << 8) + i;
  }
  return ret;
}

string longToIp(long val) {
  string ret;
  while (val > 0) {
    ret = to_string(val & 0xff) + '.' + ret;
    val = (val >> 8);
  }
  ret.pop_back();
  return ret;
}

vector<string> range2cidr(string start, string end) {
  long s = ipToLong(start), e = ipToLong(end);
  vector<string> res;

  while (s <= e) {
    // identify the last one in s
    // e.g. 0xf0 & (-0xf0) = 0x10
    int lastOne = s & (-s);
    int maxMask = 32 - int(log(lastOne) / log(2));
    int maxDiff = 32 - int(floor(log(e - s + 1) / log(2)));
    maxMask = max(maxMask, maxDiff);
    string ip = longToIp(s);
    res.push_back(ip + "/" + to_string(maxMask));
    s += int(pow(2, 32 - maxMask));
  }
  return res;
}

void printResult(vector<string> res) {
  for (auto s : res) {
    cout << s << endl;
  }
}
int main() {
  {
    string start = "192.168.1.232";
    string end = "192.222.0.0";

    printResult(range2cidr(start, end));
  }
}
