//#include "StdAfx.h"
#include "Material2D.h"

using namespace std;
using namespace arma;

///<summary>Default Constructor.</summary>
///<remarks>description</remarks>
Material2D::Material2D(void)
{
};

///<summary>Default Destructor.</summary>
///<param name="name"></param>
///<remarks>description</remarks>
Material2D::~Material2D(void)
{
};

///<summary></summary>
///<param name="Material"></param>
///<remarks>description</remarks>
Material2D& Material2D::operator =(const Material2D &Material)
{
	// Storing the Material.
	MyID = Material.MyID;

	return *this;
};

///<summary>Add the Dynamic Increase Factor.</summary>
///<param name="YieldDIF"></param>
///<param name="UltimateDIF"></param>
///<returns>description</returns>
///<remarks>description</remarks>
void Material2D::IncludeDynamicIncreaseFactor(double YieldDIF, 
											  double UltimateDIF)
{
	IncludeDIF = true;

	MyYieldDIF = YieldDIF;
	MyUltimateDIF = UltimateDIF;
};

///<summary>Set the ID of the material.</summary>
///<param name="ID">Material ID.</param>
///<remarks>description</remarks>
void Material2D::SetID(int ID)
{
	MyID = ID;
};

///<summary>Set the Density of the fiber.</summary>
///<param name="Density">Unit weight of the fiber.</param>
///<remarks>description</remarks>
void Material2D::SetDensity(double Density)
{
	MyMassDensity = Density;
};


///<summary>Return the ID of the material.</summary>
///<remarks>description</remarks>
int Material2D::GetID()
{
	return MyID;
};

///<summary>Return the Density of the material.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double Material2D::GetDensity()
{
	return MyMassDensity;
};

void Material2D::Print()
{

};
