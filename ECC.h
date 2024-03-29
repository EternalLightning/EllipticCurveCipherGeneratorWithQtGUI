//secp256k1: y² ≡ x³ + 7 (MOD 10000000000037) Ep(0, 7)
#include <cmath>
#include "HighPrecision.h"

const int MOD=998244353;

//struct expandNum{
//	int a, b;
//
//	expandNum operator*(expandNum m){
//		int c=a*a-
//	}
//}

int quickPow(int a, int b){
	int ret=1;

	while(b){
		if(b&1) ret=ret*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}

	return ret;
}

int quickMul(int a, int b){
	int ret=0;

	while(b){
		if(b&1) ret=(ret+a)%MOD;
		a<<=1;
		a%=MOD;
		b>>=1;
	}

	return ret;
}

int gcd(int a, int b){
	return b?gcd(b, a%b):a;
}

int legendre(int a){
	return quickPow(a%MOD, (MOD-1)/2);
}

struct Point{
	int x, y;

	Point(int a, int b):x(a), y(b){};

	bool operator==(Point m) const{
		return x==m.x&&y==m.y;
	}
	Point operator+(Point m){
		if(this->x==0&&this->y==0) return m;
		else if(m.x==0&&m.y==0) return *this;

		int retx, rety;
		bool flag=false; //true is negative number
		int molecule, denominator, _gcd, lambda, invElem;

		if(*this==m)
			molecule=3*x*x, denominator=y<<1;
		else
			molecule=y-m.y, denominator=x-m.x;

		if(molecule*denominator<0)
			flag=true;

		molecule=abs(molecule), denominator=abs(denominator);
		_gcd=gcd(molecule, denominator);
		molecule/=_gcd, denominator/=_gcd;
		invElem=quickPow(denominator, MOD-2);
		if(flag)
			molecule=-molecule;
		lambda=(quickMul(molecule, invElem)%MOD+MOD)%MOD;
		retx=((quickMul(lambda, lambda)-x-m.x)%MOD+MOD)%MOD;
		rety=((lambda*(x-retx)-y)%MOD+MOD)%MOD;

		return {retx, rety};
	}
	Point operator-(Point m){
		Point tmp(m.x, -m.y);
		return *this+tmp;
	}
	Point operator*(int n){
		Point ret(0, 0), tmp=*this;

		n%=MOD;
		while(n){
			if(n&1) ret=ret+tmp;
			tmp=tmp+tmp;
			n>>=1;
		}

		return ret;
	}
};

const Point PUBLICKEY();