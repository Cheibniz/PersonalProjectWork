#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include"Personal.h"
#include <random>
using namespace std;

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
	double a0 = l1.a, b0 = l1.b, c0 = l1.c, a1 = center.pointX, b1 = center.pointY, r1 = r;
	double a12 = a1 * a1, b12 = b1 * b1, r12 = r1 * r1, a02 = a0 * a0, b02 = b0 * b0, c02 = c0 * c0;
	double delta = -a02 * a12 + a02 * r12 - 2 * a0 * a1 * b0 * b1 - 2 * a0 * a1 * c0 - b02 * b12 + b02 * r12 - 2 * b0 * b1 * c0 - c02;
	if (delta < 0) {
		return 0;
	}
	double delta_1 = a02 + b02;
	Line lr(l1.b, -l1.a, l1.a * center.pointY - l1.b * center.pointX);
	Point t1 = lr.GetCrossPoint(l1);
	double delta_2 = sqrt(delta);
	double delta_3 = a0 * c0 - a1 * b02 + a0 * b0 * b1;
	double delta_4 = b0 * c0 - a02 * b1 + a0 * a1 * b0;
	Point cross1(-(delta_3 - b0 * delta_2) / delta_1, -(delta_4 + a0 * delta_2) / delta_1);
	Point cross2(-(delta_3 + b0 * delta_2) / delta_1, -(delta_4 - a0 * delta_2) / delta_1);
	pointSet.insert(cross1);
	pointSet.insert(cross2);
	return 2;
}

int main(int argc, char** argv)
{
	ifstream infile;
	ofstream outfile;
	int n;
	double x0, x1, y0, y1;
	char type;
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
	/*for (int i = 0; i < 10000; i++)
	{
		cout << pointSet.size() << endl;
	}*/
	
	return 0;
}

