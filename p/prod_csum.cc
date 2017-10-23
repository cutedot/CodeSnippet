#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

using namespace std;

class ProducerConsumer {
public:
  ProducerConsumer(int capacity)
      : mu_(), cv_prod_(), cv_csum_(), max_cap_(capacity) {}

  // producer
  void Produce(int item) {
    unique_lock<mutex> l(mu_);

    while (data_.size() == max_cap_) {
      cv_prod_.wait(l);
    }
    data_.push(item);
    cv_csum_.notify_one();
  }

  // consumer
  int Consume() {
    unique_lock<mutex> l(mu_);
    while (data_.size() == 0) {
      cv_csum_.wait(l);
    }
    int item = data_.front();
    data_.pop();

    cv_prod_.notify_one();
    return item;
  }

private:
  mutex mu_;
  condition_variable cv_prod_;
  condition_variable cv_csum_;
  queue<int> data_;
  int max_cap_;
};

int main() {
  ProducerConsumer *pc = new ProducerConsumer(3);
  thread t1([pc]() {
    for (int i = 0; i < 10; ++i) {
      this_thread::sleep_for(chrono::microseconds(rand() % 1000));
      pc->Produce(i);
      string output = "Produce " + to_string(i);
      cout << output << endl;
    }
  });
  thread t2([pc]() {
    for (int i = 0; i < 10; ++i) {
      this_thread::sleep_for(chrono::microseconds(rand() % 1000));
      string output = "Consume " + to_string(pc->Consume());
      cout << output << endl;
    }
  });
  // t1.detach();
  // t2.detach();

  t1.join();
  t2.join();
}
