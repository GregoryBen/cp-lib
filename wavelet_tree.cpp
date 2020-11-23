// preprocessing O(log n log(max(A)), query(log(max(A)), max(A) maximum element in array

template <typename T>
struct wavelet_node {
	int n;
	T lo, hi;
	wavelet_node *l = nullptr;
	wavelet_node *r = nullptr;
	vector<int> b;

	template <typename IT, class C>
	wavelet_node(IT begin, IT end, T _lo, T _hi, const C& comp) : n(end - begin), lo(_lo), hi(_hi) {
		if(n == 0 || lo == hi) {
      return;
    }
		T mid = lo + (hi - lo) / 2;
		auto f = [&](T x) {
		  return comp(x, mid);
    };
		b.reserve(n + 1);
		b.push_back(0);
		for (auto it = begin; it != end; it++) {
      b.push_back(b.back() + f(*it));
		}
		auto pivot = stable_partition(begin, end, f);
		l = new wavelet_node(begin, pivot, lo, mid, comp);
		r = new wavelet_node(pivot, end, mid + 1, hi, comp);
	}
};

template <typename T, class C = function<T(const T&, const T&>>
struct wavelet_tree {
	int n;
	wavelet_node<T> *root;
	C comp;

	template <typename IT>
	wavelet_tree(IT begin, IT end, const C& c) : n(end - begin), comp(c) {
	  T min = *min_element(begin, end, comp);
	  T max = *max_element(begin, end, comp);
		root = new node<T>(begin, end, min, max, comp);
	}

	int count(node<T> *u, int ql, int qr, T x) {
		if (ql >= qr || !comp(u->lo, x)) return 0;
		if (!comp(x, u->hi)) return qr - ql;
		int lcnt = u->b[ql], rcnt = u->b[qr];
		return count(u->l, lcnt, rcnt, x) + count(u->r, ql - lcnt, qr - rcnt, x);
	}

	T k_th(node<T> *u, int ql, int qr, int k) {
		assert(0 <= k && k < u->n);
		if (u->lo + 1 == u->hi) return u->lo;
		int lcnt = u->b[ql], rcnt = u->b[qr];
		if (k < rcnt - lcnt) return k_th(u->l, lcnt, rcnt, k);
		else return k_th(u->r, ql - lcnt, qr - rcnt, k - (rcnt - lcnt));
	}

	void print() {
		deque<wavelet_node<T>*> q{root};
		while (!q.empty()) {
			auto u = q.front();
			q.pop_front();
			cout << "range = [" << u->lo << ", " << u->hi << "), frequency: ";
			for (auto x : u->b) {
				cout << x << " ";
			}
			cout << "\n";
			if (u->l) q.push_back(u->l);
			if (u->r) q.push_back(u->r);
		}
	}
};
