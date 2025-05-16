#ifndef POINT_H
#define POINT_H

struct Point
{
	double x;
	double y;
};

inline bool operator==(const Point& firstPoint, const Point& secondPoint)
{
	return firstPoint.x == secondPoint.x && firstPoint.y == secondPoint.y;
}

#endif // POINT_H
