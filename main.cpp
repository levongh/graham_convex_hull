#include <iostream>

#include "graham_convex_hull.h"

int main()
{
    auto result = convex_hull::graham_scan({
            { 1.0, 2.0 },
            { 1.0, 3.0 },
            { 6.0, 2.0 },
            { 4.0, 3.0 },
            { 8.0, 8.0 },
            { 1.0, 9.0 },
            { 0.0, 2.0 }
            });
    while (!result.empty()) {
        const auto& p = result.top();
        std::cout << p.x() << ' ' << p.y() << '\n';
        result.pop();
    }
	return 0;
}
