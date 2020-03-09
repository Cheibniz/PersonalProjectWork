#ifndef _PERSONAL_H_
#define _PERSONAL_H_
#include <unordered_set>

#define EPS 1e-10
using namespace std;

class Point {
public:
	double pointX;
	double pointY;
	Point(double x, double y) { pointX = x; pointY = y; }
	bool operator< (const Point l1)const {
		//return memcmp(this, &l1, sizeof(l1)) < 0;
		
		if (fabs(pointX - l1.pointX) < EPS)
		{
			if (fabs(pointY - l1.pointY) < EPS) {
				return false;
			}
			
		}
		return true;
	}
};

struct MyStruct
{

};

class Line {
public:
	double a;
	double b;
	double c;
public:
	//Line() {};
	Line(double x0, double y0, double x1, double y1) {
		a = y1 - y0;
		b = x0 - x1;
		c = x1 * y0 - x0 * y1;
	};
	Line(double x0, double y0, double x1) {
		a = x0;
		b = y0;
		c = x1;
	};
	Point GetCrossPoint(Line l1);

	bool operator< (const Line l1)const {
		return memcmp(this, &l1, sizeof(l1)) < 0;
	}
};
struct RecordHash
{
	size_t operator()(const Point& rhs) const {
		return hash<double>()(rhs.pointX) ^ hash<double>()(rhs.pointY);
	}
};
struct RecordCmp
{
	bool operator()(const Point& lhs, const Point& rhs) const {
		return fabs(lhs.pointX - rhs.pointX) < EPS && fabs(lhs.pointY - rhs.pointY) < EPS;
	}
};
class Circle
{
public:
	Point center;
	double r;
	Circle(Point p, double i) : center(p), r(i) {};
	int GetCrossToCircle(Circle c1);
	int GetCrossToLine(Line l1);
	bool operator< (const Circle c1)const {
		return memcmp(this, &c1, sizeof(c1)) < 0;
	}
};

unordered_set<Point, RecordHash, RecordCmp> pointSet;
//set<pair<double, double>> pointSet;
//set<Point> pointSet;
#endif