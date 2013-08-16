#include "StdAfx.h"
#include "RebarFiber2D.h"

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void RebarFiber2D::Initialize(int ID = 0,
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

	// Find the Area.
	MyArea = PI * pow(Diameter / 2, 2);

	// Find the Inertia.
	MyInertiaX = PI * pow(Diameter / 2, 4) / 4;
	MyInertiaY = PI * pow(Diameter / 2, 4) / 4;
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
RebarFiber2D::RebarFiber2D(int ID, 
						   Material2D &Material, 
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

RebarFiber2D::RebarFiber2D(int ID, 
						   Material2D &Material, 
						   double X, 
						   double Y, 
						   int BarType)
{
	
	this -> SetBarType(BarType);

	// Initialize variables.
	this -> Initialize(ID, 
					   X, 
					   Y, 
					   MyDiameter);

	// Store the material pointers.
	this -> SetMaterial(Material);
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
RebarFiber2D::RebarFiber2D(int ID, 
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

RebarFiber2D::RebarFiber2D(int ID, 
						   Material2D *Material, 
						   double X, 
						   double Y, 
						   int BarType)
{
	
	this -> SetBarType(BarType);

	// Initialize variables.
	this -> Initialize(ID, 
					   X, 
					   Y, 
					   MyDiameter);

	// Store the material pointers.
	this -> SetMaterial(*Material);
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
RebarFiber2D::RebarFiber2D(void)
{
	this -> Initialize();
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
RebarFiber2D::~RebarFiber2D(void)
{
};

///<summary>Set according to ACI 318-08.</summary>
///<param name="name"></param>
///<remarks>description</remarks>
void RebarFiber2D::SetBarType(int BarType)
{
	switch (BarType)
	{
		case Type_No3:
			MyDiameter = 0.375;
			MyArea = 0.11;

			break;
		case Type_No4:
			MyDiameter = 0.500;
			MyArea = 0.20;

			break;
		case Type_No5:
			MyDiameter = 0.625;
			MyArea =0.31;

			break;
		case Type_No6:
			MyDiameter = 0.750;
			MyArea = 0.44;

			break;
		case Type_No7:
			MyDiameter = 0.875;
			MyArea =0.60;

			break;
		case Type_No8:
			MyDiameter = 1.00;
			MyArea = 0.79;

			break;
		case Type_No9:
			MyDiameter = 1.128;
			MyArea = 1.00;

			break;
		case Type_No10:
			MyDiameter = 1.270;
			MyArea = 1.27;

			break;
		case Type_No11:
			MyDiameter = 1.410;
			MyArea = 1.56;

			break;
		case Type_No14:
			MyDiameter = 1.693;
			MyArea = 2.25;

			break;
		case Type_No18:
			MyDiameter = 2.257;
			MyArea = 4.00;

			break;
	};
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
RebarFiber2D& RebarFiber2D::operator= (const RebarFiber2D &Fiber)
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
double RebarFiber2D::GetDiameter()
{
	return MyDiameter;
};