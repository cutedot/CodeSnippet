#pragma once

/**
 * Generic Key Value Store Interface
 **/
class KVS {
public:
  void Get(int key, int *value) = 0;
  void Put(int key, int value) = 0;
  void Del(int key) = 0;
};
