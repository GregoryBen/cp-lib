mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
  return uniform_int_distribution<int>(a, b)(rng);
}

double rand(double a, double b) {
  return uniform_real_distribution<double>(a, b)(rng);
}
