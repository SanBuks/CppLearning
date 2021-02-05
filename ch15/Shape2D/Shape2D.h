#pragma once
#include <utility>
#include <string>
#include <iostream>

class Shape2D{
public:
	Shape2D(const std::string &i, const std::string &n):id(i), name(n){}
	Shape2D():id("00000"), name("Default_Name"){ } 
	~Shape2D(){}

	virtual double getArea() const =0; 
	virtual double getPerimeter() const =0;
	virtual void printInfo() const;

protected:
	std::string id;
	std::string name;
};

void Shape2D::printInfo()const{ std::cout<<"id: "<<id<<" name: "<<name<<std::endl; }
