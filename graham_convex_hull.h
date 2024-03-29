#pragma once

#include <stack>
#include <cmath>
#include <vector>
#include <algorithm>


namespace convex_hull {

struct point
{
public:
    point()
        : x_coord(0)
        , y_coord(0)
    {}

    point(const double x, const double y)
        : x_coord(x)
        , y_coord(y)
    {}

    point(const std::initializer_list<double>& il)
        : x_coord(*il.begin())
        , y_coord(*(il.begin() + 1))
    {}

    double x() const
    {
        return x_coord;
    }
    double y() const
    {
        return y_coord;
    }

private:
    double x_coord;
    double y_coord;
};

point next_to_top(std::stack<point> &s)
{
    point temp = s.top();
    s.pop();
    point res = s.top();
    s.push(temp);
    return res;
}

void swap(point& p1, point& p2)
{
    point temp = p1;
    p1 = p2;
    p2 = temp;
}

double distance(const point& p1, const point& p2)
{
    return (p1.x() - p2.x())*(p1.x() - p2.x())
        + (p1.y() - p2.y())*(p1.y() - p2.y());
}

double orientation(const point& p1, const point& p2, const point& p3)
{
    /// @brief returns 0 if the point are lyng in the same line,
    /// a positive value if the points are clockwise
    /// and negative if the points are counterclockwise
    return (p2.y() - p1.y()) * (p3.x() - p2.x()) - (p2.x() - p1.x()) * (p3.y() - p2.y());
}

point p0;
bool compare(const point& p1, const point& p2)
{
    double orient = orientation(p0, p1, p2);
    return orient > 0 ? true :
           orient < 0 ? false :
           (distance(p0, p2) >= distance(p0, p1)) ? false : true;
}

std::stack<point> graham_scan(std::vector<point> vec)
{
    if (vec.size() < 3) {
        return std::stack<point>();
    }
    //STEP 1.
    //first of all we need the bottomest point
    double y_min = vec[0].y();
    int min = 0;
    for (auto i = 1; i < vec.size(); ++i) {
        double y_cur = vec[i].y();
        if ((y_cur < y_min) || (y_min == y_cur && vec[i].x() < vec[min].x())) {
            y_min = vec[i].y();
            min = i;
        }
    }
    swap(vec[0], vec[min]);

    // Sort n-1 points with respect to the first point.  A point p1 comes
    // before p2 in sorted ouput if p2 has larger polar angle (in
    // counterclockwise direction) than p1
    p0 = vec[0];
    //STEP 2.
    std::sort(vec.begin() + 1, vec.end(), compare);
    //STEP 3
    std::stack<point> result;
    result.push(vec[0]);
    result.push(vec[1]);
    result.push(vec[2]);
    for (auto i = 3; i < vec.size(); ++i) {
        while ((orientation(next_to_top(result), result.top(), vec[i]) <= 0) &&
                (result.size() > 2)) {
            result.pop();
        }
        result.push(vec[i]);
    }
    if (orientation(next_to_top(result), result.top(), p0) <= 0) {
        result.pop();
    }
    return result;
}

} // namespace convex_hull
