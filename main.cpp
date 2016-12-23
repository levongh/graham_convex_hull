#include <iostream>

#include "graham_convex_hull.h"

int main()
{
    std::vector<convex_hull::point> points;
    for (int x = 0; x <= 10000; ++x) {
        if (x <= 5000) {
            for (int y = 0; y <= x; ++y) {
                points.push_back({x, y});
            }
        } else {
            for (int y = 0; y <= 10000 - x; ++y) {
                points.push_back({x, y});
            }
        }
    }
    auto result = convex_hull::graham_scan(points);
    while (!result.empty()) {
        const auto& p = result.top();
        std::cout << p.x() << ' ' << p.y() << '\n';
        result.pop();
    }
	return 0;
}
