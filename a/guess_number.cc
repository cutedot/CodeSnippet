#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class guessGame {
public:
  guessGame(string s) : secret_(s), done_(false), count_(0) {}

  int getCount() const { return count_; }
  string getSecret() const { return secret_; }

  string getHint(string guess) {
    ++count_;
    int s[10], g[10];
    int bull = 0, cow = 0;
    memset(s, 0, sizeof(int) * 10);
    memset(g, 0, sizeof(int) * 10);
    for (int i = 0; i < secret_.size(); ++i) {
      if (secret_[i] == guess[i]) {
        ++bull;
      } else {
        ++s[secret_[i] - '0'];
        ++g[guess[i] - '0'];
      }
    }
    for (int i = 0; i < secret_.size(); ++i) {
      cow += min(s[i], g[i]);
    }
    return to_string(bull) + "A" + to_string(cow) + "B";
  }

  string guess() {
    string subset = "";
    string res;
    // initial guess
    for (int i = 0; i < 10; ++i) {
      string g(4, '0' + i);
      string h = getHint(g);
      if (h[0] != 0) {
        subset += string(h[0] - '0', '0' + i);
      }
    }

    // try out all permutation
    bt(subset, res, 0);
    return res;
  }

  void bt(string &subset, string &res, int idx) {
    if (idx == subset.size()) {
      string h = getHint(subset);
      if (h[0] == '4') {
        res = subset;
        done_ = true;
        return;
      }
    }
    for (int i = idx; i < subset.size(); ++i) {
      if (done_)
        return;
      swap(subset[idx], subset[i]);
      bt(subset, res, idx + 1);
      swap(subset[idx], subset[i]);
    }
  }

private:
  string secret_;
  bool done_;
  int count_;
};
int main() {
  {
    srand(time(NULL));
    guessGame game(to_string((1000 + rand()) % 10000));
    cout << "Secret : " << game.getSecret() << endl;
    cout << "Guess  : " << game.guess() << endl;
    cout << "In " << game.getCount() << " guesses" << endl;
  }
}
