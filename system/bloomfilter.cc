
/**
 * A filter interface
 **/
class FilterInterface {
public: // public interface
  // add an item to the filter
  void Add(int item) = 0;
  // check if we have the item in filter
  bool Contain(int item) = 0;
  // remove an item
  void Del(int item) = 0;
  // number of items in the filter
  int Size() = 0;
  // size in bytes of the filter
  int SizeInBytes() = 0;
};

/**
 * Bloom Filter implementation
 **/
class BloomFilter : public FilterInterface {};
