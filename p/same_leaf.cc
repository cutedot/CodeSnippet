#include <iostream>
#include <stack>

using namespace std;

//
// Check if two binary trees have the same leaf nodes
//

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

class LeafIterator {
public:
  LeafIterator(TreeNode *root) {
    TreeNode *r = root;
    while (r) {
      st_.push(r);
      r = r->left;
    }
  }

  bool HasNext() { return !st_.empty(); }

  TreeNode *Next() {
    TreeNode *n = st_.top();
    st_.pop();

    TreeNode *r = n->right;
    while (r) {
      st_.push(r);
      r = r->left;
    }
    return n;
  }

  TreeNode *Peek() { return st_.top(); }

  TreeNode *NextLeaf() {
    while (HasNext()) {
      TreeNode *p = Peek();
      if (p->left == NULL && p->right == NULL) {
        return Next(); // return leaf nodes
      } else {
        Next(); // throw away non-leaf nodes
      }
    }
    return NULL;
  }

private:
  stack<TreeNode *> st_;
};

bool SameLeaf(TreeNode *r1, TreeNode *r2) {
  LeafIterator it1(r1);
  LeafIterator it2(r2);

  while (it1.HasNext() && it2.HasNext()) {
    TreeNode *l1 = it1.NextLeaf();
    TreeNode *l2 = it2.NextLeaf();

    if (l1->value != l2->value) {
      return false;
    }
  }
  if (it1.HasNext() || it2.HasNext()) {
    return false;
  }
  return true;
}

//
//         r(1)                                     z(3)
//        /  \                                      / \
//      a(2) b(3)             VS                  x(1) v(5)
//            / \                                 /     / \
//          c(4) d(5)                           y(2)  u(4) w(6)
//                  \
//                  e(6)

int main() {
  TreeNode r(1), a(2), b(3), c(4), d(5), e(6);
  r.left = &a;
  r.right = &b;
  b.left = &c;
  b.right = &d;
  d.right = &e;

  TreeNode x(1), y(2), z(3), u(4), v(5), w(6);
  z.left = &x;
  z.right = &v;
  x.left = &y;
  v.left = &u;
  v.right = &w;

  cout << SameLeaf(&r, &z) << endl;

  TreeNode p(7);
  w.right = &p;

  cout << SameLeaf(&r, &z) << endl;
}
