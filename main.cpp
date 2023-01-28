#include <iostream>
#include <string>
#include <vector>
#include <map>
 
#include <stack>
 
using namespace std;
 
struct Node{
    string str;
    Node* left;
    Node* right;
    Node(string str_) {
        str = str_;
        left = nullptr;
        right = nullptr;
    }
};
 
bool isbracket(char c) {
    return c == '(' || c == ')';
}
 
bool isoper(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
 
bool prio_less(char oper1, char oper2) {
    if (isbracket(oper1)) {
        return true;
    }
    if ((oper2 == '*' || oper2 == '/') && (oper1 == '+' || oper1 == '-'))
        return true;
    if (oper2 == '/' && oper1 == '*')
        return true;
    return false;
}
 
vector <string> infix_to_postfix(vector <string> v) {
    stack<string> st;
    vector <string> ans;
    for (auto &s : v) {
        if (s.back() == '(') {
            st.push(s);
            continue;
        }
        if (s.back() == ')') {
            while (!st.empty() && st.top().back() != '(') {
                ans.push_back(st.top());
                st.pop();
            }
            st.pop();
            continue;
        }
        if (isdigit(s.back())) {
            ans.push_back(s);
            continue;
        }
        while (!st.empty() && !prio_less(st.top().back(), s.back())) {
            ans.push_back(st.top());
            st.pop();
        }
        st.push(s);
    }
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}
 
int it = 0;
 
Node* build_tree_prefix(Node* cur, vector <string> &v) {
    if (it == v.size()) {
        return cur;
    }
    if (isdigit(v[it].back())) {
        cur = new Node(v[it++]);
        return cur;
    }
    else {
        cur = new Node(v[it++]);
        cur->left = build_tree_prefix(cur->left, v);
        cur->right = build_tree_prefix(cur->right, v);
        return cur;
    }
}
 
 
Node* build_tree_postfix(Node* cur, vector <string> &v) {
    if (it == -1) {
        return cur;
    }
    if (isdigit(v[it].back())) {
        cur = new Node(v[it--]);
        return cur;
    }
    else {
        cur = new Node(v[it--]);
        cur->right = build_tree_postfix(cur->right, v);
        cur->left = build_tree_postfix(cur->left, v);
        return cur;
    }
}
 
void print_prefix(Node* cur) {
    if (!cur) {
        return;
    }
    cout << cur->str << ' ';
    print_prefix(cur->left);
    print_prefix(cur->right);
}
 
void print_postfix(Node* cur) {
    if (!cur) {
        return;
    }
    print_postfix(cur->left);
    print_postfix(cur->right);
    cout << cur->str << ' ';
}
 
 
void print_infix(Node* cur) {
    if (!cur) {
        return;
    }
    if (isdigit(cur->str.back())) {
        cout << cur->str;
        return;
    }
    cout << "( ";
    print_infix(cur->left);
    cout << ' ' << cur->str << ' ';
    print_infix(cur->right);
    cout << " )";
}
 
int main() {
    string type = "infix";
    cin >> type;
    string text = "(1 + 2) * (3 + 4)";
    getline(cin, text);
    getline(cin, text);
    text += ' ';
    vector <string> v;
    if (type == "prefix" || type == "postfix") {
        int pos = -1; // last space
        for (int i = 0; i < text.size(); i++) {
            if (isspace(text[i])) {
                v.push_back(text.substr(pos + 1, i - pos - 1));
                pos = i;
            }
        }
    }
    else {
        int pos = -1; // start of digit
        for (int i = 0; i < text.size(); i++) {
            if (isdigit(text[i])) {
                if (pos == -1) {
                    pos = i;
                }
                continue;
            }
            if (pos != -1) {
                v.push_back(text.substr(pos, i - pos));
            }
            pos = -1;
            if (isoper(text[i]) || isbracket(text[i])) {
                string tmp = "";
                tmp += text[i];
                v.push_back(tmp);
            }
        }
    }
    Node* root = nullptr;
    if (type == "infix") {
        vector <string> postfix = infix_to_postfix(v);
 
        it = postfix.size() - 1;
 
        root = build_tree_postfix(root, postfix);
        cout << "prefix : ";
        print_prefix(root);
        cout << endl;
        cout << "postfix : ";
        print_postfix(root);
        cout << endl;
    }
    
    if (type == "prefix") {
        it = 0;
        root = build_tree_prefix(root, v);
 
        cout << "infix : ";
        print_infix(root);
        cout << endl;
        cout << "postfix : ";
        print_postfix(root);
        cout << endl;
    }
 
    if (type == "postfix") {
        it = v.size() - 1;
        root = build_tree_postfix(root, v);
        cout << "prefix : ";
        print_prefix(root);
        cout << endl;
        cout << "infix : ";
        print_infix(root);
        cout << endl;
    }
 
}
