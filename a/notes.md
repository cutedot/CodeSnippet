# Just a list of stupid mistakes
-------

Overall, practicing for Airbnb interview questions is definitely more fun than
solving those leetcode questions. Here are a list of stupid mistakes I made as
well as a set of templates I summarized during the preparation.

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

4. To use object in priority queue, need to provide copy assignment operator=.

5. DFS template:
```cpp
dfs(u) {
  visit(u);
  for (auto i : u.neighbors()) {
    visit(i)
  }
}
```

6. BFS template:
```cpp
queue<item> q;
// initial item
q.push(start);

while (!q.empty()) {
  i = q.top();
  q.pop();

  visite(q);

  for (auto j : q.neighbors()) {
    if (visited[j]) {
      q.push(j);
    }
  }
}
```
But keep in mind that what information you want to keep track of. Essentially
you want to keep track of the current state of whatever item you are searching,
so extra memory copy is inevitable.

7. A\* template
```cpp
priority_queue<item> pq;
pq.push(start);

while (!pq.empty()) {
  i = q.top();
  q.pop();

  visit(q);
  
  for (auto j : q.neighbors()) {
    if (visited[j]) {
      q.push(j);
    }
  }
}
```

8. Representation of a graph
- The most generic way is to use `map<int, set<int>>` so we can handle discrete
  keys.
- Simpler way would be just to use `vector<vector<int>>` assume all nodes are
  present which may not be true in cases like alien dictionary
