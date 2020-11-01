# include <bits/stdc++.h>
# define DataType int

using namespace std;

struct node{
	DataType data;
	node *LeftChild,*RightChild;
	node(){data = 0; LeftChild = RightChild = NULL;}
	node(DataType dat){data = dat;  LeftChild = RightChild = NULL;} 
};

stack <node*> st;

void RecPreorder (node *now){
	printf("%d ",now->data);
	if (now->LeftChild != NULL) RecPreorder(now->LeftChild);
	if (now->RightChild != NULL) RecPreorder(now->RightChild);
}

void RecMidorder (node *now){
	if (now->LeftChild != NULL) RecMidorder(now->LeftChild);
	printf("%d ",now->data);
	if (now->RightChild != NULL) RecMidorder(now->RightChild);
}

void RecPostorder (node *now){
	if (now->LeftChild != NULL) RecPostorder(now->LeftChild);
	if (now->RightChild != NULL) RecPostorder(now->RightChild);
	printf("%d ",now->data);
}

void NoRecPreorder (node* now){
	if (now == NULL) return;
	while (now != NULL || !st.empty())
	{
		while (now != NULL)
		{
			printf("%d ",now->data);
			st.push(now);
			now = now->LeftChild;
		}
		
		if (!st.empty())
		{
			now = st.top();
			st.pop();
			now = now->RightChild;
		}
	}
}

void NoRecMidorder (node *now){
	if (now == NULL) return;
	while (now != NULL || !st.empty())
	{
		while (now != NULL)
		{
			st.push(now);
			now = now->LeftChild;
		}
		
		if (!st.empty())
		{
			now = st.top();
			st.pop();
			printf("%d ",now->data);
			now = now->RightChild;
		}
	}
}

void NoRecPostorder (node *now){
	if (now == NULL) return;
	node *last=NULL;
	while (now != NULL || !st.empty())
	{
		while (now != NULL)
		{
			st.push(now);
			now = now->LeftChild;
		}
		
		if (!st.empty())
		{
			now = st.top();
			if (now->RightChild == NULL || now->RightChild == last)
			{
				printf("%d ",now->data);
				last = now;
				now = NULL;
				st.pop();			
			}
			else now = now->RightChild;
		}
	}
}

int main(){
	node *root = new node(1);
	root->LeftChild = new node(2);
	root->RightChild = new node(3);
	root->LeftChild->LeftChild = new node(4);
	root->LeftChild->RightChild = new node(5);
	root->RightChild->RightChild = new node(7);
	RecPreorder(root);
	printf("\n");
	NoRecPreorder(root);
	printf("\n");
	RecMidorder(root);
	printf("\n"); 
	NoRecMidorder(root);
	printf("\n");
	RecPostorder(root);
	printf("\n");
	NoRecPostorder(root);
}
