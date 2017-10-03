#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class NestedInteger {
public:
  // Constructor initializes an empty nested list.
  NestedInteger() { is_integer_ = false; }

  // Constructor initializes a single integer.
  NestedInteger(int value) {
    is_integer_ = true;
    integer_ = value;
  }

public:
  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  bool isInteger() const { return is_integer_; }

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer The result is undefined if this NestedInteger holds a nested
  // list
  int getInteger() const { return integer_; }

  // Set this NestedInteger to hold a single integer.
  void setInteger(int value) { integer_ = value; }

  // Set this NestedInteger to hold a nested list and adds a nested integer to
  // it.
  void add(const NestedInteger &ni) { list_.push_back(ni); }

  // Return the nested list that this NestedInteger holds, if it holds a nested
  // list The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger> &getList() const { return list_; }

private:
  bool is_integer_;
  int integer_;
  vector<NestedInteger> list_;
};

// miniParser code
NestedInteger buildNestedInteger(istringstream &in) {
  if (in.peek() == '[') {
    in.get(); // consume the left bracket and create a new list
    NestedInteger ni;
    while (in.peek() != ']') {
      ni.add(buildNestedInteger(in));
      if (in.peek() == ',') {
        in.get(); // consume ','
      }
    }
    // meet right bracket
    in.get();
    return ni;
  } else {
    // must be number
    int num;
    in >> num;
    NestedInteger ni(num);
    return ni;
  }
}

NestedInteger deserialize(string s) {
  // create NestedInteger recursively
  istringstream in(s);
  return buildNestedInteger(in);
}

string serialize(NestedInteger ni) {
  if (ni.isInteger()) {
    return to_string(ni.getInteger());
  } else {
    string ret = "[";
    vector<NestedInteger> l = ni.getList();
    for (int i = 0; i < l.size(); ++i) {
      // comma sperated
      ret += serialize(l[i]);
      if (i != l.size() - 1) {
        ret += ",";
      }
    }
    ret += "]";
    return ret;
  }
}
