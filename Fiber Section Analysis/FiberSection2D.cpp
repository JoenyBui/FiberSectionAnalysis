#include "StdAfx.h"
#include "FiberSection2D.h"

FiberSection2D::FiberSection2D(void)
{
}

FiberSection2D::~FiberSection2D(void)
{
}

FiberSection2D& FiberSection2D::operator =(const FiberSection2D &Section)
{
	return *this;
};

FiberSection2D::FiberSection2D(const FiberSection2D &Section)
{

};

void FiberSection2D::Analyze()
{
	this -> CalculateArea();
	this -> CalculateCentroid();
	this -> CalculateInertia();

	this -> CalculateFullMomentCurvatureX();
	this -> CalculateFullMomentCurvatureY();
};

void FiberSection2D::CalculateFullMomentCurvatureX()
{
	
};

///<summary></summary>
///<remarks>description</remarks>
void FiberSection2D::CalculateFullMomentCurvatureY()
{
	
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void FiberSection2D::CalculateCentroid()
{
	// Calculate the X-Axis.

	// Calculate the Y-Axis.
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void FiberSection2D::CalculateArea()
{

};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void FiberSection2D::CalculateInertia()
{

};

vector <vector<double>> FiberSection2D::GetMomentCurvatureY()
{
	// Add the curvature.
	vector <vector<double>> Curvature;

	size_t NegativeY_Size = MyNegativeCurvatureY.size();
	size_t PositiveY_Size = MyPositiveCurvatureY.size();

	// Add the Curvature for the Negative Side.
	for (size_t i = 0; i < NegativeY_Size; i++)
	{
		Curvature.push_back(MyNegativeCurvatureY[NegativeY_Size - 1 - i]);
	};

	// Add the Curvature for the Positive Side.
	for (size_t j = 1; j < PositiveY_Size; j++)
	{
		Curvature.push_back(MyPositiveCurvatureY[j]);
	};

	return Curvature;
};

///<summary></summary>
///<returns>description</returns>
///<remarks>description</remarks>
Section2D FiberSection2D::GetBiLinearSection()
{
	Section2D BiLinearSection;

	return BiLinearSection;
};

///<summary>Set the tolerance of the section.</summary>
///<param name="name"></param>
///<remarks>description</remarks>
void FiberSection2D::SetTolerance(double Tolerance)
{
	MyForceTolerance = Tolerance;
};

///<summary>Return the Density of the Section.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double FiberSection2D::GetMassDensity()
{
	double MassPerArea = 0.0;
	double Area = 0.0;

	for (size_t i = 0; i < MyFibers.size(); i++)
	{
		// Add to Area.
		Area += MyFibers[i].GetArea();

		// Add to Ratio.
		MassPerArea += MyFibers[i].GetArea() * MyFibers[i].GetDensity();
	};

	return MassPerArea / Area;
};

///<summary>Return the Mass per Unit Length of the section.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double FiberSection2D::GetMassPerUnitLength()
{
	double MassPerLength = 0.0;

	for (size_t i = 0; i < MyFibers.size(); i++)
	{
		MassPerLength += MyFibers[i].GetArea() * MyFibers[i].GetDensity();
	};

	return MassPerLength;
};

