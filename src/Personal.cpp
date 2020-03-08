#include<iostream>
#include<iomanip>
#include<fstream>
#include <set>
using namespace std;

constexpr auto N = 6;
class Point {
public:
	double pointX;
	double pointY;

	Point(double x, double y) { pointX = x; pointY = y; }
	bool operator< (const Point l1)const {
		return this->pointX < l1.pointX && this->pointY < l1.pointY;
	}
};

class Line{
public:
	double a;
	double b;
	double c;
public:
	Line() {};
	Line(double x0, double y0, double x1, double y1) {
		a = y1 - y0;
		b = x0 - x1;
		c = x1 * y0 - x0 * y1;
	};
	Line GetLine(Point ptSource, Point ptDestination);
	Point GetCrossPoint(Line l1);

	bool operator< (const Line l1)const {
		return this->a < l1.a && this->b < l1.b && this->c < l1.c;
	}
};

Line Line::GetLine(Point ptSource, Point ptDestination)
{
	Line lTemp;
	lTemp.a = ptSource.pointY - ptDestination.pointY;
	lTemp.b = ptDestination.pointX - ptSource.pointX;
	lTemp.c = ptSource.pointX * ptDestination.pointY - ptDestination.pointX * ptSource.pointY;
	return lTemp;
}

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


void main(int argc, char** argv)
{
	ifstream infile;
	ofstream outfile;

	int n;
	double x0, x1, x2, x3, y0, y1, y2, y3;
	char type, c1, d0;
	set<Line> lineSet;
	set<Point> pointSet;
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
			lineSet.insert(l);
		}
		else if (type == 'C')
		{

		}
	}
	outfile << pointSet.size() << endl;
}