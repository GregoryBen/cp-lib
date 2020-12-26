// Millar Rabin Primality Test / Pollard Rho Algorithm
// 7 times slower than a^b mod m / O(n^{1/4}) gcd calls
// source : https://github.com/FlowerOfSorrow/Cpp_Implementations/blob/master/Numeric/Number_Theory/pollard_rho.sublime-snippet

using ull = unsigned long long;

ull mult(ull a, ull b, ull md) {
  long long ret = a * b - md * ull(1.L / md * a * b);
  return ret + md * (ret < 0) - md * (ret >= (long long) md);
}

ull power(ull a, ull b, ull md) {
  ull ans = 1;
  while (b > 0) {
    if (b & 1) {
      ans = mult(ans, a, md);
    }
    a = mult(a, a, md);
    b >>= 1;
  }
  return ans;
}

bool is_prime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) {
    return (n | 1) == 3;
  }
  ull s = __builtin_ctzll(n - 1);
  ull d = n >> s;
  const ull A[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  for (ull a : A) {
    ull p = power(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) {
      p = mult(p, p, n);
    }
    if (p != n - 1 && i != s) {
      return false;
    }
  }
  return true;
}

ull pollard(ull n) {
  auto f = [n](ull x) {
    return mult(x, x, n) + 1;
  };
  ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) {
      x = ++i;
      y = f(x);
    }
    if ((q = mult(prd, max(x,y) - min(x,y), n))) {
      prd = q;
    }
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}

vector<ull> factor(ull n) {
  if (n == 1) {
    return vector<ull>();
  }
  if (is_prime(n)) {
    return {n};
  }
  ull x = pollard(n);
  vector<ull> l = factor(x);
  vector<ull> r = factor(n / x);
  l.insert(l.end(), r.begin() ,r.end());
  return l;
}
