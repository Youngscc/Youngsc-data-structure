# include <bits/stdc++.h>
# define LL long long
# define MAXM 100
# define MAXN 30

using namespace std;

int n,m,v[MAXN];
queue <int> q;
struct edge{int x,y;}ed[MAXM];

struct Matrix{
	
	int matrix[MAXN][MAXN];
	
	Matrix(){
		memset(matrix,0,sizeof(matrix));
	}
	
	void clear(){
		memset(matrix,0,sizeof(matrix));
	}
	
	void Show(){
		printf("  �ڽӾ���Ϊ��\n    ");
		for (int i=1; i<=n; ++i) printf("%3d",i);
		printf("\n   -----------------------------------\n");
		for (int i=1; i<=n; ++i,printf("\n"))
		{
			printf("%2d |",i);
			for (int j=1; j<=n; ++j) printf("%3d",matrix[i][j]);
		}
		printf("\n ------------ ������� ---------------\n\n");
	}
	
	void Make(){
		for (int i=1; i<=m; ++i) 
			matrix[ed[i].x][ed[i].y] = matrix[ed[i].y][ed[i].x] = 1;
		Show();
	}
	
	void dfs(int x){
		for (int i=1; i<=n; ++i)
		{
			if (!matrix[x][i] || v[i]) continue;
			v[i] = x;
			dfs(i);
		}
	}
	
	void Dfs_rec(){
		memset(v,0,sizeof(v));
		for (int i=1; i<=n; ++i)
		{
			if (!v[i])
			{
				v[i] = -1;
				dfs(i);
				v[i] = 0;
			}
		}
		printf("�ڻ����ڽӾ���ĵݹ��������У�����ĸ��׽ڵ�ֱ�Ϊ��"); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// �����ڵ�Ϊ0��õ�Ϊ������dfs���еĸ��ڵ� 
		printf("\n ------------ ������� ---------------\n\n");
	}
	
	void Dfs_Norec(){
		memset(v,0,sizeof(v));
		int mem[MAXN],st[MAXN],top=0;
		for (int i=1; i<=n; ++i) mem[i] = 1; 
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			v[i] = -1;
			st[++top] = i;
			while (top)
			{
				int x = st[top];
				for (int j=mem[x]; j<=n; ++j,mem[x]=j) // ����һ��ö�ٵ��Ľڵ㿪ʼö�٣��Ż��㷨Ч��
				{
					if (v[j] || !matrix[x][j]) continue;
					st[++top] = j;
					v[j] = x;
					break;
				}
				if (mem[x] == n+1) top--;
			}
			v[i] = 0;
 		} 
 		printf("�ڻ����ڽӾ���ķǵݹ��������У�����ĸ��׽ڵ�ֱ�Ϊ��"); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// �����ڵ�Ϊ0��õ�Ϊ������dfs���еĸ��ڵ� 
		printf("\n ------------ ������� ---------------\n\n");
	}
	
	void BFS(int s){
		q.push(s);
		v[s] = 1;
		while (!q.empty())
		{
			int x=q.front();
			printf("%d ",x);
			q.pop();
			for (int i=1; i<=n; ++i)
			{
				if (v[i] || !matrix[x][i]) continue;
				v[i] = 1;
				q.push(i);
			}
		}
	}
	
	void bfs(){
		memset(v,0,sizeof(v));
		printf("�����ڽӾ���Ĺ�������㷨�У���������Ϊ��");
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			BFS(i);
		}
		printf("\n ------------ ������� ---------------\n\n");
	} 
}mat;

struct List{
	
	vector <int> list[MAXN];
	
	void clear(){
		for (int i=1; i<=n; ++i) list[i].clear();
	}
	
	void Show(){
		printf("  �ڽӱ�Ϊ��\n");
		for (int i=1; i<=n; ++i,printf("\n"))
		{
			printf("%2d: ",i);
			for (auto x:list[i])
				printf("%4d",x);
		}
		printf("\n ------------ ������� ---------------\n\n");
	}
	
	
	void Make(){
		for (int i=1; i<=n; ++i) list[i].clear();
		for (int i=1; i<=m; ++i)
		{
			list[ed[i].x].push_back(ed[i].y);
			if (ed[i].x != ed[i].y)	list[ed[i].y].push_back(ed[i].x);
		}
		Show();
	}
	
	void dfs(int x){
		for (auto t:list[x])
		{
			if (v[t]) continue;
			v[t] = x;
			dfs(t);
		}
	}
	
	void Dfs_rec(){
		memset(v,0,sizeof(v));
		for (int i=1; i<=n; ++i)
		{
			if (!v[i])
			{
				v[i] = -1;
				dfs(i);
				v[i] = 0;
			}
		}
		printf("�ڻ����ڽӱ���������У�����ĸ��׽ڵ�ֱ�Ϊ��"); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// �����ڵ�Ϊ0��õ�Ϊ������dfs���еĸ��ڵ�
		printf("\n ------------ ������� ---------------\n\n");
	}
	
	void Dfs_Norec(){
		memset(v,0,sizeof(v));
		int st[MAXN],top=0,mem[MAXN]={0};
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			v[i] = -1;
			st[++top] = i;
			while (top)
			{
				int x = st[top];
				for (int j=mem[x]; j<list[x].size(); ++j,mem[x]=j) // ����һ��ö�ٵ��Ľڵ㿪ʼö�٣��Ż��㷨Ч�� 
				{
					if (v[list[x][j]]) continue;
					st[++top] = list[x][j];
					v[list[x][j]] = x;
					break;
				}
				if (mem[x] == list[x].size()) top--;
			}
			v[i] = 0;
 		} 
 		printf("�ڻ����ڽӱ�ķǵݹ��������У�����ĸ��׽ڵ�ֱ�Ϊ��"); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// �����ڵ�Ϊ0��õ�Ϊ������dfs���еĸ��ڵ� 
		printf("\n ------------ ������� ---------------\n\n");
	}
	
	void BFS(int s){
		q.push(s);
		v[s] = 1;
		while (!q.empty())
		{
			int x=q.front();
			printf("%d ",x);
			q.pop();
			for (auto i:list[x])
			{
				if (v[i]) continue;
				v[i] = 1;
				q.push(i);
			}
		}
		printf("\n ------------ ������� ---------------\n\n");
	}
	
	void bfs(){
		memset(v,0,sizeof(v));
		printf("�����ڽӱ�Ĺ�������㷨�У���������Ϊ��");
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			BFS(i);
		}
	} 
}lst;


void MatrixToList(Matrix& mat,List& lst){
	for (int i=1; i<=n; ++i) lst.list[i].clear();
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
			if (mat.matrix[i][j])
				lst.list[i].push_back(j);
	
	lst.Show();
}

void ListToMatrix(List &lst,Matrix &mat){
	mat.clear();
	for (int i=1; i<=n; ++i)
		for (auto x:lst.list[i])
			mat.matrix[i][x] = 1;
	mat.Show();
}

int main(){
	freopen("undir.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; ++i) scanf("%d%d",&ed[i].x,&ed[i].y);
	printf("�ļ���ȡ�������!\n");
	freopen("CON","r",stdin);
	while (1)
	{
		int opt,op;
		printf("\n\n��ѡ�񴢴淽ʽ�� 1���ڽӾ���    2���ڽӱ�\n");
		scanf("%d",&opt);
		if (opt == 1) mat.Make();
		else if (opt == 2) lst.Make();
		else
		{
			printf("��������������������룡\n");
			continue;
		}
		while (1)
		{
			printf("\n\n                         ��ѡ�������  \n            1���ݹ����Ѳ�����������ĸ��ڵ㸸�ڵ�\n            2���ǵݹ����Ѳ�����������ĸ��ڵ㸸�ڵ�\n");
			printf("            3�����Ѳ��������\n            4�������һ�ִ��淽ʽ\n            5�����ĵ�ǰ���淽ʽ\n\n"); 
			scanf("%d",&op);
			if (opt == 1)
			{
				if (op == 1) mat.Dfs_rec();
				else if (op == 2) mat.Dfs_Norec();
				else if (op == 3) mat.bfs();
				else if (op == 4) MatrixToList(mat,lst);
				else if (op == 5) break;
				else printf("��������������������룡\n");
			} 
			
			if (opt == 2)
			{
				if (op == 1) lst.Dfs_rec();
				else if (op == 2) lst.Dfs_Norec();
				else if (op == 3) lst.bfs();
				else if (op == 4) ListToMatrix(lst,mat);
				else if (op == 5) break;
				else printf("��������������������룡\n");
			} 
		}
	}
}
