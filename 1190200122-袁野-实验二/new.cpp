# include <bits/stdc++.h>
using namespace std;
char s[100];
int main(){
	freopen("textt.in","r",stdin);
	freopen("text.in","w",stdout);
	bool flag = 0;
	while (~scanf("%s",s))
	{
		if (flag) printf(" ");
		else flag = 1;
		printf("%s",s);
	}
}
