#include<iostream>
#include<iomanip>
#include<fstream>
#include <set>
#include<cmath>
using namespace std;

class Point {
public:
	double pointX;
	double pointY;

	Point(double x, double y) { pointX = x; pointY = y; }
	bool operator< (const Point l1)const {
		return memcmp(this, &l1, sizeof(l1)) < 0;
	}
};

set<Point> pointSet;

class Line{
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

Point Line::GetCrossPoint(Line l1)
{
	double D;
	D = l1.a * this->b - this->a * l1.b;
	if (!D)
	{
		throw exception();
	}
	Point pTemp(0, 0);
	pTemp.pointX = (l1.b * this->c - this->b * l1.c) / D;
	pTemp.pointY = (l1.c * this->a - this->c * l1.a) / D;
	return pTemp;
}

class Circle
{
public:
	Point center;
	double r;
	Circle(Point p, int i) : center(p),r(i) {};
	int GetCrossToCircle(Circle c1);
	int GetCrossToLine(Line l1);
	bool operator< (const Circle c1)const {
		return memcmp(this, &c1, sizeof(c1)) < 0;
	}
};

int Circle::GetCrossToCircle(Circle c1)
{
	double a1, b1, r1, a0, b0, r0;
	a0 = center.pointX;
	b0 = center.pointY;
	r0 = r;
	a1 = c1.center.pointX;
	b1 = c1.center.pointY;
	r1 = c1.r;
	double a12 = a1 * a1, b12 = b1 * b1, r12 = r1 * r1, a02 = a0 * a0, b02 = b0 * b0, r02 = r0 * r0;
	double delta = (-a02 + 2 * a0 * a1 - a12 - b02 + 2 * b0 * b1 - b12 + r02 + 2 * r0 * r1 + r12) * (a02 - 2 * a0 * a1 + a12 + b02 - 2 * b0 * b1 + b12 - r02 + 2 * r0 * r1 - r12);
	if (delta < 0)
	{
		return 0;
	}
	double delta_1 = a0 * b02 - a02 * a1 - a0 * a12 + a0 * b12 + a1 * b02 + a1 * b12 - a0 * r02 + a0 * r12 + a1 * r02 - a1 * r12 + a02 * a0 + a12 * a1 - 2 * a0 * b0 * b1 - 2 * a1 * b0 * b1;
	double delta_2 = sqrt(delta);
	double delta_3 = 2 * (a02 - 2 * a0 * a1 + a12 + b02 - 2 * b0 * b1 + b12);
	double delta_4 = a02 * b0 + a02 * b1 + a12 * b0 + a12 * b1 - b0 * b12 - b02 * b1 - b0 * r02 + b0 * r12 + b1 * r02 - b1 * r12 + b0 * b02 + b1 * b12 - 2 * a0 * a1 * b0 - 2 * a0 * a1 * b1;
	Point cross1((delta_1 - b0 * delta_2 + b1 * delta_2) / delta_3, (delta_4 + a0 * delta_2 - a1 * delta_2) / delta_3);
	Point cross2((delta_1 + b0 * delta_2 - b1 * delta_2) / delta_3, (delta_4 - a0 * delta_2 + a1 * delta_2) / delta_3);
	pointSet.insert(cross1);
	pointSet.insert(cross2);
	return 2;
}

int Circle::GetCrossToLine(Line l1)
{
	double length = fabs(l1.a * center.pointX + l1.b * center.pointY + l1.c) / sqrt(l1.a * l1.a + l1.b * l1.b);
	if (length > r) {
		return 0;
	}
	Line lr(l1.b, -l1.a, l1.a * center.pointY - l1.b * center.pointX);
	Point t1 = lr.GetCrossPoint(l1);
	
	if (length == r)
	{
		pointSet.insert(t1);
		return 1;
	}
	double dd = sqrt(r * r - length * length), length2 = sqrt(l1.a * l1.a + l1.b * l1.b);
	double shiftX = -dd * l1.b / length2, shiftY = dd * l1.a / length2;
	Point cross1(t1.pointX + shiftX, t1.pointY + shiftY);
	Point cross2(t1.pointX - shiftX, t1.pointY - shiftY);
	pointSet.insert(cross1);
	pointSet.insert(cross2);
	return 2;
}

void main(int argc, char** argv)
{
	ifstream infile;
	ofstream outfile;
	int n;
	double x0, x1, y0, y1;
	char type, c1, d0;
	set<Line> lineSet;
	set<Circle> circleSet;
	if (!strcmp(argv[1], "-i") && !strcmp(argv[3], "-o"))
	{
		infile = ifstream(argv[2]);
		outfile = ofstream(argv[4]);
	}
	else if (!strcmp(argv[3], "-i") && !strcmp(argv[1], "-o"))
	{
		infile = ifstream(argv[4]);
		outfile = ofstream(argv[2]);
	}
	else
	{
		exit(0);
	}
	infile >> n;
	for (int i = 0; i < n; i++)
	{
		infile >> type;
		if (type == 'L')
		{
			infile >> x0 >> y0 >> x1 >> y1;
			Line l(x0, y0, x1, y1);
			for (Line temp : lineSet) {
				try
				{
					Point tp = l.GetCrossPoint(temp);
					pointSet.insert(tp);
				}
				catch (const exception&) {}
			}
			for (Circle temp : circleSet) {
				temp.GetCrossToLine(l);
			}
			lineSet.insert(l);
		}
		else if (type == 'C')
		{
			infile >> x0 >> y0 >> x1;
			Circle circle(Point(x0, y0), x1);
			for (Line temp : lineSet) {
				circle.GetCrossToLine(temp);
			}
			for (Circle temp : circleSet)
			{
				circle.GetCrossToCircle(temp);
			}
			circleSet.insert(circle);
		}
	}
	outfile << pointSet.size() << endl;
}

