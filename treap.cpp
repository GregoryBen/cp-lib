// simple treap
// need rng

struct tnode {
	int pri;
	int val;
	int sz;
	long long sum;
	bool flip = false;
	tnode* c[2];

	tnode (int _v) {
		pri = rng();
		sum = val = _v;
		sz = 1;
		c[0] = c[1] = nullptr;
	}

	~tnode() {
	  delete c[0];
	  delete c[1];
	}
};

int get_size(tnode* x) {
  return (x ? x->sz : 0);
}

long long get_sum(tnode* x) {
  return (x ? x->sum : 0);
}

tnode* propagate(tnode* x) {
	if (!x || !x->flip) {
    return x;
	}
	swap(x->c[0], x->c[1]);
	x->flip = 0;
	for (int i = 0; i < 2; i++) {
    if (x->c[i]) {
      x->c[i]->flip ^= 1;
    }
	}
	return x;
}

tnode* calc(tnode* x) {
	tnode* a = x->c[0];
	tnode* b = x->c[1];
	assert(!x->flip);
	propagate(a);
	propagate(b);
	x->sz = 1 + get_size(a) + get_size(b);
	x->sum = x->val + get_sum(a) + get_sum(b);
	return x;
}

void tour(tnode* x, vector<int> &v) {
	if (!x) {
    return;
	}
	propagate(x);
	tour(x->c[0], v);
	v.emplace_back(x->val);
	tour(x->c[1], v);
}

pair<tnode*, tnode*> split(tnode* t, int v) {
	if (!t) {
    return {t, t};
	}
	propagate(t);
	if (t->val >= v) {
		auto p = split(t->c[0], v);
		t->c[0] = p.second;
		return {p.first, calc(t)};
	} else {
		auto p = split(t->c[1], v);
		t->c[1] = p.first;
		return {calc(t), p.second};
	}
}

pair<tnode*, tnode*> split_size(tnode* t, int sz) {
	if (!t) {
    return {t, t};
	}
	propagate(t);
	if (get_size(t->c[0]) >= sz) {
		auto p = split_size(t->c[0], sz);
		t->c[0] = p.second;
		return {p.first, calc(t)};
	} else {
		auto p = split_size(t->c[1], sz - get_size(t->c[0]) - 1);
		t->c[1] = p.first;
		return {calc(t), p.second};
	}
}

tnode* merge(tnode* l, tnode* r) {
	if (!l) {
    return l;
	}
	if (!r) {
    return l;
	}
	propagate(l);
	propagate(r);
	tnode* t;
	if (l->pri > r->pri) {
    l->c[1] = merge(l->c[1], r);
    t = l;
	} else {
    r->c[0] = merge(l, r->c[0]);
    t = r;
	}
	return calc(t);
}

tnode* insert(tnode* x, int v) {
	auto a = split(x, v);
	auto b = split(a.second, v + 1);
	return merge(a.first, merge(new tnode(v), b.second));
}

tnode* remove(tnode* x, int v) { // delete v
	auto a = split(x, v);
	auto b = split(a.second, v + 1);
	return merge(a.first, b.second);
}
