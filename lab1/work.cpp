# include <bits/stdc++.h>

using namespace std;

int gcd(int x,int y){return y? gcd(y,x%y):x;} // ͨ��շת���������Ӻͷ�ĸ�����Լ���Ӷ�ʵ��Լ��ͨ��

struct fraction{ // �����Ľṹ�� 
	int numerator,denominator,flag; // �ֱ�Ϊ���ӡ���ĸ�������š�
	fraction(){numerator = 0, denominator = 1; flag=0;} // ���캯����ʼ��
	fraction(int _nume,int _deno){numerator = abs(_nume),denominator = _deno,flag = numerator ? _nume/numerator : 0;}
	
	fraction simplify() // Լ�ֺ���
	{
		if (!numerator) denominator = 1;
		else
		{
			int p = gcd(numerator,denominator); // ��÷��ӷ�ĸ�����Լ�� 
			numerator /= p;
			denominator /= p;
		}
		return *this;
	}
	
	fraction operator + (const fraction& a) const{ // �������������ļӷ� 
		int p = gcd(denominator,a.denominator); // ������������ķ�ĸ�����Լ������ʵ��ͨ�� 
		fraction ret = fraction(numerator*(a.denominator/p)*flag+a.numerator*(denominator/p)*a.flag,denominator*a.denominator/p);
		return ret.simplify();
	}
	
	fraction operator - (const fraction& a) const{// �������������ļ��� 
		int p = gcd(denominator,a.denominator);
		fraction ret = fraction(numerator*(a.denominator/p)*flag-a.numerator*(denominator/p)*a.flag,denominator*a.denominator/p);
		return ret.simplify();
	}
	
	fraction operator * (const fraction& a) const{//�������������ĳ˷� 
		fraction ret = fraction(numerator*a.numerator*flag*a.flag,denominator*a.denominator);
		return ret.simplify();
	}
	
	fraction operator / (const fraction& a) const{//�������������ĳ��� 
		fraction ret = fraction(numerator*a.denominator*flag*a.flag,denominator*a.numerator);
		return ret.simplify();
	}
	
	double operator * (const double& a) const { // ����һ��������һ��˫���ȸ������ĳ˷� 
		return 1.0*numerator*a/denominator*flag;
	}
};

struct ele{ // �������ʽ��ÿһ��Ľṹ�� 
	fraction coefficient; // ������ʽ��ϵ�� 
	int power; // ���� 
	ele *nxt; // �������ڶ���ʽ�е���һ�� 
	ele(){};
	ele(int _numer,int _denom,int _power){coefficient = fraction(_numer,_denom),power = _power; nxt = NULL;}
	ele(fraction _ceof,int _power){coefficient = _ceof,power = _power; nxt = NULL;}
	// ���ֲ�ͬ�����Ĺ��캯�� 
};   

struct polynomial{ // �������ʽ�Ľṹ�� 
	ele *base;// �ö���ʽ����ߴ��� 
	polynomial(){base = new ele(0,1,0);} // ���캯����ʼ�� 
	
	void change(ele to) // ��ǰ����ʽ����to��һ�� 
	{
		if (!to.coefficient.numerator) return; // �ӵ���Ϊ0�򷵻� 
		ele *now = this -> base,*pre = NULL;
		while (now != NULL && now->power > to.power) pre = now,now = now->nxt;
		if (now == NULL || now -> power < to.power) // ��ԭ����������toͬ���ݵ��� 
		{
			ele *it = new ele; // �½��� 
			*it = to;
			if (pre != NULL) pre -> nxt = it;
			else base = it;
			it -> nxt = now;
			it -> coefficient.simplify();
		}
		
		else // ��ԭ���ʹ��ڸô��ݵ��� 
		{
			now -> coefficient = now -> coefficient + to.coefficient;
			if (!now -> coefficient.numerator && now -> power) 
			{
				if (pre == NULL) this -> base  = now -> nxt;
				else pre -> nxt = now -> nxt;
				delete(now);
			}
		}
	}
	
	polynomial operator + (const polynomial& a) const // ���ض���ʽ�ӷ� 
	{
		polynomial ret;
		ele *nowa = base,*nowb = a.base,*now = new ele;
		while (nowa != NULL && nowb != NULL) // ���ս��ηֱ���� 
		{
			if (nowa->power > nowb->power) *now = *nowa,nowa = nowa->nxt;
			else if (nowa->power < nowb->power) *now = *nowb,nowb = nowb->nxt;
			else *now = ele(nowa->coefficient+nowb->coefficient,nowa->power),nowa = nowa->nxt,nowb = nowb->nxt;
			ret.change(*now);
		}
		delete(now);
		while (nowa != NULL) ret.change(*nowa),nowa = nowa->nxt;
		while (nowb != NULL) ret.change(*nowb),nowb = nowb->nxt;
		return ret;
	}
	
	polynomial operator - (const polynomial& a) const //���ض���ʽ�ļ��� 
	{
		polynomial ret;
		ele *nowa = base,*nowb = a.base,*now = new ele;
		while (nowa != NULL && nowb != NULL)
		{
			if (nowa->power > nowb->power) ret.change(*nowa),nowa = nowa->nxt;
			else if (nowa->power < nowb->power)
			{
				*now = *nowb;
				now -> coefficient.flag *= -1;
				ret.change(*now);
				nowb = nowb->nxt;
			}
			else
			{
				*now = ele(nowa->coefficient-nowb->coefficient,nowa->power),nowa = nowa->nxt,nowb = nowb->nxt;
				ret.change(*now);
			}
		}
		
		while (nowa != NULL) ret.change(*nowa),nowa = nowa->nxt;
		while (nowb != NULL) 
		{
			*now = *nowb;
			now->coefficient.flag *= -1;
			ret.change(*now);
			nowb = nowb->nxt;
		}
		delete now;
		return ret;
	}
	
	polynomial operator * (const polynomial& a) const // ���ض���ʽ�ĳ˷� 
	{
		polynomial ret;
		ele *nowa = base,*nowb,*now = new ele;
		while (nowa != NULL)
		{
			nowb = a.base;
			while (nowb != NULL) ret.change(ele(nowa->coefficient*nowb->coefficient,nowa->power+nowb->power)),nowb = nowb->nxt;
			// ʹ��������ʽ�е������������˺������ 
			nowa = nowa->nxt;
		}
		return ret;
	}
	
	pair <polynomial,polynomial> operator / (const polynomial& a) const // ʹ�ö�Ԫ�����ʽ���ض���ʽ�������Ӷ�����ͬʱ�����̶���ʽ����������ʽ 
	{
		polynomial ret,res=*this,*b = new polynomial;
		while (res.base -> power >= a.base -> power)
		{
			ele *now;
			*b = a;
			polynomial ex;
			ex.change(ele(res.base->coefficient/b->base->coefficient,res.base->power-b->base->power));
			*b = *b*ex;
			res = res-(*b);
			ret.change(*(ex.base));
		}
		// ���ն���ʽ�����ķ�������� 
		return make_pair(ret,res);
	}
	
	polynomial derivative(int k){ //��k�ε����� 
		polynomial ret;
		ele *now = this -> base;
		while (now != NULL && now->power >= k)
		{
			fraction x=now->coefficient;
			for (int i=now->power; i>=now->power-k+1; -  -i) x = x*fraction(i,1);
			ret.change(ele(x,now->power-k));
			now = now->nxt;
		}// ���ն���ʽ�󵼷����� 
		return ret;
	}
	
	void print(){ // ��ӡ����ʽ 
		ele *now = base;
		if (now -> power == 0) //  
		{
			if (now->coefficient.denominator != 1) printf("%d/%d",now->coefficient.numerator*now->coefficient.flag,now->coefficient.denominator);
			else printf("%d",now->coefficient.numerator*now->coefficient.flag); // ʶ����������� 
			printf("\n");
			return;
		}
		bool flag = 0;
		while (now != NULL)
		{              
			if (now->coefficient.numerator == 0 && flag) break;
			if (!flag) // �ж��ǲ���Ҫ����ĵ�һ�� 
			{
				flag = 1;
				if (now -> coefficient.flag < 0) printf("-"); // ��һ��Ϊ�����ܣ�Ϊ��������� 
			}
			else
			{
				if (now -> coefficient.flag > 0) printf("+ "); // ����һ���⣬��������ȷ������ķ���Ϊ�Ӻż��š� 
				else printf("- ");
			}

			if (now->coefficient.denominator != 1) printf("%d/%d",abs(now->coefficient.numerator),now->coefficient.denominator); // ϵ���Ƿ����������ʽ 
			else if (!now->power) printf("%d",abs(now->coefficient.numerator)); // 
			else if (now->coefficient.numerator != 1) printf("%d",abs(now->coefficient.numerator));	 // ϵ��Ϊ�����������ʽ�� 
			
			if (now->power > 1) printf("x^%d ",now->power); // ��ǰ���������1�������ʽ 
			else if (now->power == 1) printf("x ",now->power); // ��ǰ���������1ʱֻ���x 
			else printf(" "); //�����������ʽ 
			now = now -> nxt;
		}
		printf("\n");
	}
	
	void scan(){ // �������ʽ 
		int n,x,y,z;
		scanf("%d",&n);
		for (int i=1; i<=n; ++i) scanf("%d%d%d",&x,&y,&z),change(ele(x,y,z)); 
	}
	
	double calc(double x){ // ����x��ͬȡֵ�µĺ���ֵ 
		double ret = 0;
		ele *now = this->base;
		while (now != NULL)
		{
			double sum = 1;
			for (int i=1; i<=now->power; ++i) sum *= x;
			ret += now->coefficient*sum;
			now = now->nxt;
		}
		return ret;
	}
};

int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	polynomial x,y;
	printf("����ʽAΪ��"); 
	x.scan(); x.print();
	printf("����ʽBΪ��");
	y.scan(); y.print();
	printf("\nA+BΪ��");
	(x+y).print();
	printf("\nA-BΪ��");
	(x-y).print();
	printf("\nA*BΪ��");
	(x*y).print();
	pair <polynomial,polynomial> now = x/y;
	printf("\nA/B���̶���ʽΪ��");
	now.first.print();
	printf("A/B����������ʽΪ��");
	now.second.print();
	printf("��֤�����");
	(now.first*y+now.second).print();
	
	printf("\n");
	for (int i=0; i<=5; ++i)
	{
		printf("A����ʽ��%d�׵���Ϊ��",i);
		x.derivative(i).print();
	}
	printf("\n");
	
	printf("��ԭ�������Ա���ȡֵΪ1ʱ������ʽAȡֵΪ%.3lf\n",x.calc(1));
	printf("��ԭ�������Ա���ȡֵΪ2ʱ������ʽAȡֵΪ%.3lf\n",x.calc(2));
	printf("��ԭ�������Ա���ȡֵΪ3ʱ������ʽAȡֵΪ%.3lf\n",x.calc(3));
}

