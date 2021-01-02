vector<int> lp;
vector<int> prime;

void generate_primes_linear_time(int n) {
  assert(n > 1);
  lp.resize(n + 1, 0);
  prime.clear();
  for (int i = 2; i <= n; i++) {
    if (lp[i] == 0) {
      lp[i] = i;
      prime.emplace_back(i);
    }
    for (int p : prime) {
      if (p > lp[i] || i * p > n) {
        break;
      }
      lp[i * p] = p;
    }
  }
}
