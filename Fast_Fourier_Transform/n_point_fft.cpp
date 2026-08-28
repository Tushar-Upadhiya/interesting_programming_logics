#include <iostream>
#include<complex>
#include<cmath>
#include<vector>
using namespace std;
using Complex = complex<double>;

void bitReverse(vector<Complex>&a){
int n = a.size();
for(int i =1,j=0;i<n;++i){
    int bit = n>>1;
    for(;j&bit;bit>>1){
        j^=bit;
    }
    j^=bit;
    if(i<j){
        swap(a[i],a[j]);
    }
}
}

void fft(vector<Complex>&a){
    int n = a.size();
    bitReverse(a);
    for(int len = 2; len<=n;len<<=1){
        double angle = -2.0* M_PI/len;
        Complex wlen(cos(angle),sin(angle));

        for(int i = 0 ; i< len;i+=len){
            Complex w(1.0,0.0);
            int half = len/2;

            for (int j = 0;j< half;++j){
                Complex u = a[i+j];
                Complex v = a[i+j+half]*w;

                a[i+j] = u+v;
                a[i+j+half] = u-v;
                
                w*=wlen;

            }
        }
    }
}




int main() {
    vector<Complex> signal = {1.0, 2.0, 3.0, 4.0};

    fft(signal);

    for (int i = 0; i < signal.size(); ++i) {
        cout << "X[" << i << "] = " << signal[i] << endl;
    }

    return 0;
}