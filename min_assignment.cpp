//
// Minimum assignment (simplified Jonker-Volgenant)
//
// Description:
//   We are given a cost table of size n times m with n <= m.
//   It finds a minimum cost assignment, i.e.,
//     min sum_{ij} c(i,j) x(i,j)
//     where sum_{i in [n]} x(i,j)  = 1,
//           sum_{j in [m]} x(i,j) <= 1.
//
// Algorithm:
//   Simplified version of Jonker-Volgenant algorithm,
//   which omits a heuristical initialization step.
//
// Complexity:
//   O(n^3).
//   Much faster than the Kuhn-Munkres/hungarian algorithm.
//
// Note:
//   v = potential
//   L, R = matching pair
//   It finds minimum cost maximal matching.
//   To find the minimum cost non-maximal matching,
//   we add n dummy vertices to the right side.
//
// Verified:
//   SPOJ 286: Selfish City
//
// References:
//   R. Jonker and A. Volgenant (1987):
//   A shortest augmenting path algorithm for dense and sparse linear assignment problems.
//   Computing, vol.38, no.4, pp.325-340.
//
//   A. Volgenant (1996):
//   Linear and Semi Assignment Problems: a core oriented approach.
//   Computers and Operations Research, vol.23, pp.917-932.
//

template <typename T>
vector<int> min_assignment(const vector<vector<T>> &c) {
  int n = c.size(), m = c[0].size();
  assert(n <= m);
  vector<int> L(n, -1);
  vector<int> R(m, -1);
  vector<int> index(m);
  vector<int> prev(m);
  vector<T> v(m);
  vector<T> dist(m);
  iota(index.begin(), index.end(), 0);
  auto residue = [&](int i, int j) {
    return c[i][j] - v[j];
  };
  for (int f = 0; f < n; f++) {
    for (int j = 0; j < m; j++) {
      dist[j] = residue(f, j);
      prev[j] = f;
    }
    int j, l;
    int s = 0, t = 0;
    T w;
    while (true) {
      if (s == t) {
        l = s;
        w = dist[index[t]];
        ++t;
        for (int k = t; k < m; k++) {
          j = index[k];
          T h = dist[j];
          if (h <= w) {
            if (h < w) {
              t = s;
              w = h;
            }
            index[k] = index[t];
            index[t] = j;
            ++t;
          }
        }
        for (int k = s; k < t; k++) {
          j = index[k];
          if (R[j] < 0) {
            goto augment;
          }
        }
      }
      int q = index[s], i = R[q];
      ++s;
      for (int k = t; k < m; k++) {
        j = index[k];
        T h = residue(i, j) - residue(i, q) + w;
        if (h < dist[j]) {
          dist[j] = h;
          prev[j] = i;
          if (h == w) {
            if (R[j] < 0) {
              goto augment;
            }
            index[k] = index[t];
            index[t] = j;
            ++t;
          }
        }
      }
    }
    augment:
      for (int k = 0; k < l; k++) {
        v[index[k]] += dist[index[k]] - w;
      }
      int i;
      do {
        R[j] = i = prev[j];
        swap(j, L[i]);
      } while (i != f);
  }
  return L;
}
