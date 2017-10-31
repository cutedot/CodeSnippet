#include <iostream>

class TokenBucket {
public:
  TokenBucket(const string &key, int capacity, double refilltime,
              double refillamount)
      : key_(key), max_amount_(capacity), refill_time_(0.0),
        refill_time_(refilltime), refill_amount_(refillamount), count_(0),
        last_update_(0.0) {}
  ~TokenBucket() {}

  bool Acquire(int n = 1) {
    // calculate current available bucket
    double curr_time = NowMicro();
    double delta = (curr_time - last_update_) / refill_time_ * refill_amount_;
    count_ = min(max_amount_, count_ + delta);
    last_update_ = curr_time;
    // consume
    if (count_ > n) {
      count_ -= n;
      return true;
    } else {
      return false;
    }
  }

private:
  string key_; // unique idenfier of the bucket
  double max_amount_;
  double refill_time_; // in micros
  double refill_amount_;
  double count_;
  double last_update_;
};
