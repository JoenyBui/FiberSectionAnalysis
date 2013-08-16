#include "StdAfx.h"
#include "ForceFiber2D.h"

void ForceFiber2D::Initialize(int ID = -1,
							  double Magnitude = 0.0,
							  double X = 0.0,
							  double Y = 0.0)
{ 
	// Store the ID.
	MyID = ID;

	// Store the Magnitude;
	MyMagnitude = Magnitude;

	// Store the X and Y coordinates.
	MyX = X;
	MyY = Y;
};

ForceFiber2D::ForceFiber2D(int ID,
						   double Magnitude, 
						   double X, 
						   double Y)
{ 
	this -> Initialize(ID, Magnitude, X, Y);
};

ForceFiber2D::ForceFiber2D(void)
{
	this -> Initialize();
};

ForceFiber2D::~ForceFiber2D(void)
{
};

ForceFiber2D& ForceFiber2D:: operator= (const ForceFiber2D &Section)
{ 
	this -> Initialize(Section.MyID,
					   Section.MyMagnitude,
					   Section.MyX,
					   Section.MyY);

	return *this;	
};

ForceFiber2D::ForceFiber2D(const ForceFiber2D &Section)
{ 
	this -> Initialize(Section.MyID,
					   Section.MyMagnitude,
					   Section.MyX,
					   Section.MyY);
};

double ForceFiber2D::GetX()
{ 
	return MyX;
};

double ForceFiber2D::GetY()
{ 
	return MyY;
};

double ForceFiber2D::GetMagnitude()
{ 
	return MyMagnitude;
};