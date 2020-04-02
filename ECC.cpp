#include<bits/stdc++.h>
using namespace std;

template<typename T> T gcd(T a, T b){ if(a==0) return b; return gcd(b%a, a); }

int getModuloMultiplicativeInverse(int a, int modulo){
	int m0 = modulo;
	int y = 0, x = 1;

	if(modulo == 1) return 0;
	while(a > 1){
		int q = a/modulo;
		int t = modulo;

		modulo = a%modulo; a = t;
		t = y;

		y = x - q*y;
		x = t;
	}

	if(x < 0) x += m0;
	return x;
}

struct Point{
	int x;
	int y;

	friend void operator >> (istream &in, Point &p);
	bool operator == (Point &q){
		return (this->x == q.x and this->y == q.y);
	}
};

struct EllipticCurve{
	Point pt;
	int mod;

	int delta(Point p, Point q){
		int res;
		if(p == q){
			cout<<"Points are same"<<endl;
			int numerator = 3 * (p.x) * (p.x) + this->pt.x;
			int denominator = 2*p.y;
			if(denominator < 0) numerator *= (-1);
			denominator = abs(denominator);
			int g = gcd(abs(numerator), abs(denominator));
			numerator /= g; denominator /= g;

			int moduloMultiplicativeInverse = getModuloMultiplicativeInverse(denominator, this->mod);
			res = (numerator * moduloMultiplicativeInverse)%this->mod;
		}
		else{
			int numerator = q.y - p.y;
			int denominator = q.x - p.x;
			if(denominator < 0) numerator *= (-1);
			denominator = abs(denominator);
			int g = gcd(abs(numerator), abs(denominator));
			numerator /= g; denominator /= g;

			int moduloMultiplicativeInverse = getModuloMultiplicativeInverse(denominator, this->mod);
			res = (numerator * moduloMultiplicativeInverse)%this->mod;
		}

		return res;
	}

	Point addPoint(Point p, Point q){
		int delta = this->delta(p, q);
		cout<<"delta: "<<delta<<endl;
		Point r;
		r.x = (delta*delta - p.x - q.x)%this->mod;
		r.y = (delta*(p.x - r.x) - p.y)%this->mod;

		if(r.x < 0) r.x += this->mod;
		if(r.y < 0) r.y += this->mod;

		return r;
	}
};

EllipticCurve ecc;

void operator >> (istream &in, Point &p){
	in>>p.x>>p.y;
}

int main(){
	ecc = {{1, 1}, 23};
	Point p, q;
	cout<<"Enter point p(x, y): ";
	cin>>p;
	cout<<"Enter point q(x, y): ";
	cin>>q;

	Point r = ecc.addPoint(p, q);
	cout<<"A = B+C: \n(x, y): ";
	cout<<r.x<<", "<<r.y<<endl;

	Point r2 = ecc.addPoint(r, r);
	cout<<"2A(x, y): "<<r2.x<<", "<<r2.y<<endl;
}
