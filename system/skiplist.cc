

template <typename Key, typename Value> class SkipList {
private: // skiplist node
  struct Node {
  public:
    Node() {}
    ~Node() {}

  public:
  private:
    Key key_;
    Value value_;
  };

public: // public interface
  bool Get(const Key &key, Value *value) {}

  bool Put(const Key &key, const Value &value) {}

  bool Del(const Key &key) {}
}
