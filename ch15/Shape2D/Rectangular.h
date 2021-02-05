#pragma once
#include "Shape2D.h"
class Rectangular: public Shape2D{
public:
	typedef std::pair<double, double> Coordinate;
	typedef std::pair<Coordinate, double> Position;

	Rectangular(const std::string &i, const std::string &n, 
			double len, double wid,  // size 
			double llxx, double llyy, double ang):  // position
			Shape2D(i,n), length(len), width(wid), llx(llxx), lly(llyy), angle(ang){}
	Rectangular():Shape2D(), length(0.0), width(0.0), llx(0.0), lly(0.0), angle(0.0){}

	double getArea() const override { return length*width; }
	double getPerimeter() const override { return 2*(length+width); }
	void printInfo() const override; 
	virtual Position getPosition() const { return {{llx, lly}, angle}; }
	

protected:
	double length, width;
	double llx, lly;
	double angle;
};

void Rectangular::printInfo() const { 
	Shape2D::printInfo();
	std::cout<<"length: "<<length<<" width: "<<width<<std::endl;
	std::cout<<"coordinate: "<<llx<<", "<<lly<<" angle: "<<angle<<std::endl;
}
