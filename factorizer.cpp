// Millar Rabin Primality Test / Pollard Rho Algorithm
// work up to 2 ** 60
// 7 times slower than a^b mod m / O(n^{1/4}) gcd calls
// source : https://github.com/FlowerOfSorrow/Cpp_Implementations/blob/master/Numeric/Number_Theory/pollard_rho.sublime-snippet

long long mult(long long a, long long b, long long md) {
  long long ret = a * b - md * (long long) (1.L / md * a * b);
  return ret + md * (ret < 0) - md * (ret >= (long long) md);
}

long long power(long long a, long long b, long long md) {
  a %= md;
  long long ans = 1;
  while (b > 0) {
    if (b & 1) {
      ans = mult(ans, a, md);
    }
    a = mult(a, a, md);
    b >>= 1;
  }
  return ans;
}

bool is_prime(long long n) {
  if (n < 2 || n % 6 % 4 != 1) {
    return (n | 1) == 3;
  }
  long long s = __builtin_ctzll(n - 1);
  long long d = n >> s;
  long long A[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  for (long long a : A) {
    long long p = power(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) {
      p = mult(p, p, n);
    }
    if (p != n - 1 && i != s) {
      return false;
    }
  }
  return true;
}

long long pollard(unsigned long long n) {
  auto f = [n](long long x) {
    return mult(x, x, n) + 1;
  };
  unsigned long long x = 0, y = 0, t = 0;
  unsigned long long prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) {
      ++i;
      x = i;
      y = f(x);
    }
    q = mult(prd, max(x, y) - min(x, y), n);
    if (q > 0) {
      prd = q;
    }
    x = f(x);
    y = f(f(y));
  }
  return __gcd(prd, n);
}

vector<long long> factor(long long n) {
  assert(n > 0);
  if (n == 1) {
    return vector<long long>();
  }
  if (is_prime(n)) {
    return {n};
  }
  long long x = pollard(n);
  vector<long long> l = factor(x);
  vector<long long> r = factor(n / x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}
