const int md = (int) ...;

vector<int> F;
vector<int> G;

long long C(int x, int y) {
  if (x < y || y < 0) return 0;
  return (long long) F[x] * G[y] % md * G[x - y] % md;
}

long long P(int x, int y) {
  if (x < y || y < 0) return 0;
  return (long long) F[x] * G[x - y] % md;
}

void init(int n) {
  F.resize(n + 1);
  G.resize(n + 1);
  vector<int> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = (md - md / i) * (long long) inv[md % i] % md;
  }
  F[0] = G[0] = 1;
  for (int i = 1; i <= n; i++) {
    F[i] = (long long) F[i - 1] * i % md;
    G[i] = (long long) G[i - 1] * inv[i] % md;
  }
}
