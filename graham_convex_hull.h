#pragma once

#include <stack>
#include <cmath>
#include <vector>
#include <algorithm>


namespace convex_hull {
	
struct point
{
private:
	float x_coord;
	float y_coord;

public:
	float x() const
	{
		return x_coord;
	}
	float y() const
	{
		return y_coord;
	}

};

point nextToTop(std::stack<point> &s)
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

int orientation(const point& p1, const point& p2, const point& p3)
{
	double result = (p2.y() - p1.y()) * (p3.x() - p2.x()) - (p2.x() - p1.x()) * (p3.y() - p2.y());
	/// @brief if result == 0 the point are lyng in the same line
	if (result == 0) {
		return 0;
	}
	/// @brief when result > 0 then points are lying clockwise otherwise conterclockwise
	return (result > 0) ? 1 : 2;
}

point p0;
int compare(const point& p1, const point& p2)
{
	int orient = orientation(p0, p1, p2);
	if (orient == 0) {
		return (distance(p0, p2) >= distance(p0, p1)) ? -1 : 1;
	}
	return (orient == 2) ? -1 : 1;
}

void graham_scan(std::vector<point> &vec)
{
	if (vec.size() < 3) {
		return;
	}
	//STEP 1.
	//first of all we need the bottomest point
	float yMin = vec[0].y();
	int min = 0;
	for (auto i = 1; i < vec.size(); ++i) {
		float yCur = vec[i].y();
		if ((yCur < yMin) || (yMin == yCur && vec[i].x() < vec[min].x())) {
			yMin = vec[i].y();
			min = i;
		}
	}
	swap(vec[0], vec[min]);

	// Sort n-1 points with respect to the first point.  A point p1 comes
	// before p2 in sorted ouput if p2 has larger polar angle (in
	// counterclockwise direction) than p1
	p0 = vec[0];
	//STEP 2.
	std::sort(vec.begin(), vec.end(), compare);
		//STEP 3
	std::stack<point> S;
	S.push(vec[0]);
	S.push(vec[1]);
	S.push(vec[2]);
	for (auto i = 3; i < vec.size(); i++) {
		while ((orientation(nextToTop(S), S.top(), vec[i]) != 2) && (S.size() > 3))
			S.pop();
		S.push(vec[i]);
	}
}

} // namespace convex_hull