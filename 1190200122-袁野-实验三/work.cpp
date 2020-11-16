# include <bits/stdc++.h>
# define MAXN 30
# define inf 1000000000
using namespace std; 
 
struct edge{
 	int to,val;
 	edge(){to = val = 0;}
 	edge(int _to,int _val){to = _to,val = _val;}
};

struct Graph{
	vector <edge> List[MAXN];
	int n,m;
	bool isRec;
	Graph(){n=m=isRec=0;}
}gra,rgra;

struct Heap{
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
 
void Input(){
	freopen("dir.txt","r",stdin);
	scanf("%d%d",&gra.n,&gra.m);
	rgra.n = gra.n;
	rgra.m = gra.m;
	rgra.isRec = 1;
 	int x,y,z;
 	for (int i=1; i<=gra.m; ++i)
 	{
 		scanf("%d%d%d",&x,&y,&z);
 		gra.List[x].push_back(edge(y,z));
 		rgra.List[y].push_back(edge(x,z));
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
	
	void Dijkstra(int s,Graph &G){
		for (int i=1; i<=G.n; ++i) dis[i] = inf,pre[i] = 0;
		pre[s] = -1;
		dis[s] = 0;
		q.push(make_pair(dis[s],s));
		while (!q.empty())
		{
			int now=q.top().second,nowdis=q.top().first;
			q.pop();
			if (dis[now] != nowdis) continue;
			for (auto x:G.List[now])
			{
				if (dis[x.to] <= dis[now]+x.val) continue;
				dis[x.to] = dis[now]+x.val;
				pre[x.to] = now;
				q.push(make_pair(dis[x.to],x.to));
			}
		}
	}
	
	void doit(int x,Graph &G){
		if (dis[x] == inf)
		{
			if (!G.isRec) printf("Դ��%d����%d���ɴ�\n",s,x);
			else printf("��%d���յ�%d���ɴ�\n",x,s);
			return;
		}
		if (!G.isRec) printf("Դ��%d����%d����̾���Ϊ��",s,x);
		else printf("��%d���յ�%d����̾���Ϊ��",x,s);
		printf("%d\n",dis[x]);
		if (!G.isRec)
		{
			printf("Դ��%d����%d�����·��Ϊ��",s,x);
			print(pre[x]);
			printf("%d\n",x);
		}
		else
		{
			printf("��%d���յ�%d�����·��Ϊ��",x,s);
			int now = x;
			while (now != s)
			{
				printf("%d->",now);
				now = pre[now];
			}
			printf("%d\n",s);
		}
		
		printf("---------------������----------------\n\n");
	} 
	
	bool qury(Graph &G){
		int x;
		printf("������Ҫ��ѯ�ĵ�ı�ţ�����������-1,ȫ�����������0\n");
		scanf("%d",&x);
		if (x == -1) return 0;
		if (x == 0)
		{
			for (int i=1; i<=G.n; ++i) doit(i,G);
			return 1;
		}
		if (x > G.n||x < 1)
		{
			printf("�������ݳ�����Χ�����������룺\n\n");
			return 1;
		}
		doit(x,G);
		return 1;
	}
	
	Main(Graph &G){
		if (!G.isRec) printf("������Դ�㣺\n");
		else printf("�������յ㣺\n");
		scanf("%d",&s);
		while (s<1||s>G.n)
		{
			if (!G.isRec) printf("����Դ�㳬����Χ�����������룺\n");
			else printf("�����յ㳬����Χ�����������룺\n");
			scanf("%d",&s);
		}
		Dijkstra(s,G);
		while (qury(G));
	}
}

namespace Floyed{
	int dis[MAXN][MAXN];
	Make_Matrix(Graph &G){
		for (int i=1; i<=G.n; ++i)
			for (int j=1; j<=G.n; ++j)
			{
				if (i == j) dis[i][j] = 0;
				else dis[i][j] = inf;
			}
			
		for (int i=1; i<=G.n; ++i)
			for (auto x:G.List[i])
				dis[i][x.to] = min(x.val,dis[i][x.to]);
		
		for (int k=1; k<=G.n; ++k)
			for (int i=1; i<=G.n; ++i)
				for (int j=1; j<=G.n; ++j)
					dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	
	void qury(int s,int t,Graph &G){
		if (dis[s][t] == inf)
		{
			printf("��%d����%d�޷�����\n",s,t); 
			return;
		}
		printf("��%d����%d����̾����ǣ�%d\n",s,t,dis[s][t]);
		printf("��%d����%d�����·���ǣ�\n",s,t);
		int now = s;
		while (now != t){
			printf("%d->",now);
			for (int i=1; i<=G.n; ++i)
			{
				if (i == now) continue;
				if (dis[now][i]+dis[i][t] == dis[now][t])
				{
					now = i;
					break;
				}
			}
		}
		printf("%d\n",now);
	}
	
	void Main(Graph &G){
		Make_Matrix(G);
		int s,t;
		while (1)
		{
			printf("������Ҫ��ѯ·������㣬����-1�˳���\n");
			scanf("%d",&s);
			if (s == -1) break;
			while (s<1 || s>G.n)
			{
				printf("�������ݳ�����Χ�����������룺");
				scanf("%d",&s);
			}
			printf("������Ҫ��ѯ·�����յ㣺\n");
			scanf("%d",&t);
			while (t<1 || t>G.n)
			{
				printf("�������ݳ�����Χ�����������룺");
				scanf("%d",&t);
			}
			qury(s,t,G);
		}
	}
	
	void Main2(Graph &G){
		Make_Matrix(G);
		int s,t;
		while (1)
		{
			printf("���������еĵ�һ���㣬����-1�˳���\n");
			scanf("%d",&s);
			if (s == -1) break;
			while (s<1 || s>G.n)
			{
				printf("�������ݳ�����Χ�����������룺");
				scanf("%d",&s);
			}
			printf("���������е���һ�㣺\n");
			scanf("%d",&t);
			while (t<1 || t>G.n)
			{
				printf("�������ݳ�����Χ�����������룺");
				scanf("%d",&t);
			}
			qury(s,t,G);
			qury(t,s,G);
			printf("---------------������----------------\n\n");
		}
	}
	
	void Main3(Graph &G){
		memset(dis,0,sizeof(dis));
		for (int i=1; i<=G.n; ++i)
			for (auto x:G.List[i])
				dis[i][x.to] = 1;
		
		for (int i=1; i<=G.n; ++i) dis[i][i] = 1;
		
		for (int k=1; k<=G.n; ++k)
			for (int i=1; i<=G.n; ++i)
				for (int j=1; j<=G.n; ++j)
					dis[i][j] |= (dis[i][k]&dis[k][j]);
		
		printf("  �ɴ����Ϊ��\n    ");
		for (int i=1; i<=G.n; ++i) printf("%3d",i);
		printf("\n   -----------------------------------\n");
		for (int i=1; i<=G.n; ++i,printf("\n"))
		{
			printf("%2d |",i);
			for (int j=1; j<=G.n; ++j) printf("%3d",dis[i][j]);
		}
		printf("\n ------------ ������� ---------------\n\n");
	}
}

int main()
{
 	Input();
 	while (1)
 	{
 		int opt;
 		printf(" ------------------- ����ѡ�� --------------------\n");
 		printf("            1��������������·��\n");
 		printf("            2�����������������·��\n");
 		printf("            3��������յ�����·��\n");
 		printf("            4���������Ե����·��\n");
 		printf("            5����ɴ����\n");
 		scanf("%d",&opt);
		if (opt == 1) DIJ::Main(gra);
		else if (opt == 2) Floyed::Main(gra);
		else if (opt == 3) DIJ::Main(rgra);
		else if (opt == 4) Floyed::Main2(gra);
		else if (opt == 5) Floyed::Main3(gra); 
		else printf("������Ŵ������������룺");
	}	
    return 0;
}

