#include <iostream>
#include<complex>
#include<cmath>
using namespace std;
using Complex = complex<double>;

Complex getTwiddle(int k , int N){
    double angle = 2.0*M_PI * k/N;
    return Complex(cos(angle), sin(angle));
}
int main() {
    Complex w0 = getTwiddle(0, 8);
    Complex w4 = getTwiddle(4, 8);

    cout<< w0 <<endl; 
    cout<< w4 <<endl; 
    return 0;
}