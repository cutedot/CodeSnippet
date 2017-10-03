# Just a list of stupid mistakes
-------
1. pop item from queue:
```cpp
// this is FIFO queue so push to back and pop from front
item = q.front();
q.pop();
```

pop item from stack:
```cpp
// stack always push to the top and pop from the top
item = q.top();
q.pop();
```

2. be careful about reference &

3. For iterator type question, given that we always call hasNext() before
   Next(), we can break the responsibility fo the two function into:
    - Next() just return the current item and initialize the move (not
      necessarily move the a valid item, but move to the next item blindly)
    - hasNext() do the navigation to the next ***valid*** item
