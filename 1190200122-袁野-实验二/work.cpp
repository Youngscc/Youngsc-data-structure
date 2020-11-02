# include <bits/stdc++.h>
# define MAXN 10

using namespace std;

int K;
map <char,int> t;
map <char,string> s;
string TXT,Hufcode;

void read(){
	getline(cin,TXT);
	int len = TXT.length();
	for (int i=0; i<len; ++i) t[TXT[i]]++;
}

namespace KthHuffman{
	struct Knode{
		char c;
		int weight;
		Knode* Child[MAXN];
		clear(){for (int i=0; i<K; ++i) Child[i]=NULL;}
		Knode(){clear(); c = 0; weight = 0;}
		Knode(char _c,int _weight){c = _c,weight = _weight,clear();}
		Knode(int _weight){weight = _weight; clear(); c = 0;}
		bool operator < (const Knode& p) const {
			return weight > p.weight;
		} 
	} *root;
	
	priority_queue <Knode> q;
	
	Knode* MakeHuffman(){
		map<char,int>::iterator iter;
		printf("����ĸ����Ƶ��Ϊ��\n");
		for (iter=t.begin(); iter != t.end(); iter++) q.push(*new Knode(iter->first,iter->second)),printf("%c: %d\n",iter->first,iter->second);
		int sum = (q.size()-1)%(K-1)+1;
		if (sum > 1)
		{
			Knode* now = new Knode;
			for (int i=0; i<sum; ++i)
			{
				Knode* x = new Knode; *x = q.top(); q.pop();
				now->Child[i] = x;
				now->weight += x->weight;
			}
			q.push(*now);
		}
		while (1)
		{
			if (q.size() == 1)
			{
				Knode* ret = new Knode;
				*ret = q.top();
				return ret;
			}
			Knode* now = new Knode;
			for (int i=0; i<K; ++i)
			{
				Knode* x = new Knode; *x = q.top(); q.pop();
				now->Child[i] = x;
				now->weight += x->weight;
			}
			q.push(*now);
		}
	}
	
	void dfs(Knode* now,string S){
		if (now->c)
		{
			s[now->c] = S;
			return;
		 } 
		for (int i=0; now->Child[i]!=NULL; ++i) dfs(now->Child[i],S+(char)(i+'0'));
	}
	
	bool cmp(){
		freopen("textans.out","w",stdout);
		int Hufflen = Hufcode.length(),TXTlen = TXT.length();
		int t=0,i;
		for (i=0; i<TXTlen; ++i)
		{
			Knode *now = root;
			do
			{
				now = now->Child[Hufcode[t]-'0'];
				t++;
			} while (now->c == 0);
			if (now->c != TXT[i])
			{
				fclose(stdout);
				freopen("CON","w",stdout);
				return 0;
			}
			printf("%c",now->c);
		}
		fclose(stdout);
		freopen("CON","w",stdout);
		return i == TXTlen;
	}
	
	Main(){
		root = MakeHuffman();
		dfs(root,"");
		map<char,string>::iterator iter;
		printf("����ĸ����������Ϊ��\n");
		for (iter=s.begin(); iter != s.end(); iter++) cout << iter->first << ": " << iter->second << endl;
		int len = TXT.length(),sum=0;
		freopen("text.out","w",stdout);
		for (int i=0; i<len; ++i) {
			cout << s[TXT[i]];
			sum += s[TXT[i]].length();
			Hufcode += s[TXT[i]];
		}
		fclose(stdout);
		freopen("CON","w",stdout);
		printf("�ļ�ѹ����ɣ�\n���ļ���ѹ����Ϊ: %.8lf%\n",((int)log2(K-1)+1)*sum*1.0/len/8*100);
		if (cmp()) printf("���Ƚϣ���ѹ��ȷ\n");
		else printf("���Ƚϣ���ѹ����\n"); 
	}
}

namespace Huffman{
	struct node{
		char c;
		int weight;
		node* LeftChild;
		node* RightChild;
		node(){LeftChild = RightChild = NULL; c = 0;}
		node(char _c,int _weight){c = _c,weight = _weight,LeftChild = RightChild = NULL;}
		node(int _weight,node *_Left,node* _Right){weight = _weight,LeftChild =_Left; RightChild = _Right; c = 0;}
		bool operator < (const node& p) const {
			return weight > p.weight;
		} 
	} *root;
	
	priority_queue <node> q;
	
	node* MakeHuffman(){
		map<char,int>::iterator iter;
		printf("����ĸ����Ƶ��Ϊ��\n");
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
	
	bool cmp(){
		freopen("textans.out","w",stdout);
		int Hufflen = Hufcode.length(),TXTlen = TXT.length();
		int t=0,i;
		for (i=0; i<TXTlen; ++i)
		{
			node *now = root;
			do
			{
				if (Hufcode[t] == '1') now = now->RightChild;
				else now = now->LeftChild;
				t++;
			} while (now->c == 0);
			if (now->c != TXT[i])
			{
				fclose(stdout);
				freopen("CON","w",stdout);
				return 0;
			}
			printf("%c",now->c);
		}
		fclose(stdout);
		freopen("CON","w",stdout);
		return i == TXTlen;
	}
	
	Main(){
		root = MakeHuffman();
		dfs(root,"");
		map<char,string>::iterator iter;
		printf("����ĸ����������Ϊ��\n");
		for (iter=s.begin(); iter != s.end(); iter++) cout << iter->first << ": " << iter->second << endl;
		int len = TXT.length(),sum=0;
		freopen("text.out","w",stdout);
		for (int i=0; i<len; ++i) {
			cout << s[TXT[i]];
			sum += s[TXT[i]].length();
			Hufcode += s[TXT[i]];
		}
		fclose(stdout);
		freopen("CON","w",stdout);
		printf("�ļ�ѹ����ɣ�\n���ļ���ѹ����Ϊ: %.8lf%\n",sum*1.0/len/8*100);
		if (cmp()) printf("���Ƚϣ���ѹ��ȷ\n");
		else printf("���Ƚϣ���ѹ����\n"); 
	}
}

using namespace Huffman;
using namespace KthHuffman;

int main(){
	printf("���������������ƣ�");
	scanf("%d",&K);
	freopen("text.in","r",stdin);
	read();
	fclose(stdin);
	if (K==2) Huffman::Main();
	else if (K>2) KthHuffman::Main();
	else printf("��������"); 
	return 0; 
}
