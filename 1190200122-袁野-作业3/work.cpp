# include <bits/stdc++.h>
# define DataType int

using namespace std;

struct node{
	DataType data;
	node *LeftChild,*RightChild;
	node(){data = 0; LeftChild = RightChild = NULL;}
	node(DataType dat){data = dat;  LeftChild = RightChild = NULL;} 
};

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

int main(){
	node *root = new node(1);
	root->LeftChild = new node(2);
	root->RightChild = new node(3);
	root->LeftChild->LeftChild = new node(4);
	root->LeftChild->RightChild = new node(5);
	root->RightChild->RightChild = new node(7);
	RecPreorder(root);
	printf("\n");
	RecMidorder(root);
}
