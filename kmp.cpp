// kmp 
// O(n)

template <typename T>
vector<int> prefix_function(const T &s){
	int n = (int) s.size(), j = 0;
	vector<int> p(n);
	for(int i = 1; i < n; i++) {
		while (j > 0 && s[i] != s[j]) {
      j = p[j - 1];
		}
		if(s[i] == s[j]) {
      j++;
		}
		p[i] = j;
	}
	return p;
}
