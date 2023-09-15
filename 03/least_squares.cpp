#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include <string>
using namespace std;

struct Point
{
    double x, y;
    Point() = default;
    Point(double xx, double yy): x{xx}, y{yy}{};
};

istream& operator >> (istream& is, Point& p)
{
    is >> p.x >> p.y;
    return is;
}

ostream& operator << (ostream& os, const Point& p)
{
    os << p.x << " " << p.y;
    return os;
}

auto read(const string &filename)
{
    ifstream ifs{filename};
    if (!ifs)
        throw runtime_error{"Can't open file \"" + filename + "\""};
    return vector<Point>{istream_iterator<Point>{ifs}, istream_iterator<Point>{}};
}

struct Coeff
{
    double value;
    double delta;
    Coeff(double v, double d): value{v}, delta{d} {};
};

auto least_squares(const vector<Point>& points)
{
    size_t N {points.size()};
    double x_avg {0.0};
    double y_avg {0.0};
    double xy_avg {0.0};
    double sqr_x_avg {0.0};

    for (const auto& p:points)
    {
        x_avg += p.x;
        y_avg += p.y;
        xy_avg += p.x * p.y;
        sqr_x_avg += p.x * p.x;
    }

    x_avg /= N;
    y_avg /= N;
    xy_avg /= N;
    sqr_x_avg /= N;

    double b {(xy_avg - x_avg * y_avg) / (sqr_x_avg - x_avg*x_avg)};
    if(!isfinite(b))
        throw overflow_error{"Division by zero"};

    double a {x_avg - b*y_avg};

    return make_tuple(Coeff{a, 0.0}, Coeff{b, 0.0});
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "usage: " << argv[0] << " </path/to/data>" << endl;
        return 2;
    }

    try {
        string datafile {argv[1]};
        auto [a, b] = least_squares(read(datafile));
        cout << datafile << " " << a.value << " "
             << b.value << " " << b.delta << endl;
    }
    catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
