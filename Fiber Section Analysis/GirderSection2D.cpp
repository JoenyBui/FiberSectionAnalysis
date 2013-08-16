#include "StdAfx.h"

#include "GirderSection2D.h"

using namespace std;
using namespace arma;

void GirderSection2D::Initialize(double D1 = 0.0,
								 double D2 = 0.0,
								 double D3 = 0.0, 
								 double D4 = 0.0,
								 double D5 = 0.0,
								 double D6 = 0.0,
								 double W1 = 0.0,
								 double W2 = 0.0, 
								 double W3 = 0.0, 
								 double W4 = 0.0,
								 double W5 = 0.0,
								 double W6 = 0.0,
								 string GirderType = "Unknown Girder Type",
								 double DesiredFiberIncrement = 0.1,
								 double Tolerance = 100)
{
	// Store the Girder Dimension.
	MyD1 = D1;
	MyD2 = D2;
	MyD3 = D3;
	MyD4 = D4;
	MyD5 = D5;
	MyD6 = D6;

	// Save D7
	MyD7 = MyD1 - MyD2 - MyD3 - MyD4 - MyD5 - MyD6;

	MyW1 = W1;
	MyW2 = W2;
	MyW3 = W3;
	MyW4 = W4;
	MyW5 = W5;
	MyW6 = W6;

	// Girder Type
	MyGirderType = GirderType;

	// Increment in 'inches'.
	MyDesiredFiberIncrement = DesiredFiberIncrement;

	// Tolerance for Sum of Forces.
	MyForceTolerance = Tolerance;
};

GirderSection2D::GirderSection2D(int TypeOfGirder)
{
	// Initialize first.
	this -> Initialize();

	// Set the girder dimension.
	this -> SetGirderDimension(TypeOfGirder);

	// Increment in 'inches'.
	MyDesiredFiberIncrement = 1.0;
};

GirderSection2D::GirderSection2D(vector <double> *Widths,
								 vector <double> *Depths,
								 double DesiredIncrement,
								 double Tolerance)
{
	double LocalWidths[5];
	double LocalDepths[5];

	LocalDepths[0] = (*Depths)[0];
	LocalDepths[1] = (*Depths)[1];
	LocalDepths[2] = (*Depths)[2];
	LocalDepths[3] = (*Depths)[3];
	LocalDepths[4] = (*Depths)[4];
	LocalDepths[5] = (*Depths)[5];

	LocalWidths[0] = (*Widths)[0];
	LocalWidths[1] = (*Widths)[1];
	LocalWidths[2] = (*Widths)[2];
	LocalWidths[3] = (*Widths)[3];
	LocalWidths[4] = (*Widths)[4];
	LocalWidths[5] = (*Widths)[5];

	this -> Initialize(LocalDepths[0],
					   LocalDepths[1],
					   LocalDepths[2],
					   LocalDepths[3],
					   LocalDepths[4],
					   LocalDepths[5],
					   LocalWidths[0],
					   LocalWidths[1],
					   LocalWidths[2],
					   LocalWidths[3],
					   LocalWidths[4],
					   LocalWidths[5],
					   "Custom Girder", 
					   DesiredIncrement, 
					   Tolerance);
};

GirderSection2D::GirderSection2D(vector <double> Widths, 
								 vector <double> Depths, 
								 double DesiredIncrement,
								 double Tolerance)
{
	this -> Initialize(Depths[0],
					   Depths[1],
					   Depths[2],
					   Depths[3],
					   Depths[4],
					   Depths[5],
					   Widths[0],
					   Widths[1],
					   Widths[2],
					   Widths[3],
					   Widths[4],
					   Widths[5],
					   "Custom Girder", 
					   DesiredIncrement, 
					   Tolerance);
};



GirderSection2D::GirderSection2D(void)
{
	this -> Initialize();
}

GirderSection2D::~GirderSection2D(void)
{
}

GirderSection2D& GirderSection2D::operator =(const GirderSection2D &Section)
{
	this -> Clone(Section);

	return *this;
};

GirderSection2D::GirderSection2D(const GirderSection2D& Section)
{
	this -> Clone(Section);
};

void GirderSection2D::Clone(const GirderSection2D &Section)
{
	// Super Class Variable
	MyID = Section.MyID;

	MyFibers = Section.MyFibers;

	MyMaterials = Section.MyMaterials;

	MyCentroidX = Section.MyCentroidX;
	MyCentroidY = Section.MyCentroidY;

	MyInertiaX = Section.MyInertiaX;
	MyInertiaY = Section.MyInertiaY;

	MyArea = Section.MyArea;

	MyForceTolerance = Section.MyForceTolerance;

	MyPositiveCurvatureY = Section.MyPositiveCurvatureY;
	MyNegativeCurvatureY = Section.MyNegativeCurvatureY;

	// Sub-Class Variable.
	MyGirderType = Section.MyGirderType;

	MyD1 = Section.MyD1;
	MyD2 = Section.MyD2;
	MyD3 = Section.MyD3;
	MyD4 = Section.MyD4;
	MyD5 = Section.MyD5;
	MyD6 = Section.MyD6;
	MyD7 = Section.MyD7;

	MyW1 = Section.MyW1;
	MyW2 = Section.MyW2;
	MyW3 = Section.MyW3;
	MyW4 = Section.MyW4;
	MyW5 = Section.MyW5;
	MyW6 = Section.MyW6;

	MyDesiredFiberIncrement = Section.MyDesiredFiberIncrement;

	MyConcreteMaterial = Section.MyConcreteMaterial;
	MyRebarMaterials = Section.MyRebarMaterials;
	MyPrestressStrandsMaterials = Section.MyPrestressStrandsMaterials;

	MyForceFibers = Section.MyForceFibers;
	MyConcreteFibers = Section.MyConcreteFibers;
	MyRebarFibers = Section.MyRebarFibers;
	MyStrandFibers = Section.MyStrandFibers;
};

void GirderSection2D::SetGirderDimension(int TypeOfGirder)
{
	switch (TypeOfGirder)
	{
		case (ID_TypeI):
			// Depth from 1-6
			MyD1 = 28.0;
			MyD2 = 4.0;
			MyD3 = 0.0;
			MyD4 = 3.0;
			MyD5 = 5.0;
			MyD6 = 5.0;

			// Width from 1-6
			MyW1 = 12.0;
			MyW2 = 16.0;
			MyW3 = 6.0;
			MyW4 = 3.0;
			MyW5 = 0.0;
			MyW6 = 5.0;

			MyGirderType = "AASHTO Type I";

			break;
		case (ID_TypeII):
			// Depth from 1-6
			MyD1 = 36.0;
			MyD2 = 6.0;
			MyD3 = 0.0;
			MyD4 = 3.0;
			MyD5 = 6.0;
			MyD6 = 6.0;

			// Width from 1-6
			MyW1 = 12.0;
			MyW2 = 18.0;
			MyW3 = 6.0;
			MyW4 = 3.0;
			MyW5 = 0.0;
			MyW6 = 6.0;

			MyGirderType = "AASHTO Type II";

			break;
		case (ID_TypeIII):
			// Depth from 1-6
			MyD1 = 45.0;
			MyD2 = 7.0;
			MyD3 = 0.0;
			MyD4 = 4.5;
			MyD5 = 7.5;
			MyD6 = 7.0;

			// Width from 1-6
			MyW1 = 16.0;
			MyW2 = 22.0;
			MyW3 = 7.0;
			MyW4 = 4.5;
			MyW5 = 0.0;
			MyW6 = 7.5;

			MyGirderType = "AASHTO Type III";
			break;
		case (ID_TypeIV):
			// Depth from 1-6
			MyD1 = 54.0;
			MyD2 = 8.0;
			MyD3 = 0.0;
			MyD4 = 6.0;
			MyD5 = 9.0;
			MyD6 = 8.0;

			// Width from 1-6
			MyW1 = 20.0;
			MyW2 = 26.0;
			MyW3 = 8.0;
			MyW4 = 6.0;
			MyW5 = 0.0;
			MyW6 = 9.0;

			MyGirderType = "AASHTO Type IV";

			break;
		case (ID_TypeV):
			// Depth from 1-6
			MyD1 = 63.0;
			MyD2 = 5.0;
			MyD3 = 3.0;
			MyD4 = 4.0;
			MyD5 = 10.0;
			MyD6 = 8.0;

			// Width from 1-6
			MyW1 = 42.0;
			MyW2 = 28.0;
			MyW3 = 8.0;
			MyW4 = 4.0;
			MyW5 = 13.0;
			MyW6 = 10.0;

			MyGirderType = "AASHTO Type V";

			break;
		case (ID_TypeVI):
			// Depth from 1-6
			MyD1 = 72.0;
			MyD2 = 5.0;
			MyD3 = 3.0;
			MyD4 = 4.0;
			MyD5 = 10.0;
			MyD6 = 8.0;

			// Width from 1-6
			MyW1 = 42.0;
			MyW2 = 28.0;
			MyW3 = 8.0;
			MyW4 = 4.0;
			MyW5 = 13.0;
			MyW6 = 10.0;

			MyGirderType = "AASHTO Type VI";
			break;
		default:
			// Depth from 1-6
			MyD1 = 0.0;
			MyD2 = 0.0;
			MyD3 = 0.0;
			MyD4 = 0.0;
			MyD5 = 0.0;
			MyD6 = 0.0;

			// Width from 1-6
			MyW1 = 0.0;
			MyW2 = 0.0;
			MyW3 = 0.0;
			MyW4 = 0.0;
			MyW5 = 0.0;
			MyW6 = 0.0;

			MyGirderType = "Unknown Girder Type";
			break;

	};

	// Save D7
	MyD7 = MyD1 - MyD2 - MyD3 - MyD4 - MyD5 - MyD6;
};

///<summary>Add the force to the section.</summary>
///<param name="Fiber"></param>
///<remarks>description</remarks>
void GirderSection2D::AddForceFiber(ForceFiber2D Fiber)
{
	MyForceFibers.push_back(Fiber);
};

///<summary>Add the concrete material of the section.</summary>
///<param name="Material"></param>
///<remarks>description</remarks>
void GirderSection2D::AddConcreteMaterial(ConcreteMaterial2D Material)
{
	// Store the concrete material.
	MyConcreteMaterial = Material;
};

void GirderSection2D::AddConcreteMaterial(ConcreteMaterial2D *Material)
{
	// Store the concrete material.
	MyConcreteMaterial = *Material;
};

///<summary>Mesh the Concrete fiber.</summary>
///<remarks>description</remarks>
void GirderSection2D::MeshConcreteFiber()
{
	/*
                                               |<--- W5 -->|
                   |<-----             W1      ----------->|
        -------    *****************************************   [Z6]
           D2      *                                       *
        ------     *                                       *   [Z5]
           D3          *                               *
                           *                       *
        -------                  *             *               [Z4]
           D4                     *          *
        -------                    *       *                   [Z3]
                                   *       *
                                   *<- W3->*   |<-- W4
                                   *       *
                                   *       *
           D7                      *       *
                                   *       *
                                   *       *
                                   *       *
                                   *       *|--|<--W6
                                   *       *
        -------                    *       *                   [Z2]			^
           D5                    *           *								|
        -------                *               *               [Z1]			|
           D6                  *               *							|
        -------                *****************               [Z0]			_
                               <--     W2    -->
	*/

	int ID_Counter = 1;

	// Add Z-Points.
	vector <double> W_Points;
	vector <double> Z_Points;
	
	// Z0
	Z_Points.push_back(0.0);
	W_Points.push_back(MyW2);

	// Z1
	Z_Points.push_back(MyD6);
	W_Points.push_back(MyW2);

	// Z2
	Z_Points.push_back(MyD6 + MyD5);
	W_Points.push_back(MyW3);

	// Z3
	Z_Points.push_back(MyD6 + MyD5 + MyD7);
	W_Points.push_back(MyW3);

	// Z4
	Z_Points.push_back(MyD6 + MyD5 + MyD7 + MyD4);
	W_Points.push_back(MyW3 + MyW4*2);

	// Z5
	Z_Points.push_back(MyD6 + MyD5 + MyD7 + MyD4 + MyD3);
	W_Points.push_back(MyW1);

	// Z6
	Z_Points.push_back(MyD1);
	W_Points.push_back(MyW1);

	for (int j = 0; j < 6; j++)
	{
		int NumOfIncrement = ceil(Z_Points[j+1] - Z_Points[j]) / MyDesiredFiberIncrement;
		double Increment = (Z_Points[j+1] - Z_Points[j]) / NumOfIncrement;

		for (int i = 0; i < NumOfIncrement; i++)
		{
			// Set the x coordinate.
			double x = 0.0;

			// Set the y coordinate.
			double y = Increment * 1 / 2 + Increment * i + Z_Points[j];

			// Set the fiber width;
			double width;
			
			// Check to see if it is the same width.
			if (Z_Points[j + 1] == Z_Points[j])
			{
				width = W_Points[j];
			}
			else
			{
				width = W_Points[j] + (W_Points[j + 1] - W_Points[j]) * (y - Z_Points[j]) / (Z_Points[j + 1] - Z_Points[j]);
			};
			

			// Set the fiber thickness.
			double thickness = Increment;

			// Create New Fiber.
			MyConcreteFibers.push_back(ConcreteFiber2D(ID_Counter, 
													   MyConcreteMaterial, 
													   x, 
													   y, 
													   width, 
													   thickness));

			// Increment the ID.
			ID_Counter++;
		};
	};

};

///<summary></summary>
///<param name="Material"></param>
///<remarks>description</remarks>
void GirderSection2D::AddRebarMaterial(RebarMaterial2D Material)
{
	MyRebarMaterials.push_back(Material);
};

void GirderSection2D::AddRebarMaterial(RebarMaterial2D *Material)
{
	MyRebarMaterials.push_back(*Material);
};

///<summary>Add to the rebar arrays.</summary>
///<param name="Fiber"></param>
///<remarks>description</remarks>
void GirderSection2D::AddRebar(RebarFiber2D Fiber)
{
	int Index = this -> GetRebarIndex(Fiber.GetMaterialID());

	if (Index > -1)
	{
		// Store the strand fiber.
		MyRebarFibers.push_back(Fiber);

		// Set the Material Card.
		MyRebarFibers[MyRebarFibers.size() - 1].SetMaterial(MyRebarMaterials[Index]);
	};
};

void GirderSection2D::AddRebar(RebarFiber2D *Fiber)
{
	this -> AddRebar(*Fiber);
};

///<summary></summary>
///<param name="ID"></param>
///<returns>description</returns>
///<remarks>description</remarks>
int GirderSection2D::GetRebarIndex(int ID)
{
	int Index = -1;

	for (size_t i = 0; i < MyRebarMaterials.size(); i++)
	{
		// Check to see if the material is used.
		if (ID == MyRebarMaterials[i].GetID())
		{
			// Store the Index.
			Index = i;
		};
	};

	return Index;
};

///<summary>Add the prestressing strand material.</summary>
///<param name="Material"></param>
///<remarks>description</remarks>
void GirderSection2D::AddStrandMaterial(PrestressStrandMaterial2D Material)
{
	MyPrestressStrandsMaterials.push_back(Material);
};

void GirderSection2D::AddStrandMaterial(PrestressStrandMaterial2D *Material)
{
	// dereference the pointer to store
	MyPrestressStrandsMaterials.push_back(*Material);
};

///<summary>Add the strand to the vector.</summary>
///<param name="Fiber"></param>
///<remarks>description</remarks>
void GirderSection2D::AddStrand(StrandFiber2D Fiber)
{
	int Index = this -> GetStrandIndex(Fiber.GetMaterialID());

	if (Index > -1)
	{
		// Store the strand fiber.
		MyStrandFibers.push_back(Fiber);

		// Set the Material Card.
		MyStrandFibers[MyStrandFibers.size() - 1].SetMaterial(MyPrestressStrandsMaterials[Index]);
	};
};

void GirderSection2D::AddStrand(StrandFiber2D *Fiber)
{
	this -> AddStrand(*Fiber);
};

///<summary></summary>
///<param name="ID"></param>
///<returns>description</returns>
///<remarks>description</remarks>
int GirderSection2D::GetStrandIndex(int ID)
{
	int Index = -1;

	for (size_t i = 0; i < MyPrestressStrandsMaterials.size(); i++)
	{
		// Check to see if the material is used.
		if (ID == MyPrestressStrandsMaterials[i].GetID())
		{
			// Store the Index.
			Index = i;
		};
	};

	return Index;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
void GirderSection2D::CalculateCentroid()
{
	// Calculate the X-Centroid.
	// Sum (x * Area) / Sum(Area)
	double x_numerator = 0.0;
	double x_denominator = 0.0;

	// Calculate the Y-Centroid.
	// Sum (y * Area) / Sum(Area0)
	double y_numerator = 0.0;
	double y_denominator = 0.0;

	for (size_t i = 0; i < MyConcreteFibers.size(); i++)
	{
		double x = MyConcreteFibers[i].GetX();
		double y = MyConcreteFibers[i].GetY();
		double area = MyConcreteFibers[i].GetArea();

		x_numerator += x * area;
		x_denominator += area;

		y_numerator += y * area;
		y_denominator += area;
	};
	
	MyCentroidX = x_numerator / x_denominator;
	MyCentroidY = y_numerator / y_denominator;
};

///<summary>Calculate the area of the girder.</summary>
///<remarks>description</remarks>
void GirderSection2D::CalculateArea()
{
	double Area = 0.0;

	for (size_t i = 0; i < MyConcreteFibers.size(); i++)
	{
		Area += MyConcreteFibers[i].GetArea();
	};

	// Stre the Area.
	MyArea = Area;
};

///<summary>Calculate the Moment of Inertia of the Girder.</summary>
///<remarks>description</remarks>
void GirderSection2D::CalculateInertia()
{
	MyInertiaX = 0.0;
	MyInertiaY = 0.0;

	for (size_t i = 0; i < MyConcreteFibers.size(); i++)
	{
		double x = MyConcreteFibers[i].GetX();
		double y = MyConcreteFibers[i].GetY();
		
		double area = MyConcreteFibers[i].GetArea();

		double inertiaX = MyConcreteFibers[i].GetInertiaX();
		double inertiaY = MyConcreteFibers[i].GetInertiaY();

		// I = Io + Ad^2
		MyInertiaX += inertiaX + area * pow(y - MyCentroidY, 2);
		MyInertiaY += inertiaY + area * pow(x - MyCentroidX, 2);
	};
};

///<summary></summary>
///<remarks></remarks>
void GirderSection2D::CalculateFullMomentCurvatureX()
{

};

///<summary>Calculate the full moment curvature for the Y direction away from the X-Axis.</summary>
///<remarks>description</remarks>
void GirderSection2D::CalculateFullMomentCurvatureY()
{
	MyPositiveCurvatureY = this -> GetCurvatureVectorY(+25e-7, 400);
	MyNegativeCurvatureY = this -> GetCurvatureVectorY(-25e-7, 400);
};

///<summary>Find the curvature vector Y.</summary>
///<param name="CurvatureIncrement"></param>
///<param name="MaxCurvatureCounter"></param>
///<remarks></remarks>
vector <vector<double>> GirderSection2D::GetCurvatureVectorY(double CurvatureIncrement,
															 int MaxCurvatureCounter)
{
	// Set the return vector.
	vector <vector<double>> CurvatureVectors;

	/*
			Curvature
				|******
				|***
				|*
			   *|________ Centroid
			 ***|
		  ******|
		********|
	*/
	
	double Curvature = 0.0;
	
	int CurvatureCounter = 0;

	bool GirderFailure = false;

	// Enter the global loop to find the moment curvature.
	while (!GirderFailure)
	{
		// Loop through varying the strain at the centroid to balance the force
		// in the system.  Afterwards, it is possible to calculate the resistance moment
		// of the curvature.

		// Strain = Strain.At.Centroid - Curvature * (Y - Y.Centroid)
		bool AxialForceConverge = false;

				// Strain at Centroid.
		double StrainAtCentroid;

		if (CurvatureCounter == 0)
		{
			// Start from 0.0.
			StrainAtCentroid = 0.0;
		}
		else
		{
			// Store the strain of the centroid from the previous an increment from there.
			StrainAtCentroid = CurvatureVectors[CurvatureCounter - 1][1];
		};

		// Determine the direction the strain should be incremented.
		double DirectionFactor = this -> GetStrainDirection(this -> GetForce(Curvature, StrainAtCentroid + 0.00001),
															this -> GetForce(Curvature, StrainAtCentroid),
															this -> GetForce(Curvature, StrainAtCentroid - 0.00001));
		
		double StrainIncrement = DirectionFactor * 0.001;

		int LoopCounter = 0;
	
		// Load Converges.
		while(!AxialForceConverge)
		{
			// Find the Sum of the forces at this strain.
			double SumOfForces = this -> GetForce(Curvature, StrainAtCentroid);

			// Increment the Loop Counter
			LoopCounter++;

			// Check to see if the force is less then the tolerance.
			if (abs(SumOfForces) < MyForceTolerance || LoopCounter > 20)
			{
				// Exit the Loop and stor the values.
				AxialForceConverge = true;

				// Add to Array.
				vector <double> MomentCurvatureVector;

				MomentCurvatureVector.push_back(Curvature);
				MomentCurvatureVector.push_back(StrainAtCentroid);
				MomentCurvatureVector.push_back(SumOfForces);

				// The moment is reverse because the moment calculated is forces exerted on the fiber, but not what is exerted into the section.
				MomentCurvatureVector.push_back(this -> GetMoment(Curvature, StrainAtCentroid) * -1);

				// Save the vector.
				CurvatureVectors.push_back(MomentCurvatureVector);
			}
			else
			{
				// Store the Previous Sum Of Force.
				StrainIncrement = this -> GetNextStrainIncrement(Curvature, 
															     StrainAtCentroid, 
																 StrainIncrement);
				// Change the Next Strain.
				StrainAtCentroid += StrainIncrement;
			};
		};

		// Get the curvature increment.
		//CurvatureIncrement = this -> GetCurvatureIncrement(Curvature);

		// Get the next incremnt.		
		Curvature += CurvatureIncrement; 

		// Increase the curvature.
		CurvatureCounter++;

		if (CurvatureCounter > MaxCurvatureCounter)
		{
			GirderFailure = true;
		};
	};

	// Return the Vector.
	return CurvatureVectors;
};

///<summary></summary>
///<param name="PositiveStrainForce"></param>
///<param name="NeutralStrainForce"></param>
///<param name="NegativeStrainForce"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetStrainDirection(double PositiveStrainForce,
										   double NeutralStrainForce,
										   double NegativeStrainForce)
{
	double Direction = 0.0;

	bool IsPositiveStrainPositiveForce = PositiveStrainForce >= 0.0;
	bool IsNeutralStrainPositiveForce = NeutralStrainForce >= 0.0;
	bool IsNegativeStainPositiveForce = NegativeStrainForce >= 0.0;

	if (IsPositiveStrainPositiveForce == true && 
		IsNeutralStrainPositiveForce == true && 
		IsNegativeStainPositiveForce == true)
	{
		// All the force is positive, meaning that the smallest value is the direction.
		if (PositiveStrainForce <= NegativeStrainForce)
		{
			Direction = +1.0;
		}
		else
		{
			Direction = -1.0;
		}
	}
	else if (IsPositiveStrainPositiveForce == false && 
		     IsNeutralStrainPositiveForce == false && 
		     IsNegativeStainPositiveForce == false)
	{
		// All the force is negative, meaning that the largest values is the direction.
		if (PositiveStrainForce >= NegativeStrainForce)
		{
			Direction = +1.0;
		}
		else
		{
			Direction = -1.0;
		}
	}
	else
	{
		// Need to check which of the two section changed signs.
		if (IsPositiveStrainPositiveForce == IsNeutralStrainPositiveForce)
		{
			Direction = -1.0;
		}
		else
		{
			Direction = +1.0;
		};
	};

	return Direction;
};

///<summary></summary>
///<param name="Curvature"></param>
///<param name="Strain"></param>
///<param name="StrainIncrement"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetNextStrainIncrement(double Curvature, 
											   double Strain,
											   double StrainIncrement)
{
	// Declare return variable.
	double Increment = 0.0;

	// Get the force at the strain.
	double ForceAtStrain = this -> GetForce(Curvature, Strain);

	// Is the force positive.
	bool IsForceAtStrainPositive = ForceAtStrain >= 0.0;

	// Declare teh next strain increment.
	double NewStrainIncrement = StrainIncrement;

	// Declare the loop counter.
	bool ContinueLoop = true;

	// Go into the loop to find when the strain stays positive. 
	while(ContinueLoop)
	{
		// Get the force at the guess strain concdition.
		double ForceAtNextStrain = this -> GetForce(Curvature, Strain + NewStrainIncrement);

		// Check to see if it positive.
		bool IsForceAtNextStrainPositive = ForceAtNextStrain >= 0.0;

		if (IsForceAtStrainPositive == IsForceAtNextStrainPositive)
		{
			// If the signs are the same for both strains, then this increment is good.
			// Use this Increment.
			Increment = NewStrainIncrement;

			// Exit Loop.
			ContinueLoop = false;
		}
		else
		{
			// Else, we half the guess and check to see if it valid.
			// Change the New Strain Increment.
			NewStrainIncrement = NewStrainIncrement / 2;
		};
	};
	
	return Increment;
};

///<summary>Return the curvature increment.</summary>
///<param name="Curvature"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetCurvatureIncrement(double Curvature)
{
	double CurvatureIncrement = 0.0;

	// TODO: Temporarily remove the choice.
	if (false)
	{
	// Change the curvature increment changes.
	if (abs(Curvature) <= 0.00001) 
	{ 
		CurvatureIncrement = (25e-7); 
	}
	else if (abs(Curvature) <= 0.0001)
	{ 
		CurvatureIncrement = (25e-6); 
	}
	else if (abs(Curvature) <= 0.001)
	{ 
		CurvatureIncrement = (25e-5); 
	}
	else 
	{ 
		CurvatureIncrement = (25e-4); 
	};
	}
	
	CurvatureIncrement = 25e-7;

	return CurvatureIncrement;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetForce(double Curvature,
								 double StrainAtCentroid)
{
	// Sum of all the forces.
	double SumOfForces = 0.0;

	// Add the Force Fibers.
	for (size_t j = 0; j < MyForceFibers.size(); j++)
	{
		// Add force fibers.
		SumOfForces += MyForceFibers[j].GetMagnitude();
	};

	// Add the Conrete Fibers.
	for (size_t k = 0; k < MyConcreteFibers.size(); k++)
	{
		// Get the Y position of the fiber.
		double Y = MyConcreteFibers[k].GetY();

		// Find the strain.
		double strain = StrainAtCentroid - Curvature * (Y - MyCentroidY);

		// Add the force to the system.
		SumOfForces += MyConcreteFibers[k].GetForce(strain, Curvature);
	};

	// Add the Rebar Fibers.
	for (size_t l = 0; l < MyRebarFibers.size(); l++)
	{				
		// Get the Y position of the fiber.
		double Y = MyRebarFibers[l].GetY();

		// Find the strain.
		double strain = StrainAtCentroid - Curvature * (Y - MyCentroidY);

		// Add the force to the system.
		SumOfForces += MyRebarFibers[l].GetForce(strain);
	};

	// Add the Strand Fibers.
	for (size_t m = 0; m < MyStrandFibers.size(); m++)
	{
		// Get the Y position of the fiber.
		double Y = MyStrandFibers[m].GetY();

		// Find the strain.
		double strain = StrainAtCentroid - Curvature * (Y - MyCentroidY);

		// Add the force to the system.
		SumOfForces += MyStrandFibers[m].GetForce(strain);
	};

	return SumOfForces;
};

///<summary></summary>
///<param name="Curvature"></param>
///<param name="StrainCentroid"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetMoment(double Curvature,
								  double StrainAtCentroid)
{
	// Loop through varying the strain at the centroid to balance the force
	// in the system.  Afterwards, it is possible to calculate the resistance moment
	// of the curvature.

	double SumOfMoment = 0;

	// Add the Force Fibers.
	for (size_t j = 0; j < MyForceFibers.size(); j++)
	{
		// Get the Y position of the fiber.
		double Y = MyForceFibers[j].GetY();

		// Add force fibers.
		SumOfMoment += MyForceFibers[j].GetMagnitude();
	};

	// Add the Conrete Fibers.
	for (size_t k = 0; k < MyConcreteFibers.size(); k++)
	{
		// Get the Y position of the fiber.
		double Y = MyConcreteFibers[k].GetY();

		// Find the strain.
		double strain = StrainAtCentroid - Curvature * (Y - MyCentroidY);

		// Add the force to the system.
		SumOfMoment += MyConcreteFibers[k].GetForce(strain, Curvature) * (Y - MyCentroidY);
	};

	// Add the Rebar Fibers.
	for (size_t l = 0; l < MyRebarFibers.size(); l++)
	{
		// Get the Y position of the fiber.
		double Y = MyRebarFibers[l].GetY();

		// Find the strain.
		double strain = StrainAtCentroid - Curvature * (Y - MyCentroidY);

		// Add the force to the system.
		SumOfMoment += MyRebarFibers[l].GetForce(strain) * (Y - MyCentroidY);
	};

	// Add the Strand Fibers.
	for (size_t m = 0; m < MyStrandFibers.size(); m++)
	{
		// Get the Y position of the fiber.
		double Y = MyStrandFibers[m].GetY();

		// Find the strain.
		double strain = StrainAtCentroid - Curvature * (Y - MyCentroidY);

		// Add the force to the system.
		SumOfMoment += MyStrandFibers[m].GetForce(strain) * (Y - MyCentroidY);
	};

	return SumOfMoment;
};

///<summary>Return the Bi-Linear Section of the Girder to the program after calculation.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
Section2D GirderSection2D::GetBiLinearSection()
{
	Section2D BiLinearSection = Section2D(1, 
										  MyArea,
										  MyInertiaX,
										  this -> GetInitialMoment(),
										  this -> GetBiLinearSectionPoints(MyPositiveCurvatureY),
										  this -> GetBiLinearSectionPoints(MyNegativeCurvatureY),
										  this -> GetMassDensity());

	return BiLinearSection;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
vector <vector<double>> GirderSection2D::GetBiLinearSectionPoints(vector <vector<double>> Curvature)
{
	vector <vector<double>>  Points;
	
	// Inital Curvature.
	vector <double> InitialCurvature;
	// Store Curvature.
	InitialCurvature.push_back(Curvature[0][0]);
	// Store Moment Capacity.
	InitialCurvature.push_back(Curvature[0][3]);

	// Store the first points where there is zero curvature.
	vector <double> ZeroCurvatureY = InitialCurvature;
	// Store the yield coordinates.
	vector <double> YieldCurvature = InitialCurvature;
	// Store the last coordinates.
	vector <double> UltimateCurvature = InitialCurvature;

	// Get the size of the curvature.
	size_t MaxPointsInCurvature = Curvature.size();
	
	// Counter to exit loop early.
	int StayInLoopCounter = 0;
	bool StayInLoop = true;
	bool FindYieldPoint = true;

	// Find the initial moment.
	double InitialMoment = Curvature[0][3];

	// Find the initial stiffness.
	double InitialStiffness = (Curvature[1][3] - Curvature[0][3]) 
							   / (Curvature[1][0] - Curvature[0][0]);

	// Start at the 2nd Increment.
	size_t LoopCounter = 2;

	while (LoopCounter < MaxPointsInCurvature && StayInLoop)
	{
		// Instantaneous Stiffness.
		double IncrementStiffness = (Curvature[LoopCounter][3] - Curvature[LoopCounter - 1][3]) 
							        / (Curvature[LoopCounter][0] - Curvature[LoopCounter - 1][0]); 

		// Stay In Loop
		// Check to see if the instantaneous stiffness changed more than desired from the increment stifffness.
		if (this -> IsSectionYielding(Curvature[LoopCounter][0], Curvature[LoopCounter][1]) && FindYieldPoint)
		{
			vector <double> CurvaturePoint;

			// Save the data.
			CurvaturePoint.push_back(Curvature[LoopCounter][0]);
			CurvaturePoint.push_back(Curvature[LoopCounter][3]);

			// Store the curvature Point.
			YieldCurvature = CurvaturePoint;

			// Tell it not to enter.
			FindYieldPoint = false;
		}
		else if(abs(IncrementStiffness) <= abs(InitialStiffness) && FindYieldPoint)
		{
			vector <double> CurvaturePoint;

			// Save the data.
			CurvaturePoint.push_back(Curvature[LoopCounter][0]);
			CurvaturePoint.push_back(Curvature[LoopCounter][3]);

			// Store the curvature Point.
			YieldCurvature = CurvaturePoint;
		};

		// Check to see if the strain has reached it's maximum capacity.
		if (this -> IsSectionAtMaximumCapacity(Curvature[LoopCounter][0], Curvature[LoopCounter][1]))
		{
			// Store the point because it's the larget.
			// Save the data.
			vector <double> CurvaturePoint;

			CurvaturePoint.push_back(Curvature[LoopCounter - 1][0]);
			CurvaturePoint.push_back(Curvature[LoopCounter - 1][3]);

			// Store the curvature point.
			UltimateCurvature = CurvaturePoint;

			// Exit the loop because the strength decreased. 
			StayInLoop = false;

		}
		else
		{
			// Increment Stay in Loop Counter
			StayInLoopCounter++;
		};

		// Increment the Counter.
		LoopCounter++;
	};

	// Store into counter.
	Points.push_back(ZeroCurvatureY);
	Points.push_back(YieldCurvature);
	Points.push_back(UltimateCurvature);

	return Points;
};

///<summary>Get linear sections of th coodinates.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
vector <vector<double>> GirderSection2D::GetLinearSectionPoints(vector <vector<double>> Curvature)
{
	vector <vector<double>>  Points;
	
	// Inital Curvature.
	vector <double> InitialCurvature;
	// Store Curvature.
	InitialCurvature.push_back(Curvature[0][0]);
	// Store Moment Capacity.
	InitialCurvature.push_back(Curvature[0][3]);

	// Store the first points where there is zero curvature.
	vector <double> ZeroCurvatureY = InitialCurvature;
	// Store the last coordinates.
	vector <double> UltimateCurvature = InitialCurvature;

	// Get the size of the curvature.
	size_t MaxPointsInCurvature = Curvature.size();
	
	// Counter to exit loop early.
	int StayInLoopCounter = 0;
	bool StayInLoop = true;
	bool FindYieldPoint = true;

	// Find the initial moment.
	double InitialMoment = Curvature[0][3];

	// Start at the 2nd Increment.
	size_t LoopCounter = 1;

	while (LoopCounter < MaxPointsInCurvature)
	{
		// Looping to find the maximum capacity of the section.
		if (abs(UltimateCurvature[1]) < abs(Curvature[LoopCounter][3] - InitialCurvature[1]))
		{
			// Store the curvature and nominal moment capacity because it's now the largest.
			vector <double> CurvaturePoint;

			// Save the data.
			CurvaturePoint.push_back(Curvature[LoopCounter][0]);
			CurvaturePoint.push_back(Curvature[LoopCounter][3]);

			// Store the curvature Point.
			UltimateCurvature = CurvaturePoint;
		};

		// Increment the Counter.
		LoopCounter++;
	};

	// Store into counter.
	Points.push_back(ZeroCurvatureY);
	Points.push_back(UltimateCurvature);
	Points.push_back(UltimateCurvature);

	return Points;
};

///<summary>Find out if any of the part of the girder section is yielding.</summary>
///<param name="Curvature">Find the curvature of the section.</param>
///<param name="StrainAtCentroid">Find the strain at centroid.</param>
///<returns>description</returns>
///<remarks>description</remarks>
bool GirderSection2D::IsSectionYielding(double Curvature, 
										double StrainAtCentroid)
{
	bool IsYielding = false;

	// Check the Bottom fiber.
	int BottomFiberIndex = 0;
	
	// Get the Strain at the Bottom Fiber.
	double StrainAtBottomFiber = StrainAtCentroid - Curvature * (MyCentroidY - MyConcreteFibers[BottomFiberIndex].GetY());

	// See the fiber is the yielding.
	if (MyConcreteFibers[BottomFiberIndex].IsStrainAtYield(StrainAtBottomFiber))
	{
		IsYielding = true;
	};

	// Check the Top fiber.
	int TopFiberIndex = MyConcreteFibers.size() - 1;

	// Find the strain at the top fiber.
	double StrainAtTopFiber = StrainAtCentroid - Curvature * (MyCentroidY - MyConcreteFibers[TopFiberIndex].GetY());

	// Check the concrete fiber 
	if (MyConcreteFibers[TopFiberIndex].IsStrainAtYield(StrainAtTopFiber))
	{
		IsYielding = true;
	};

	// Check all the Rebar.
	for (size_t i = 0; i < MyRebarFibers.size(); i++)
	{
		double StrainAtRebar = StrainAtCentroid - Curvature * (MyCentroidY - MyRebarFibers[i].GetY());

		// Is the Strain Yielding.
		if (MyRebarFibers[i].IsStrainAtYield(StrainAtRebar))
		{
			IsYielding = true;
		};
	};

	// Check all the Strand.
	for (size_t j = 0; j < MyStrandFibers.size(); j++)
	{
		double StrainAtStrand = StrainAtCentroid - Curvature * (MyCentroidY - MyStrandFibers[j].GetY());

		// Is the Strain Yielding.
		if (MyStrandFibers[j].IsStrainAtYield(StrainAtStrand))
		{
			IsYielding = true;
		};
	};

	return IsYielding;
};

///<summary>Find out if the top and bottom fiber is at maximum strain, 
/// or if the strand snap through it's capacity, or if the 
/// mild steel reinforcemnt has past ultimate strain.</summary>
///<param name="Curvature">Find the curvature of the section.</param>
///<param name="StrainAtCentroid">Find the strain at centroid.</param>
///<returns>description</returns>
///<remarks>description</remarks>
bool GirderSection2D::IsSectionAtMaximumCapacity(double Curvature, 
												 double StrainAtCentroid)
{
	bool IsAtMaximum = false;

	// Check the Bottom fiber.
	int BottomFiberIndex = 0;
	
	// Get the Strain at the Bottom Fiber.
	double StrainAtBottomFiber = StrainAtCentroid - Curvature * (MyCentroidY - MyConcreteFibers[BottomFiberIndex].GetY());

	// See the fiber is at maximum strain.
	if (MyConcreteFibers[BottomFiberIndex].IsStrainAtMaximum(StrainAtBottomFiber))
	{
		IsAtMaximum = true;
	};

	// Check the Top fiber.
	int TopFiberIndex = MyConcreteFibers.size() - 1;

	// Find the strain at the top fiber.
	double StrainAtTopFiber = StrainAtCentroid - Curvature * (MyCentroidY - MyConcreteFibers[TopFiberIndex].GetY());

	// Check the concrete fiber 
	if (MyConcreteFibers[TopFiberIndex].IsStrainAtMaximum(StrainAtTopFiber))
	{
		IsAtMaximum = true;
	};

	// Check all the Rebar.
	for (size_t i = 0; i < MyRebarFibers.size(); i++)
	{
		double StrainAtRebar = StrainAtCentroid - Curvature * (MyCentroidY - MyRebarFibers[i].GetY());

		// Is the Strain at Maximum.
		if (MyRebarFibers[i].IsStrainAtMaximum(StrainAtRebar))
		{
			IsAtMaximum = true;
		};
	};

	// Check all the Strand.
	for (size_t j = 0; j < MyStrandFibers.size(); j++)
	{
		double StrainAtStrand = StrainAtCentroid - Curvature * (MyCentroidY - MyStrandFibers[j].GetY());

		// Is the Strain at Maximum.
		if (MyStrandFibers[j].IsStrainAtMaximum(StrainAtStrand))
		{
			IsAtMaximum = true;
		};
	};

	return IsAtMaximum;
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void GirderSection2D::SetBindingReinforcements()
{
	for (size_t i = 0; i < MyRebarFibers.size(); i++)
	{
		this -> SetBindingReinforcement(&MyRebarFibers[i],
			                            7.5 * MyRebarFibers[i].GetDiameter());
	};

	for (size_t j = 0; j < MyStrandFibers.size(); j++)
	{
		this -> SetBindingReinforcement(&MyStrandFibers[j],
			                            7.5 * MyStrandFibers[j].GetDiameter());
	};
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void GirderSection2D::SetBindingReinforcement(Fiber2D *Fiber, 
											  double EffectiveRange)
{
	double ReinforcementX = Fiber -> GetX();
	double ReinforcementY = Fiber -> GetY();

	for (size_t i = 0; i < MyConcreteFibers.size(); i++)
	{
		double ConcreteX = MyConcreteFibers[i].GetX();
		double ConcreteY = MyConcreteFibers[i].GetY();

		// Search the Y Axis.
		if (ConcreteY <= (ReinforcementY + EffectiveRange) 
			&& ConcreteY >= (ReinforcementY - EffectiveRange))
		{
			// Search to see if the X-Axis is within Range.
			if (ConcreteX <= (ReinforcementX + EffectiveRange)
				&& ConcreteX >= (ReinforcementX - EffectiveRange))
			{
				// Add the Reinforcement Pointer.
				MyConcreteFibers[i].AddBindingReinforcement(Fiber);
			};
		};
	};
};

///<summary></summary>
///<param name="DesiredIncrement"></param>
///<remarks>description</remarks>
void GirderSection2D::SetDesiredFiberIncrement(double DesiredIncrement)
{
	MyDesiredFiberIncrement = DesiredIncrement;
};

///<summary>Return the Density.</summary>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetMassDensity()
{
	double MassPerLength = 0.0;
	double Area = 0.0;

	// Set the Concrete.
	for (size_t i = 0; i < MyConcreteFibers.size(); i++)
	{
		// Add to Area.
		Area += MyConcreteFibers[i].GetArea();

		// Add to Ratio.
		MassPerLength += MyConcreteFibers[i].GetArea() * MyConcreteFibers[i].GetDensity();
	};

	// Set the Rebar.
	for (size_t j = 0; j < MyRebarFibers.size(); j++)
	{
		// Add to Area.
		Area += MyRebarFibers[j].GetArea();

		// Add to Ratio.
		MassPerLength += MyRebarFibers[j].GetArea() * MyRebarFibers[j].GetDensity();
	};

	// Set the Strand.
	for (size_t k = 0; k < MyStrandFibers.size(); k++)
	{
		// Add to Area.
		Area += MyStrandFibers[k].GetArea();

		// Add to Ratio.
		MassPerLength += MyStrandFibers[k].GetArea() * MyStrandFibers[k].GetDensity();
	};

	return MassPerLength / Area;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetInitialForce()
{
	double InitialForce = 0.0;

	for (size_t i = 0; i < MyStrandFibers.size(); i++)
	{
		// Strand force is always negative at initial loading.
		InitialForce -= MyStrandFibers[i].GetForce(0.0);
	};

	return InitialForce;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double GirderSection2D::GetInitialMoment()
{
	double InitialMoment = 0.0;

	for (size_t i = 0; i < MyStrandFibers.size(); i++)
	{
		// Strand Force is always negative at initial loading.
		double Force = -MyStrandFibers[i].GetForce(0.0);

		// Get the strand centroid Y.
		double StrandCentroidY = MyStrandFibers[i].GetY();

		// Set the initial moment.
		InitialMoment += (MyCentroidY - StrandCentroidY) * Force;
	};

	/// TODO: Look at the force fiber.
	for (size_t j = 0; j < MyForceFibers.size(); j++)
	{
		
	};

	return InitialMoment;
};

double GirderSection2D::GetTopFlangeWidth()
{
	return MyW1;
};

double GirderSection2D::GetBottomFlangeWidth()
{
	return MyW2;
};

double GirderSection2D::GetDepth()
{
	return MyD1;
};