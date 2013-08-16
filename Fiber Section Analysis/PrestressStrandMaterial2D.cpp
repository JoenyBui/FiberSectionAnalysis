#include "StdAfx.h"
#include "PrestressStrandMaterial2D.h"

void PrestressStrandMaterial2D::Initialize(int ID = -1,
										   string TypeOfStrand = "Custom Strand",
										   double Density = 1.0,
										   double TensionElasticModulus = 0.0,
								 		   double TensionYieldStress = 0.0,
								 		   double TensionYieldStrain = 0.0,
								 		   double TensionUltimateStress = 0.0,
								 		   double TensionUltimateStrain = 0.0,
								 		   double PowerConstantA = 0.0,
								 		   double PowerConstantB = 0.0,
								 		   double PowerConstantC = 0.0,
								 		   double PowerConstantD = 0.0,
								 		   double TensionInitialStrain = 0.0,
								 		   double DIF_Yield = 0.0,
								 		   double DIF_Ultimate = 0.0)
{
	// Set the ID.
	MyID = ID;

	// Store the Density.
	MyMassDensity = Density;

	// Set the Type of Strand.
	MyTypeOfStrand = TypeOfStrand;

	// Set the Power Law Constants.
	MyTensionElasticModulus =  TensionElasticModulus;
	MyTensionYieldStress=  TensionYieldStress;
	MyTensionYieldStrain=  TensionYieldStrain;
	MyTensionUltimateStress=  TensionUltimateStress;
	MyTensionUltimateStrain=  TensionUltimateStrain;

	MyPowerConstantA =  PowerConstantA;
	MyPowerConstantB =  PowerConstantB;
	MyPowerConstantC =  PowerConstantC;
	MyPowerConstantD =  PowerConstantD;

	// Store the Tension InitialStrain.
	MyTensionInitialStrain = TensionInitialStrain;

	// Store the DIF_Yield.
	IncludeDIF = false;
	MyYieldDIF = DIF_Yield;
	MyUltimateDIF = DIF_Ultimate;
};

void PrestressStrandMaterial2D::Clone(const PrestressStrandMaterial2D &Material)
{
	MyID = Material.MyID;

	MyMassDensity = Material.MyMassDensity;

	IncludeDIF = Material.IncludeDIF;
	MyYieldDIF = Material.MyYieldDIF;
	MyUltimateDIF = Material.MyUltimateDIF;

	IncludeSIF = Material.IncludeSIF;
	MyYieldSIF = Material.MyYieldSIF;
	MyUltimateSIF = Material.MyYieldSIF;

	MyTypeOfStrand = Material.MyTypeOfStrand;

	MyTensionInitialStrain = Material.MyTensionInitialStrain;

	MyTensionElasticModulus = Material.MyTensionElasticModulus;
	MyTensionYieldStress = Material.MyTensionYieldStress;
	MyTensionYieldStrain = Material.MyTensionYieldStrain;
	MyTensionUltimateStress = Material.MyTensionUltimateStress;
	MyTensionUltimateStrain = Material.MyTensionUltimateStrain;

	MyPowerConstantA = Material.MyPowerConstantA;
	MyPowerConstantB = Material.MyPowerConstantB;
	MyPowerConstantC = Material.MyPowerConstantC;
	MyPowerConstantD = Material.MyPowerConstantD;
};

PrestressStrandMaterial2D::PrestressStrandMaterial2D(int ID, 
													 int TypeOfStrand, 
													 double Density,
													 double InitialStrain)
{
	// Set the ID.
	MyID = ID;

	// Set the Type of Prestressing.
	this -> SetPowerLawConstants(TypeOfStrand);

	// Set the Density.
	MyMassDensity = Density;

	// Set the Initial Strain.
	MyTensionInitialStrain = InitialStrain;
};

PrestressStrandMaterial2D::PrestressStrandMaterial2D(void)
{
};

PrestressStrandMaterial2D::~PrestressStrandMaterial2D(void)
{
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
PrestressStrandMaterial2D& PrestressStrandMaterial2D::operator =(const PrestressStrandMaterial2D &Material)
{
	this -> Clone(Material);

	return *this;
};

///<summary>Set the Power Law Prestressing Constant for the material.</summary>
///<param name="Type"></param>
///<returns>description</returns>
///<remarks>See Devalapura and Tadros, "Stress-Strain Mdeling of 270 ksi Low-Relaxation Prestressing Strands." for
/// more information of the data.  See Naaman, "Prestressed Concrete Analaysis and Design." for strain values.</remarks>
void PrestressStrandMaterial2D::SetPowerLawConstants(int Type)
{
	switch (Type)
	{
		case (Type270ksiStrand)  :    
			MyTypeOfStrand = "270 ksi strand";

            MyPowerConstantA = 887.0;
            MyPowerConstantB = 27613.0;
            MyPowerConstantC = 112.4;
            MyPowerConstantD = 7.360;

			MyTensionElasticModulus = 28500000;

			MyTensionUltimateStress = 270000.0;
			MyTensionUltimateStrain = 0.050;

			MyTensionYieldStress = 0.90 * MyTensionUltimateStress;
			MyTensionYieldStrain = 0.010;
			

			break;

		case (Type250ksiStrand)   :   
			MyTypeOfStrand = "250 ksi strand";

            MyPowerConstantA = 384.0;
            MyPowerConstantB = 27616.0;
            MyPowerConstantC = 119.7;
            MyPowerConstantD = 6.430;

			MyTensionElasticModulus = 28500000;

			MyTensionUltimateStress = 250000;
			MyTensionUltimateStrain = 0.050;

			MyTensionYieldStress = 0.90 * MyTensionUltimateStress;
			MyTensionYieldStrain = 0.010;

			break;

		case (Type250ksiWire)   :   
			MyTypeOfStrand = "250 ksi wire";

            MyPowerConstantA = 435.0;
            MyPowerConstantB = 28565.0;
            MyPowerConstantC = 125.1;
            MyPowerConstantD = 6.351;

			MyTensionElasticModulus = 28500000;

			MyTensionUltimateStress = 250000;
			MyTensionUltimateStrain = 0.050;

			MyTensionYieldStress = 0.90 * MyTensionUltimateStress;
			MyTensionYieldStrain = 0.010;

			break;

		case (Type235ksiWire)   :  
			MyTypeOfStrand = "235 ksi wire";

            MyPowerConstantA = 403.0;
            MyPowerConstantB = 28597.0;
            MyPowerConstantC = 133.1;
			MyPowerConstantD = 5.463;

			MyTensionElasticModulus = 28500000;

			MyTensionUltimateStress = 235000;
			MyTensionUltimateStrain = 0.050;

			MyTensionYieldStress = 0.90 * MyTensionUltimateStress;
			MyTensionYieldStrain = 0.010;

			break;

		case (Type150ksiBar):
			MyTypeOfStrand = "150 ksi bar";

            MyPowerConstantA = 467.0;
            MyPowerConstantB = 28533.0;
            MyPowerConstantC = 225.2;
            MyPowerConstantD = 4.991;

			MyTensionElasticModulus = 28500000;

			MyTensionUltimateStress = 150000;
			MyTensionUltimateStrain = 0.050;

			MyTensionYieldStress = 0.85 * MyTensionUltimateStress;
			MyTensionYieldStrain = 0.0070;

			break;

		default:
			MyTypeOfStrand = "No Strand Selected";

            MyPowerConstantA = 0.0;
            MyPowerConstantB = 0.0;
            MyPowerConstantC = 0.0;
            MyPowerConstantD = 0.0;

			MyTensionElasticModulus = 0.0;

			MyTensionUltimateStress = 0.0;
			MyTensionUltimateStrain = 0.0;

			MyTensionYieldStress = 0.90 * MyTensionUltimateStress;
			MyTensionYieldStrain = 0.0;
			break;
	};
	
};

///<summary>Return the stress given the strain in the member.</summary>
///<param name="Strain">'+' strain is tension :: '-' strain is compression.</param>
///<remarks>description</remarks>
double PrestressStrandMaterial2D::GetStress(double Strain)
{
	// Initialize return variable.
	double Stress = 0.0;

	// Full Strain on the prestress.
	double epsilon = Strain + MyTensionInitialStrain;

	if (epsilon >= 0.0) 
	{
		if (epsilon > MyTensionUltimateStrain)
		{
			// Strand broke so no stress is transfered.
			Stress = 0.0;
		}
		else 
		{
			// Use the Power-Law to return the Stress.
			Stress = epsilon * (MyPowerConstantA + (MyPowerConstantB / 
				                                    pow(1 + pow(MyPowerConstantC * epsilon, MyPowerConstantD),1 / MyPowerConstantD))) * 1000;

			// Check if Stress if over maximum.
			if (Stress > MyTensionUltimateStress)
			{
				// Change to maximun stress.
				Stress = MyTensionUltimateStress;
			};
		};
	}
	else
	{
		// Strand does not react in negative tension.
		Stress = 0.0;
	};

	// Return variable.
	return +Stress;
};

///<summary></summary>
///<returns>description</returns>
///<remarks>description</remarks>
double PrestressStrandMaterial2D::GetTensionYieldStrain()
{
	return MyTensionYieldStrain;
};

double PrestressStrandMaterial2D::GetTensionFailureStrain() {
	return MyTensionUltimateStrain;
};

///<summary></summary>
///<returns>description</returns>
///<remarks>description</remarks>
double PrestressStrandMaterial2D::GetCompressionYieldStrain()
{
	return 0.0;
};

double PrestressStrandMaterial2D::GetCompressionFailureStrain() {
	return 0.0;
};

///<summary>Determine if the strain passed in has reach yielded strain.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
bool PrestressStrandMaterial2D::IsStrainAtYield(double Strain)
{
	bool IsFiberYielded = false;

	if (Strain > 0)
	{
		// Strain is '+' and in Tension
		if (MyTensionYieldStrain <= abs(Strain + MyTensionInitialStrain))
		{
			IsFiberYielded = true;
		};
	}
	else
	{
		// Strain is '-' and in Compression
		// Prestressing strands does not react in compression.
		IsFiberYielded = false;
	}

	return IsFiberYielded;
};

///<summary>Determine if the strain passed in has reach maximum allowable strain.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
bool PrestressStrandMaterial2D::IsStrainAtMaximum(double Strain)
{
	bool IsFiberAtMaximum = false;

	if (Strain > 0)
	{
		// Strain is '+' and in Tension
		// The failure tensile strain is compared with the present strain.
		if (MyTensionUltimateStrain <= abs(Strain))
		{
			IsFiberAtMaximum = true;
		};
	}
	else
	{
		// Strain is '-' and in Compression.
		// There is no compression capacity fore the prestressing strand.
		IsFiberAtMaximum = false;
	}

	return IsFiberAtMaximum;
};

///<summary></summary>
///<returns>description</returns>
///<remarks>description</remarks>
void PrestressStrandMaterial2D::Print()
{
	// State the Strain vs. Stress.
	double StrainIncrement = 0.00005;

	// Output the title.
	cout << "Strain " << "\t\t" << "Stress" << endl;

	for (int i = 0; i < 400; i++)
	{
		cout << i * StrainIncrement << "\t\t" << this -> GetStress(StrainIncrement * i - MyTensionInitialStrain) << endl;
	};
};