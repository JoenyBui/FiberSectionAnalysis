#include "StdAfx.h"
#include "StrandFiber2D.h"

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void StrandFiber2D::Initialize(int ID = 0,
							   double X = 0.0,
							   double Y = 0.0, 
							   double Diameter = 0.0)
{
	// Set the ID.
	MyID = ID;

	// Set the (x, y) coordinate.
	MyX = X;
	MyY = Y;

	// Diameter.
	MyDiameter = Diameter;

	// Find the area.
	MyArea = PI*pow(Diameter / 2, 2);

	// Find the Inertia.
	MyInertiaX = PI * pow(Diameter / 2, 4) / 4;
	MyInertiaY = PI * pow(Diameter / 2, 4) / 4;
};

///<summary></summary>
///<param name="ID"></param>
///<param name="Material"></param>
///<param name="X"></param>
///<param name="Y"></param>
///<param name="Diameter"></param>
///<remarks>description</remarks>
StrandFiber2D::StrandFiber2D(int ID, 
							 Material2D& Material,
							 double X,
							 double Y,
							 double Diameter)
{
	// Initialize variables.
	this -> Initialize(ID, 
					   X, 
					   Y, 
					   Diameter);

	// Store the material pointers.
	this -> SetMaterial(Material);
};

StrandFiber2D::StrandFiber2D(int ID,
							 Material2D *Material,
							 double X,
							 double Y,
							 double Diameter)
{
	// Initialize variables.
	this -> Initialize(ID, 
					   X, 
					   Y, 
					   Diameter);

	// Store the material pointers.
	this -> SetMaterial(*Material);
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
StrandFiber2D::StrandFiber2D(void)
{
	this -> Initialize();
}

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
StrandFiber2D::~StrandFiber2D(void)
{
}

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
StrandFiber2D& StrandFiber2D::operator =(const StrandFiber2D &Fiber)
{
	// Initialize variables.
	this -> Initialize(Fiber.MyID, 
					   Fiber.MyX, 
					   Fiber.MyY, 
					   Fiber.MyDiameter);

	// Store the material pointers.
	MyMaterial = Fiber.MyMaterial;

	return *this;
};

///<summary>Return the diameter of the strand.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double StrandFiber2D::GetDiameter()
{
	return MyDiameter;
};