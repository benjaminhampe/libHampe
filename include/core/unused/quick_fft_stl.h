//#include <complex>
//#include <vector>
//
//using namespace std;
//
//// Must provide type or MSVC++ barfs with "ambiguous call to overloaded function"
//double pi = 4 * atan(1.0);
//
//void fft(int sign, vector<complex<double>> &zs) {
//    unsigned int j=0;
//    // Warning about signed vs unsigned comparison
//    for(unsigned int i=0; i<zs.size()-1; ++i) {
//        if (i < j) {
//            auto t = zs.at(i);
//            zs.at(i) = zs.at(j);
//            zs.at(j) = t;
//        }
//        int m=zs.size()/2;
//        j^=m;
//        while ((j & m) == 0) { m/=2; j^=m; }
//    }
//    for(unsigned int j=1; j<zs.size(); j*=2)
//        for(unsigned int m=0; m<j; ++m) {
//            auto t = pi * sign * m / j;
//            auto w = complex<double>(cos(t), sin(t));
//            for(unsigned int i = m; i<zs.size(); i+=2*j) {
//                complex<double> zi = zs.at(i), t = w * zs.at(i + j);
//                zs.at(i) = zi + t;
//                zs.at(i + j) = zi - t;
//            }
//        }
//}
