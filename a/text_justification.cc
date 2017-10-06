#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> fullJustify(vector<string> &words, int maxWidth) {
  vector<string> text;
  int i = 0; // iterate through all words
  int k = 0; // number items in last line
  int l = 0; // current length of the line
  while (i < words.size()) {
    vector<string> tmp;
    k = l = 0;
    while ((k + i) < words.size() &&
           (l + words[i + k].size() + tmp.size()) <= maxWidth) {
      l += words[i + k].size();
      tmp.push_back(words[i + k]);
      ++k;
    }

    // emit this line
    string line = tmp[0];
    if (tmp.size() > 1) {
      for (int j = 0; j < tmp.size() - 1; ++j) {
        // int nws = min(ws, maxWidth - l);
        int nws;
        // XXX: this part is really tricky
        if (i + k >= words.size()) {
          // last word
          nws = 1;
        } else {
          nws = (maxWidth - l) / (k - 1) + (j < ((maxWidth - l) % (k - 1)));
        }
        line += string(nws, ' ');
        line += tmp[j + 1];
      }
    } else {
      line += string(maxWidth - l, ' ');
    }
    text.push_back(line);

    i = i + k;
  }
  return text;
}

int main() {
  {
    cout << "TEST 1" << endl;
    vector<string> words{"This",          "is", "an", "example", "of", "text",
                         "justification."};
    auto text = fullJustify(words, 16);
    for (auto l : text) {
      cout << l << endl;
    }
    cout << endl;
  }
  {
    cout << "TEST 2" << endl;
    vector<string> words{""};
    auto text = fullJustify(words, 0);
    for (auto l : text) {
      cout << l << endl;
    }
    cout << endl;
  }
  {
    cout << "TEST 3" << endl;
    vector<string> words{};
    auto text = fullJustify(words, 16);
    for (auto l : text) {
      cout << l << endl;
    }
    cout << endl;
  }
  {
    cout << "TEST 4" << endl;
    vector<string> words{"a"};
    auto text = fullJustify(words, 1);
    for (auto l : text) {
      cout << l << endl;
    }
    cout << endl;
  }
  {
    cout << "TEST 5" << endl;
    vector<string> words{"What", "must", "be", "shall", "be."};
    auto text = fullJustify(words, 12);
    for (auto l : text) {
      cout << l << endl;
    }
    cout << endl;
  }
}
