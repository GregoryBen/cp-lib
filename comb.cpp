const int md = (int) ...|;

struct Comb {
  int n;
  vector<int> F, G;

  long long C(int x, int y) {
    if (x < y || y < 0) return 0;
    return (long long) F[x] * G[y] % md * G[x - y] % md;
  }

  long long P(int x, int y) {
    if (x < y || y < 0) return 0;
    return (long long) F[x] * G[x - y] % md;
  }

  Comb(int _n) : n(_n) {
    F.resize(n);
    G.resize(n);
    vector<int> inv(n);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
      inv[i] = (int) ((md - md / i) * (long long) inv[md % i] % md);
    }
    F[0] = G[0] = 1;
    for (int i = 1; i <= n; i++) {
      F[i] = (int) ((long long) F[i - 1] * i % md);
      G[i] = (int) ((long long) G[i - 1] * inv[i] % md);
    }
  }
};
