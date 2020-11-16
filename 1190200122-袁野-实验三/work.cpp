# include <bits/stdc++.h>
# define MAXN 30
# define inf 1000000000
using namespace std; 

int n,m;
 
struct edge{
 	int to,val;
 	edge(){to = val = 0;}
 	edge(int _to,int _val){to = _to,val = _val;}
};

struct Heap
{
	int size;
	pair <int,int> queue[MAXN];
	Heap()         //��ʼ�� 
	{
		size=0;
	}
	void shift_up(int i)
	{
		while(i>1)
		{
			if(queue[i]<queue[i>>1]) swap(queue[i],queue[i>>1]);
	        i>>=1;
	    }
	}
	
	void shift_down(int i)   //�³� 
	{
		while ((i<<1)<=size)
		{
			int next=i<<1;
			if (next<size && queue[next+1]<queue[next]) next++;
			if (queue[i]>queue[next])
			{
				swap(queue[i],queue[next]);
				i=next;
			}
			else return;
		}
	}
    void push(pair <int,int> x)   //����Ԫ�� 
    {
        queue[++size]=x;
        shift_up(size);
    }
    
	void pop()         //�������� 
    {
        swap(queue[1],queue[size]);
        size--;
        shift_down(1);
    }
    
	pair <int,int> top(){return queue[1];}
    bool empty(){return !size;} 
     
}q;
 
vector <edge> List[MAXN];

void Input(){
	freopen("dir.txt","r",stdin);
	scanf("%d%d",&n,&m);
 	int x,y,z;
 	for (int i=1; i<=m; ++i)
 	{
 		scanf("%d%d%d",&x,&y,&z);
 		List[x].push_back(edge(y,z));
	}
	printf("���ݶ�ȡ��ϣ�\n");
	freopen("CON","r",stdin);
}

namespace DIJ{
	int dis[MAXN],pre[MAXN],s;
	
	void print(int x){
		if (x == -1) return;
		print(pre[x]);
		printf("%d-->",x);
	}
	
	void Dijkstra(int s){
		for (int i=1; i<=n; ++i) dis[i] = inf,pre[i] = 0;
		pre[s] = -1;
		dis[s] = 0;
		q.push(make_pair(dis[s],s));
		while (!q.empty())
		{
			int now=q.top().second,nowdis=q.top().first;
			q.pop();
			if (dis[now] != nowdis) continue;
			for (auto x:List[now])
			{
				if (dis[x.to] <= dis[now]+x.val) continue;
				dis[x.to] = dis[now]+x.val;
				pre[x.to] = now;
				q.push(make_pair(dis[x.to],x.to));
			}
		}
		
	}
	
	void doit(int x){
		if (dis[x] == inf)
		{
			printf("Դ��%d����%d���ɴ�\n",s,x);
			return;
		}
		printf("Դ��%d����%d����̾���Ϊ��",s,x);
		printf("%d\n",dis[x]);
		printf("Դ��%d����%d�����·��Ϊ��",s,x);
		print(pre[x]);
		printf("%d\n",x);
		printf("---------------������----------------\n\n");
	} 
	
	bool qury(){
		int x;
		printf("������Ҫ��ѯ�ĵ�ı�ţ�����������-1,ȫ�����������0\n");
		scanf("%d",&x);
		if (x == -1) return 0;
		if (x == 0)
		{
			for (int i=1; i<=n; ++i) doit(i);
			return 1;
		}
		if (x > n||x < 1)
		{
			printf("�������ݳ�����Χ�����������룺\n\n");
			return 1;
		}
		doit(x);
		return 1;
	}
	
	Main(){
		printf("������Դ�㣺\n");
		scanf("%d",&s);
		while (s<1||s>n)
		{
			printf("����Դ�㳬����Χ�����������룺\n");
			scanf("%d",&s);
		}
		Dijkstra(s);
		while ( qury() );
	}
}

namespace Floyed{
	int dis[MAXN][MAXN];
	Make_Matrix(){
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=n; ++j)
			{
				if (i == j) dis[i][j] = 0;
				else dis[i][j] = 1e9;
			}
			
		for (int i=1; i<=n; ++i)
			for (auto x:List[i])
				dis[i][x.to] = min(x.val,dis[i][x.to]);
		
		for (int k=1; k<=n; ++k)
			for (int i=1; i<=n; ++i)
				for (int j=1; j<=n; ++j)
					dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	
	void qury(int s,int t){
		printf("��%d����%d����̾����ǣ�%d\n",s,t,dis[s][t]);
		printf("��%d����%d�����·���ǣ�\n",s,t);
		int now = s;
		while (now != t){
			printf("%d->",now);
			for (int i=1; i<=n; ++i)
			{
				if (i == now) continue;
				if (dis[now][i]+dis[i][t] == dis[now][t])
				{
					now = i;
					break;
				}
			}
		}
		printf("%d",now);
		printf("---------------������----------------\n\n");
		
	}
	
	void Main(){
		Make_Matrix();
		int s,t;
		while (1)
		{
			printf("������Ҫ��ѯ·������㣬����-1�˳���\n");
			scanf("%d",&s);
			if (s == -1) break;
			while (s<1 || s>n) scanf("%d",&s);
			printf("������Ҫ��ѯ·�����յ㣺\n");
			scanf("%d",&t);
			while (t<1 || t>n) scanf("%d",&t);
			qury(s,t);
			
		}
	} 
	
}

int main()
{
 	Input();
// 	DIJ::Main();
	Floyed::Main();
    return 0;
}

