#include <bits/stdc++.h>
using namespace std;

struct node {
    string data;            // Expression
    vector<node *> sub;     // children (sub-expression)
};


struct node *newNode(string s){
    struct node *node = new struct node();
    node->data = s;         // Set expression
    node->sub.clear();      // Empty vecter
    return node;
}

char op[] = {'+','*','^'};
struct node* divide(node* node){      
    int n = node->data.length(), i = 0, pv = 0; // pv = previous
    if(n==1){
        node->sub.push_back(node); // Points to itself
        return node;
    }
    while(i<3 && pv==0){
        char c = op[i]; // Target operator
        int j = 0, paren = 0;
        while(j<n){
            if(node->data[j]=='(')paren++;
            else if(node->data[j]==')')paren--;
            else if(paren==0 && (node->data[j]==c)){    // if current position is not covered by parentheses && The character is the target operator
                node->sub.push_back(divide(newNode(node->data.substr(pv,j-pv)))); // divide with current operator
                pv = j+1; // The begining of the next sub-expression
            }
            j++;
        }
        
        if(pv!=0)node->sub.push_back(divide(newNode(node->data.substr(pv,n-pv)))); // If current operator could divide
        i++;
    }
    
    if(pv==0)node->sub.push_back(divide(newNode(node->data.substr(1,n-2)))); // No operator could divide = All in one parenthesis
    return node;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    struct node *root = newNode(s); // Create a root with data of full expression
    root = divide(root);
    // cout << root->data;
    int n;
    cin >> n;
    while(n--){
        struct node *temp = root;
        int x;
        bool flag = 0; // For null cases
        stack<int> st;
        do {
            cin >> x;
            if(x==0)break;
            st.push(x);
            if(x>temp->sub.size() || flag)flag = 1; // turn to null
            else temp = temp->sub[x-1];
        } while(x!=0);
        int sz = st.size();
        while(!st.empty()){
            cout << "op(" << st.top() << (st.size()>1 ? "," : ",p");
            st.pop();
        }
        while(sz--)cout << ")";
        cout << "=" << (flag ? "null" : temp->data) << "\n";
    }
}

/*
a*b^c+d*e^f
3
1 1 0
1 2 0
1 2 2 0

(x+y)+z
5
1 0
1 1 0
1 1 1 0
1 1 2 0
3 0

(a)
3
1 0
1 1 0
1 1 1 0
*/
