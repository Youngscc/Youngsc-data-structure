# include <bits/stdc++.h>

using namespace std;

struct node{
	char c;
	int weight;
	node* LeftChild;
	node* RightChild;
	node(){LeftChild = RightChild = NULL;}
	node(char _c,int _weight){c = _c,weight = _weight,LeftChild = RightChild = NULL;}
	node(int _weight,node *_Left,node* _Right){weight = _weight,LeftChild =_Left; RightChild = _Right;}
	bool operator < (const node& p) const {
		return weight > p.weight;
	} 
};

map <char,int> t;
map <char,string> s;
priority_queue <node> q;
string TXT;

void read(){
	getline(cin,TXT);
	int len = TXT.length();
	for (int i=0; i<len; ++i) t[TXT[i]]++;
}

node* MakeHuffman(){
	map<char,int>::iterator iter;
	printf("各字母出现频率为：\n");
	for (iter=t.begin(); iter != t.end(); iter++) q.push(*new node(iter->first,iter->second)),printf("%c: %d\n",iter->first,iter->second);
	while (!q.empty())
	{
		if (q.size() == 1)
		{
			node* ret = new node;
			*ret = q.top();
			return ret;
		}
		node* x = new node; *x = q.top(); q.pop();
		node* y = new node; *y = q.top(); q.pop();
		q.push(*new node(x->weight+y->weight,x,y));
	}
}

void dfs(node* now,string S){
	if (now->LeftChild == NULL)
	{
		s[now->c] = S;
		return;
	 } 
	dfs(now->LeftChild,S+"0");
	dfs(now->RightChild,S+"1");
}

int main(){
	freopen("text.in","r",stdin);
	read();
	node* root = MakeHuffman();
	dfs(root,"");
	map<char,string>::iterator iter;
	printf("各字母哈夫曼编码为：\n");
	for (iter=s.begin(); iter != s.end(); iter++) cout << iter->first << ": " << iter->second << endl;
	int len = TXT.length(),sum=0;
//	int fd_stdout = dup(fileno(stdout));
	freopen("text.out","w",stdout);
	for (int i=0; i<len; ++i) {
		cout << s[TXT[i]];
		sum += s[TXT[i]].length();
	}
	fclose(stdout);
	freopen("CON","w",stdout);
	printf("文件压缩完成！\n该文件的压缩率为: %.8lf%\n",sum*1.0/len/8*100);
	return 0;
}
