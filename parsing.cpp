int num_eval;
stack<int> values;
stack<char> ops;

void process_op() {
    int r = values.top();
    values.pop();
    int l = values.top();
    values.pop();
    char op = ops.top();
    ops.pop();
    switch (op) {
        case '+':
            values.push(l + r);
            break;
        case '-':
            values.push(l - r);
            break;
        case '*':
            values.push(l * r);
            break;
        case '/':
            values.push(l / r);
            break;
    }
}

int priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return 0;
}

int eval(string s) {
    num_eval++;
    s = '(' + s + ')';
    for (char c : s)
        if (c == ' ')
          continue;
        else if ('0' <= c && c <= '9')
            values.push(c - '0');
        else if (c == '(')
            ops.push(c);
        else if (c == ')') {
            while (ops.top() != '(')
                process_op();
            ops.pop();
        } else {
            while (!ops.empty() && priority(ops.top()) >= priority(c))
                process_op();
            ops.push(c);
        }
    int ans = values.top();
    values.pop();
    return ans;
}
