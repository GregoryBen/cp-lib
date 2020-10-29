namespace fast_IO {

static const int BUF_SIZE = 1 << 20;
static int write_pos = 0;
static char write_buf[BUF_SIZE];

inline char get_char() {
  static char buf[BUF_SIZE];
  static int len = 0, pos = 0;
  if (pos == len) {
    pos = 0, len = fread(buf, 1, BUF_SIZE, stdin);
  }
  if (pos == len) {
    return -1;
  }
  return buf[pos++];
}

inline char scan_char() {
  char c = get_char();
  while (c <= 32)
    c = get_char();
  return c;
}

inline string scan_str() {
  string str;
  char c = scan_char();
  while (c <= ' ') {
    c = get_char();
  }
  while (c > ' ') {
    str.push_back(c);
    c = get_char();
  }
  return str;
}

template <typename T = int>
inline T scan() {
  int s = 1;
  char c = scan_char();
  T x = 0;
  if (c == '-') {
    s = -1, c = get_char();
  }
  while ('0' <= c && c <= '9') {
    x = x * 10 + c - '0';
    c = get_char();
  }
  return s == 1 ? x : -x;
}

inline void write_char(char x) {
  if (write_pos == BUF_SIZE) {
    fwrite(write_buf, 1, BUF_SIZE, stdout);
    write_pos = 0;
  }
  write_buf[write_pos++] = x;
}

inline void write_str(string str, char end = 0) {
  for (char c : str) {
    write_char(c);
  }
  if (end) {
    write_char(end);
  }
}

template <typename T>
inline void write(T x, char end = 0) {
  if (x < 0) {
    write_char('-'), x = -x;
  }
  int n = 0;
  char s[24];
  while (x || !n) {
    s[n++] = '0' + x % 10;
    x /= 10;
  }
  while (n--) {
    write_char(s[n]);
  }
  if (end) {
    write_char(end);
  }
}

struct Flusher {
  ~Flusher() {
    if (write_pos) {
      fwrite(write_buf, 1, write_pos, stdout);
      write_pos = 0;
    }
  }
} flusher;

} // namespace fast_IO

using namespace fast_IO;
