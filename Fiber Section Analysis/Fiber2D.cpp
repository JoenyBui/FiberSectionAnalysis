#include "StdAfx.h"
#include "Fiber2D.h"

using namespace std;
using namespace arma;

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
Fiber2D::Fiber2D(void)
{
}

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
Fiber2D::~Fiber2D(void)
{
}

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
Fiber2D& Fiber2D::operator =(const Fiber2D &Fiber)
{
	MyID = Fiber.MyID;
	
	MyX = Fiber.MyX;
	MyY = Fiber.MyY;

	MyArea = Fiber.MyArea;

	MyInertiaX = Fiber.MyInertiaX;
	MyInertiaY = Fiber.MyInertiaY;

	return *this;
};

///<summary>Return the Fiber ID.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
int Fiber2D::GetID()
{
	return MyID;
};

///<summary>Return Material ID.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
int Fiber2D::GetMaterialID()
{
	return MyMaterial -> GetID();
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void Fiber2D::SetMaterial(Material2D &Material)
{
	MyMaterial = &Material;
};



///<summary>Returnt the X coordinate of the centroid of the fiber.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double Fiber2D::GetX()
{
	return MyX;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double Fiber2D::GetY()
{
	return MyY;
};

///<summary>Return the Area of the Fiber.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double Fiber2D::GetArea()
{
	return MyArea;
};

///<summary>Return the X Inertia of the Fiber.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double Fiber2D::GetInertiaX()
{
	return MyInertiaX;
};

///<summary>Return the Y Inertia of the Fiber.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double Fiber2D::GetInertiaY()
{
	return MyInertiaY;
};

///<summary>Return the Density of the Fiber.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double Fiber2D::GetDensity()
{
	return MyMaterial -> GetDensity();
};

///<summary>Return the force.</summary>
///<param name="Strain"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double Fiber2D::GetForce(double Strain)
{
	// Return the Strain.
	double Stress = MyMaterial -> GetStress(Strain);

	// Get the Force.
	return Stress * MyArea;
};

///<summary>Determine if the strain is at it's yielding limit.</summary>
///<param name="Strain">The strain of the fiber.</param>
///<returns>Return true for reaching yield, flase because it has not.</returns>
///<remarks>description</remarks>
bool Fiber2D::IsStrainAtYield(double Strain)
{
	return MyMaterial -> IsStrainAtYield(Strain);
};

///<summary>Determine if the strain is at its maximum limit.</summary>
///<param name="Strain">The strain of the fiber.</param>
///<returns>Returns true for reaching maximum, false because it has not.</returns>
///<remarks>description</remarks>
bool Fiber2D::IsStrainAtMaximum(double Strain)
{
	return MyMaterial -> IsStrainAtMaximum(Strain);
};

///<summary>Print the fiber infomation.</summary>
///<param name="name"></param>
///<remarks>description</remarks>
void Fiber2D::Print()
{
	cout << "Fiber ID: \t" << MyID << endl;
	cout << "X       : \t" << MyX << endl;
	cout << "Y       : \t" << MyY << endl;
	cout << "Area    : \t" << MyArea << endl;
};