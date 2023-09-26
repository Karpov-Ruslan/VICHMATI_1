#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <functional>

typedef long double LD;
constexpr auto max_precision{std::numeric_limits<LD>::digits10 + 1};
const LD X = 0.5l;

// This i very bad code

LD func1(const LD x) {
    return std::sin(x*x);
}

LD pfunc1(const LD x) {
    return 2.0L*x*std::cos(x*x);
}

LD func2(const LD x) {
    return std::cos(std::sin(x));
}

LD pfunc2(const LD x) {
    return -std::sin(std::sin(x))*std::cos(x);
}

LD func3(const LD x) {
    return std::exp(std::sin(std::cos(x)));
}

LD pfunc3(const LD x) {
    return -std::exp(std::sin(std::cos(x)))*std::cos(std::cos(x))*std::sin(x);
}

LD func4(const LD x) {
    return std::log(x + 3.0L);
}

LD pfunc4(const LD x) {
    return 1.0L/(x + 3.0L);
}

LD func5(const LD x) {
    return std::sqrt(x + 3.0L);
}

LD pfunc5(const LD x) {
    return 1.0L/(2.0L*std::sqrt(x + 3.0L));
}

LD analit_proizv1(const std::function<LD(LD)>& func, const LD h) {
    return (func(X + h) - func(X))/h;
}

LD analit_proizv2(const std::function<LD(LD)>& func, const LD h) {
    return (func(X) - func(X - h))/h;
}

LD analit_proizv3(const std::function<LD(LD)>& func, const LD h) {
    return (func(X + h) - func(X - h))/(2.0L*h);
}

LD analit_proizv4(const std::function<LD(LD)>& func, const LD h) {
    return (4.0L*(func(X + h) - func(X - h)))/(3.0L*2.0L*h) -
            (func(X + 2.0L*h) - func(X - 2.0L*h))/(3.0L*4.0L*h);
}

LD analit_proizv5(const std::function<LD(LD)>& func, const LD h) {
    return (3.0L*(func(X + h) - func(X - h)))/(2.0L*2.0L*h) -
           3.0L*(func(X + 2.0L*h) - func(X - 2.0L*h))/(5.0L*4.0L*h) +
           (func(X + 3.0L*h) - func(X - 3.0L*h))/(10.0L*6.0L*h);
}

void pechat(const std::string& str, const std::function<LD(LD)>& func, const std::function<LD(LD)>& pfunc) {
    std::ofstream fin;
    fin.open(str);
    fin << std::setprecision(max_precision);
    {
        LD h = 1.0L;
        fin << "number;delta_analit_proizv1;delta_analit_proizv2;delta_analit_proizv3;delta_analit_proizv4;delta_analit_proizv5;\n";
        for (int i = 0; i <= 20; i++) {
            fin << h << ";"
            << std::abs(pfunc(X) - analit_proizv1(func, h)) << ";"
            << std::abs(pfunc(X) - analit_proizv2(func, h)) << ";"
            << std::abs(pfunc(X) - analit_proizv3(func, h)) << ";"
            << std::abs(pfunc(X) - analit_proizv4(func, h)) << ";"
            << std::abs(pfunc(X) - analit_proizv5(func, h)) << ";"
            << "\n";
            h = h / 2.0L;
        }
    }
    fin.close();
}

int main() {
    std::ofstream fin;
    pechat("data1.csv", func1, pfunc1);
    pechat("data2.csv", func2, pfunc2);
    pechat("data3.csv", func3, pfunc3);
    pechat("data4.csv", func4, pfunc4);
    pechat("data5.csv", func5, pfunc5);
    std::cout << "Done" << std::endl;
}
