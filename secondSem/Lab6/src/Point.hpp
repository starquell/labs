
#ifndef LAB6_POINT_HPP
#define LAB6_POINT_HPP

#include <random>
#include <tuple>

struct Point {

    double x;
    double y;
    double z;

    Point () {

        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution <double> rand (0, 1000);

        x = rand (gen);
        y = rand (gen);
        z = rand (gen);
    };

    Point (double _x, double _y, double _z)
            : x (_x),
              y (_y),
              z (_z)
    {}

    bool operator< (const Point &other) const {

        return std::tie (x, y, z) < std::tie (other.x, other.y, other.z);
    }

    bool operator> (const Point &other) const {

        return std::tie (x, y, z) > std::tie (other.x, other.y, other.z);
    }

    bool operator== (const Point &other) const {

        return std::tie (x, y, z) == std::tie (other.x, other.y, other.z);
    }

    bool operator != (const Point &other) const {

        return std::tie (x, y, z) != std::tie (other.x, other.y, other.z);
    }


};

template <class Stream>
Stream& operator<< (Stream& stream, const Point &point) {

    stream << '{' << point.x << ", " << point.y << ", " << point.z << "}\n";

    return stream;
}



#endif //LAB6_POINT_HPP
