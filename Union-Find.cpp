#include <bits/stdc++.h>
#define LL_INF 9223372036854775807
#define INT_INF 2147483647
using namespace std;
using ll = long long;

struct unionfind
{
  // v[i]=iが親なら-1*その集合のサイズ,違うなら親のindex
  vector<int> v;

  unionfind(int n)
  {
    v.resize(n, -1);
  }

  int root(int k)
  {
    if (v[k] >= 0)
    {
      v[k] = root(v[k]);
      return v[k];
    }
    return k;
  }

  void unite(int x, int y)
  {
    int x_s, y_s;
    x_s = root(x);
    y_s = root(y);
    if (x_s == y_s)
      return;
    v[x_s] += v[y_s];
    v[y_s] = x_s;
  }

  bool same(int x, int y)
  {
    return root(x) == root(y);
  }

  int size(int x)
  {
    int pa = root(x);
    return -v[pa];
  }
};

int main()
{
  int n;
  cin >> n;
  unionfind tree(n);
  // tree.unite(x,y);
  // tree.same(x,y);
  // tree.root(x);
  // tree.size(x);
  while (true)
  {
    string s;
    cin >> s;
    if (s == "unite")
    {
      int x, y;
      cin >> x >> y;
      tree.unite(x, y);
    }
    else if (s == "size")
    {
      int x;
      cin >> x;
      cout << tree.size(x) << endl;
    }
    else
    {
      int x;
      cin >> x;
      int ansx = tree.root(x);
      cout << "-------------" << endl;
      cout << ansx << endl;
      cout << "---------------" << endl;
    }
  }
}
