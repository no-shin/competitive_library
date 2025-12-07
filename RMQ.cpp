struct RMQ
{
  const int INF = 0;
  int n;           // 葉の数
  vector<int> dat; // 完全二分木の配列
  RMQ(int n_) : n(), dat(n_ * 4, INF)
  { // 葉の数は 2^x の形
    int x = 1;
    while (n_ > x)
    {
      x *= 2;
    }
    n = x;
  }
  void update(int i, int x)
  {
    i += n - 1;
    dat[i] += x;
    while (i > 0)
    {
      i = (i - 1) / 2; // parent
      dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
    }
  }
  // 半開区間[l,r)
  // the minimum element of [a,b)
  int query(int a, int b) { return query_sub(a, b, 0, 0, n); }
  int query_sub(int a, int b, int k, int l, int r)
  {
    if (r <= a || b <= l)
    {
      return INF;
    }
    else if (a <= l && r <= b)
    {
      return dat[k];
    }
    else
    {
      int vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
      int vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
      return vl + vr;
    }
  }
};
