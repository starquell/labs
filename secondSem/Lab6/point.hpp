
#ifndef LAB6_POINT_HPP
#define LAB6_POINT_HPP

#include <tuple>

struct Point {

    double x;
    double y;
    double z;

    bool operator< (const Point &other) {

        return std::tie (x, y, z) < std::tie (other.x, other.y, other.z);
    }

    bool operator> (const Point &other) {

        return std::tie (x, y, z) > std::tie (other.x, other.y, other.z);
    }

    bool operator== (const Point &other) {

        return std::tie (x, y, z) == std::tie (other.x, other.y, other.z);
    }


};

template <class Stream>
Stream& operator<< (Stream& stream, const Point &point) {

    stream << '{' << point.x << ", " << point.y << ", " << point.z << "}\n";

    return stream;
}



#endif //LAB6_POINT_HPP
