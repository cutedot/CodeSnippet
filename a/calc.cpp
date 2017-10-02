#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int calc(string s) {
  char op, last_op = '+';
  int term = 0, res = 0;

  istringstream in(s);

  in >> term;
  res = term;
  while (!in.eof()) {
    // leading whitespace
    while (in.peek() == ' ') {
      in.get();
    }
    int num;
    // get the op
    in >> op;
    in >> num;
    // trailing whitespace
    while (in.peek() == ' ') {
      in.get();
    }
    cout << op << " " << num << endl;
    if (op == '+') {
      term = num;
      res += num;
      last_op = '+';
    } else if (op == '-') {
      term = num;
      res -= num;
      last_op = '-';
    } else if (op == '*') {
      if (last_op == '+') {
        res -= term; // revert
        term = term * num;
        res += term;
      } else if (last_op == '-') {
        res += term;
        term = term * num;
        res -= term;
      }
    } else if (op == '/') {
      if (last_op == '+') {
        res -= term; // revert
        term = term / num;
        res += term;
      } else if (last_op == '-') {
        res += term;
        term = term / num;
        res -= term;
      }
    }
  }
  return res;
}

int main() {
  /*
  {
    // TEST 1
    string s = "3+2*2";
    cout << calc(s) << endl;
  }
  {
    // TEST 2
    string s = "3+5 / 2";
    cout << calc(s) << endl;
  }
  */
  {
    // TEST 3
    string s = "  3  /  2   ";
    cout << calc(s) << endl;
  }
}
