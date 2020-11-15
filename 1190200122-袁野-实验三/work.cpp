# include <bits/stdc++.h>
# define MAXN 30
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
	Heap()         //初始化 
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
	
	void shift_down(int i)   //下沉 
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
    void push(pair <int,int> x)   //加入元素 
    {
        queue[++size]=x;
        shift_up(size);
    }
    
	void pop()         //弹出操作 
    {
        swap(queue[1],queue[size]);
        size--;
        shift_down(1);
    }
    
	pair <int,int> top(){return queue[1];}
    bool empty(){return size;} 
     
};
 
 vector <edge> List[MAXN];
 
 int main()
 {
 	scanf("%d%d",&n,&m);
 	int x,y,z;
 	for (int i=1; i<=m; ++i)
 	{
 		scanf("%d%d%d",&x,&y,&z);
 		List[x].push_back(edge(y,z));
	}
	
    return 0;
 }

