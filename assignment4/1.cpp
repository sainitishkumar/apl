#include <iostream>
#include <cmath>

using namespace std;

// helper functions

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a%b);   
}

class Complex {
    protected:
        double real, imag;
    public:
        Complex(double r, double i);
        void setVal(double r, double i);

        pair<double, double> getVal();

        void print();
        void printR();
        
        Complex operator+(Complex c);
        Complex operator-(Complex c);
        Complex operator*(Complex c);
};

Complex::Complex(double r, double i) {
    real = r;
    imag = i;
}

void Complex::setVal(double r, double i) {
    real = r;
    imag = i;
}

pair<double, double> Complex::getVal() {
    return {real, imag};
}

void Complex::print() {
    printf("%.3f %.3f\n", real, imag);
}

void Complex::printR() {
    printf("%.3f\n", real);
}

Complex Complex::operator+(Complex c) {
    auto c1_val = this->getVal();
    auto c2_val = c.getVal();
    Complex res(c1_val.first+c2_val.first, c1_val.second+c2_val.second);

    return res;
}

Complex Complex::operator-(Complex c) {
    auto c1_val = this->getVal();
    auto c2_val = c.getVal();
    Complex res(c1_val.first-c2_val.first, c1_val.second-c2_val.second);

    return res;
}

Complex Complex::operator*(Complex c) {
    auto c1_val = this->getVal();
    auto c2_val = c.getVal();
    double r = (c1_val.first*c2_val.first)  - (c1_val.second*c2_val.second);
    double i = (c1_val.first*c2_val.second) + (c1_val.second*c2_val.first);
    Complex res(r, i);

    return res;
}

class Rational : public Complex {
    protected:
        long long int p, q;
    public:
        Rational(long long int n, long long int d);
        void reduce();
};

Rational::Rational(long long int n, long long int d): Complex((double)n/(double)d, 0) {
    p = n;
    q = d;
}

void Rational::reduce() {
    // find out the gcd for p and q, divide them by it
    long long int GCD = gcd(p, q);
    long long int n = p/GCD;
    long long int d = q/GCD;
    if(d < 0) {
        d*=-1;
        n*=-1;
    }
    printf("%lld %lld\n", n, d);
}

class Natural : public Rational {
    public:
        Natural(int a);
        bool isPrime();
        int inverse();
};

Natural::Natural(int a): Rational(a, 1) {}

bool Natural::isPrime() {
    if(this->p == 2) return true;
    if(this->p < 2) return false;
    if(this->p % 2 == 0) return false;
    for(int i=3; i <= sqrt(this->p); i+=2) {
        if(this->p % i == 0) return false;
    }
    return true;
}

int Natural::inverse() {
    int prime = 1000000007;
	int y = 0, x = 1;
    long long int a = this->p;
	while (a > 1) {
		int q = a/ prime;
		int t = prime;
        prime = a % prime;
        a = t;
		t = y;
		y = x - q * y;
		x = t;
	}
	if (x < 0) x += 1000000007;
    printf("%d\n", x);
    return x;
}

int main(int argc, char const *argv[])
{
    int n;
    cin>> n;
    string s;
    while(n--) {
        cin>> s;
        if(s[0] == 'c') {
            cin>> s;
            int last = s.length() - 1;
            double r, i;
            if(s[last] == 'd') {
                cin>> r>> i;
                Complex c1(r, i);
                cin>> r>> i;
                Complex c2(r, i);
                auto res = c1 + c2;
                res.print();
            } else if(s[last] == 'b') {
                cin>> r>> i;
                Complex c1(r, i);
                cin>> r>> i;
                Complex c2(r, i);
                auto res = c1 - c2;
                res.print();
            } else if(s[last] == 't') {
                cin>> r>> i;
                Complex c1(r, i);
                cin>> r>> i;
                Complex c2(r, i);
                auto res = c1 * c2;
                res.print();
            }
        } else if(s[0] == 'r') {
            cin>> s;
            int last = s.length() - 1;
            int r, i;
            if(s[last] == 'd') {
                cin>> r>> i;
                Rational c1(r, i);
                cin>> r>> i;
                Rational c2(r, i);
                auto res = c1 + c2;
                res.printR();
            } else if(s[last] == 'b') {
                cin>> r>> i;
                Rational c1(r, i);
                cin>> r>> i;
                Rational c2(r, i);
                auto res = c1 - c2;
                res.printR();
            } else if(s[last] == 't') {
                cin>> r>> i;
                Rational c1(r, i);
                cin>> r>> i;
                Rational c2(r, i);
                auto res = c1 * c2;
                res.printR();
            } else if(s[last] == 'e') {
                cin>> r>> i;
                Rational ra(r, i);
                ra.reduce();
            }
        } else if(s[0] == 'n') {
            cin>> s;
            int last = s.length() - 1;
            int r, i;
            if(s[last-1] == 'm') {
                cin>> r;
                Natural c1(r);
                (c1.isPrime()) ? cout<< 1<< endl: cout<< 0<< endl;
            } else if(s[last-1] == 's') {
                cin>> r;
                Natural c1(r);
                c1.inverse();
            }
        }
    }
    return 0;
}