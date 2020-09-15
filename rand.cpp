int rand(int a, int b) {
  return uniform_int_distribution<int>(a, b)(rng);
}

double rand(double a, double b) {
  return uniform_real_distribution<double>(a, b)(rng);
}
