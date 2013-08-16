#include "StdAfx.h"
#include "ConcreteFiber2D.h"

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void ConcreteFiber2D::Initialize(int ID = 0, 
								 double X = 0.0, 
								 double Y = 0.0, 
								 double Width = 0.0, 
								 double Thickness = 0.0)
{
	// Store the Content.
	MyID = ID;

	MyX = X;
	MyY = Y;
	
	// Set the thickness.
	MyWidth = Width;
	MyThickness = Thickness;

	// Set the Area.
	MyArea = MyWidth * MyThickness;

	// Inertia about the X-X axis.
	MyInertiaX = MyWidth * pow(MyThickness, 3) / 12;

	// Inertia about the Y-Y axis.
	MyInertiaY = MyThickness * pow(MyWidth, 3) / 12;
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
ConcreteFiber2D::ConcreteFiber2D(int ID, 
								 Material2D& Material,
								 double X, 
								 double Y, 
								 double Width, 
								 double Thickness)
{
	// Initialize variables.
	this -> Initialize(ID, X, Y, Width, Thickness);

	// Store the material reference.
	MyMaterial = &Material;
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
ConcreteFiber2D::ConcreteFiber2D(void)
{
	this -> Initialize();
}

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
ConcreteFiber2D::~ConcreteFiber2D(void)
{
}

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
ConcreteFiber2D& ConcreteFiber2D::operator =(const ConcreteFiber2D &Fiber)
{
	// Initialize the fiber.
	this -> Initialize(Fiber.MyID, 
					   Fiber.MyX, 
					   Fiber.MyY, 
					   Fiber.MyWidth, 
					   Fiber.MyThickness);

	// Store the material pointers.
	MyMaterial = Fiber.MyMaterial;

	return *this;
};

///<summary>Add the binding reinforcement that contributes to the tension stiffening effect.</summary>
///<param name="name"></param>
///<remarks>description</remarks>
void ConcreteFiber2D::AddBindingReinforcement(Fiber2D *Fiber)
{
	MyVectorReinforcement.push_back(Fiber);
};

///<summary>Return the force of the section.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double ConcreteFiber2D::GetForce(double Strain,
								 double Curvature)
{
	// Check if the any of the binding reinforcement has yielded.
	bool AddBindingReinforcement = false;

	// Check if the Concrete Fiber Strain is beyond tension stiffening.
	if (MyMaterial ->GetTensionYieldStrain() < Strain)
	{
		for (size_t i = 0; i < MyVectorReinforcement.size(); i++)
		{
			double ReinforcementStrain = Strain - Curvature * (MyY - MyVectorReinforcement[i] -> GetY());

			// If one of the binding reinforcement has not yielded than include tension stiffening.
			if (!MyVectorReinforcement[i] -> IsStrainAtYield(ReinforcementStrain))
			{
				AddBindingReinforcement = true;
			};
		};
	};

	// Cast Type Pointer to the Concrete Material.
	ConcreteMaterial2D* ConcreteMaterial = dynamic_cast <ConcreteMaterial2D*> (MyMaterial);
	
	// Return the Strain.
	double Stress = ConcreteMaterial -> GetStress(Strain, AddBindingReinforcement);
	
	// Get the Force.
	return Stress * MyArea;
};