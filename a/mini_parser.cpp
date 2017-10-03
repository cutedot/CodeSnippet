#include "nested_array.h"

using namespace std;

// The core code of the min parser is moved to nested_array.h so that other
// project can use the parser to quickly build up the nested array

int main() {
  {
    // TEST 1
    cout << "TEST 1" << endl;
    string s = "[123,[456,[789]]]";
    NestedInteger ni = deserialize(s);
    cout << serialize(ni) << endl;
  }
  {
    // TEST 2
    cout << "TEST 2" << endl;
    string s = "324";
    cout << serialize(deserialize(s)) << endl;
  }
}
