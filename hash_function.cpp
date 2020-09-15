struct my_hash {
  const uint64_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    return (size_t) splitmix64(x + RANDOM);
  }

  size_t operator()(pair<uint64_t, uint64_t> x) const {
    return (size_t) splitmix64(x.first + RANDOM) ^
      ((size_t) splitmix64(x.second + RANDOM) >> 1);
  }
};
