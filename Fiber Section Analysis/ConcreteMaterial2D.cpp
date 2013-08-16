#include "StdAfx.h"
#include "ConcreteMaterial2D.h"

///<summary></summary>
///<param name="ID">ID Parameter of the Material.</param>
///<param name="UltimateStress">Concrete ultimate stress.</param>
///<param name="FailureStrain">Concrete strain that is considered the failing strain.</param>
///<param name="YieldStrain">Concrete strain that is considered the yielding strain.</param>
///<param name="TensionStiffening">Use tension stiffening or not.</param>
///<param name="Alpha1">Tension Stiffening factor accounting for bond characteristic.</param>
///<param name="Alpha2">Tension Stiffening factor accounting for bond characteristic.</param>
///<remarks>description</remarks>
void ConcreteMaterial2D::Initialize(int ID = -1,
									double Density = 1.0,
									double UltimateStress = 0.0,
									double FailureStrain = 0.0,
									double YieldStrain = 0.0015,
									bool TensionStiffening = false,
									double Alpha1 = 1.0,
									double Alpha2 = 1.0,
									double DIF_Yield = 1.0,
									double DIF_Ultimate = 1.0)
{
	// Set the ID.
	MyID = ID;

	// Set the Density.
	MyMassDensity = Density;

	// Set the Dynamic Increase Factor.
	IncludeDIF = false;
	MyYieldDIF = DIF_Yield;
	MyUltimateDIF = DIF_Ultimate;

	// Set the Yield Strain.
	MyCompressionYieldStrain = YieldStrain;

	// Set the Ultimate Strain.
	MyCompressionUltimateStress = UltimateStress;

	// Set the failure strain.
	MyCompressionFailureStrain = FailureStrain;

	// Calculate the presume modulus from ACI Eq. 

	if (MyCompressionUltimateStress <= 6000)
	{
		// Set the Elastic Modulus.
		MyCompressionElasticModulus = 57000 * sqrt(UltimateStress);
	}
	else
	{
		// Set the Elastic Modulus for a Higher Stress
		MyCompressionElasticModulus = 40000 * sqrt(UltimateStress) + 1000000;
	};
	
	// Calculate the strain at ultimate peak.
	MyCompressionUltimateStrain = MyCompressionUltimateStress / (1.0 / 2.0 * MyCompressionElasticModulus);

	// Calculate the Thorenfeldt,Tomaszewicz, and Jensen Paramters.
	MyTTJ_CompressionCurveFittingFactor = 0.80 + MyCompressionUltimateStress / 2500;

	MyTTJ_CompressionPostPeakDecayFactor = 0.67 + MyCompressionUltimateStress / 9000;
	
	MyTTJ_CompressionUltimateStrain = MyCompressionUltimateStress / MyCompressionElasticModulus 
										* (MyTTJ_CompressionCurveFittingFactor / (MyTTJ_CompressionCurveFittingFactor - 1));

	// Calculate Concrete Tensile Stress
	MyTensionUltimateStress = 7.5 * sqrt(UltimateStress);

	// Calculate the Tension Strain.
	MyTensionUltimateStrain = 1.8 * MyTensionUltimateStress / MyCompressionElasticModulus;

	// Calculate the Modulus Of Elasticity.
	MyTensionElasticModulus = MyTensionUltimateStress / MyTensionUltimateStrain;

	// Calculate the Failure Strain.
	// Descending branch is considered a straight line.
	MyTensionFailureStrain = MyTensionUltimateStrain + MyTensionUltimateStress / (MyTensionElasticModulus / 5.0);

	// Include Tension Stiffening or not.
	IncludeTensionStiffening = TensionStiffening;

	// Factor Accounting for Bond Characteristic
	MyTS_TensionAlpha1 = Alpha1;

	// Factor Accounting for sustained or repeated loading.
	MyTS_TensionAlpha2 = Alpha2;
};

void ConcreteMaterial2D::Clone(const ConcreteMaterial2D &Material)
{
	MyID = Material.MyID;

	MyMassDensity = Material.MyMassDensity;

	IncludeDIF = Material.IncludeDIF;
	MyYieldDIF = Material.MyYieldDIF;
	MyUltimateDIF = Material.MyUltimateDIF;

	IncludeSIF = Material.IncludeSIF;
	MyYieldSIF = Material.MyYieldSIF;
	MyUltimateSIF = Material.MyYieldSIF;

	MyCompressionElasticModulus = Material.MyCompressionElasticModulus;
	MyCompressionYieldStrain = Material.MyCompressionYieldStrain;
	MyCompressionUltimateStress = Material.MyCompressionUltimateStress;
	MyCompressionUltimateStrain = Material.MyCompressionUltimateStrain;
	MyCompressionFailureStrain = Material.MyCompressionFailureStrain;

	MyTTJ_CompressionCurveFittingFactor = Material.MyTTJ_CompressionCurveFittingFactor;
	MyTTJ_CompressionPostPeakDecayFactor = Material.MyTTJ_CompressionPostPeakDecayFactor;
	MyTTJ_CompressionUltimateStrain = Material.MyTTJ_CompressionUltimateStrain;

	MyTensionElasticModulus = Material.MyTensionElasticModulus;
    MyTensionUltimateStress = Material.MyTensionUltimateStress;
    MyTensionUltimateStrain = Material.MyTensionUltimateStrain;
	MyTensionFailureStrain = Material.MyTensionFailureStrain;

	// Tension Stiffening Parameter. (See Collins and Mitchell for more information)
	MyTS_TensionAlpha1 = Material.MyTS_TensionAlpha1;
	MyTS_TensionAlpha2 = Material.MyTS_TensionAlpha2;

	IncludeTensionStiffening = Material.IncludeTensionStiffening;
};

///<summary>Constructor:</summary>
///<param name="UltimateStress"></param>
///<param name="FailureStrain"></param>
///<remarks>description</remarks>
ConcreteMaterial2D::ConcreteMaterial2D(int ID,
									   double Density,
									   double UltimateStress,
									   double FailureStrain,
									   bool TensionStiffening = false)
{
	// Initilize the component.
	this -> Initialize(MyID,
					   Density,
					   UltimateStress, 
					   FailureStrain, 
					   0.0015,
					   TensionStiffening);
};

ConcreteMaterial2D::ConcreteMaterial2D(void)
{
	this -> Initialize();
}

ConcreteMaterial2D::~ConcreteMaterial2D(void)
{
}

///<summary>Make a replica of the material.</summary>
///<param name="Material">Copy all the content of this reference variable.</param>
///<remarks>description</remarks>
ConcreteMaterial2D& ConcreteMaterial2D::operator =(const ConcreteMaterial2D &Material)
{
	this -> Clone(Material);

	return *this;
};

///<summary>Return the stress given the strain in the member.</summary>
///<param name="Strain">'+' strain is tension :: '-' strain is compression.</param>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetStress(double Strain)
{
	return this -> GetStress(Strain, false);
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetStress(double Strain,
									 bool BindingReinforcement)
{
	double Stress = 0;

	if (Strain >= 0.0)
	{
		// Tension Strain.
		Stress = this -> GetStressWithTensionStiffening(Strain, 
														BindingReinforcement);
	}
	else if (Strain < 0.0)
	{
		// Compression Strain.  Use the Hognestad Equation to compute the stress.
		// Stress = this -> GetStressWithHognestadParabola(Strain);
		Stress = this -> GetStressWithThorenfeldtParabola(Strain);

		
	}

	return Stress;
};

///<summary></summary>
///<param name="Strain">Strain of the Stress via equations fromThorenfeldt, Tomaszewicz, and Jensen
/// to represent the famiy of stress-strain curves for concreteat different strength.</param>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetStressWithThorenfeldtParabola(double Strain)
{
	// Initialize the return value.
	double Stress = 0.0;

	// Get the Absolute value of the strain.
	Strain = abs(Strain);

	double Numerator = MyTTJ_CompressionCurveFittingFactor * Strain / MyTTJ_CompressionUltimateStrain;
	double Denominator = MyTTJ_CompressionCurveFittingFactor - 1 + pow(Strain / MyTTJ_CompressionUltimateStrain,MyTTJ_CompressionCurveFittingFactor * MyTTJ_CompressionPostPeakDecayFactor);
	
	// Calculate the Stress.
	Stress = MyCompressionUltimateStress * Numerator / Denominator;
	
	if (Stress < 0.0) 
	{
		Stress = 0.0;
	};

	// Include Dynamic Increase Factor.
	if (IncludeDIF)
	{
		Stress = MyUltimateDIF * Stress;
	};

	return -Stress;
};

/*
	Tension Bi-Linear Curve - (Tension)


	^
	|             
	|            
	|           
	|                   *
	|                 *    *  *	
	|               *         *  *
	|             *              *
	|           *					*  *
	|         *							  *  *  *
	|       *							           *
	|     *									 
	|   *									    
	| *											   
	 ------------------|----------------------------|->
				 epsion_peak		          epsilon_max
*/
///<summary></summary>
///<param name="Strain"></param>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetStressWithTensionStiffening(double Strain, 
														  bool BindingReinforcement)
{
	// Initialize the return value.
	double Stress = 0.0;

	// Get the Absolute value of the strain.
	Strain = abs(Strain);

	// Find Compression Stress.
	if (Strain > MyTensionFailureStrain)
	{
		// Concrete fails at the section.
		Stress = 0.0;
	}
	else if (Strain > MyTensionUltimateStrain)
	{
		if (IncludeTensionStiffening)
		{
			if (BindingReinforcement)
			{
				// Concrete strain is in the descending branch.
				Stress = (MyTS_TensionAlpha1 * MyTS_TensionAlpha2 * (MyTensionUltimateStress)) / (1 + sqrt(500*Strain));
			};
		}
		else
		{
			// Assume at this time that the concrete fails after reaching tensile rupture.
			Stress = 0.0;
		}
	}
	else
	{
		// Concrete strain is in the ascending branch.
		Stress = MyTensionElasticModulus * Strain;
	};
	
	return +Stress;
};

/*
	Hognestad Parabolic - (Compression)

	Stress = f'c * [2 * epsilon / epsilon.o - (epsilon / epsilon.o)^2]

	^
	|             
	|            
	|           
	|                            *****
	|                        ****     ****
	|                    ****             ****
	|                ****                     ****
	|             ***
	|          ***
	|       ***
	|     **
	|   **
	| *
	 ------------------------------|--------------|--->
								epsion_peak		epsilon.max
*/
///<summary></summary>
///<param name="Strain"></param>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetStressWithHognestadParabola(double Strain)
{
	// Initialize the return value.
	double Stress = 0.0;

	// Get the Absolute value of the strain.
	Strain = abs(Strain);

	// Find Compression Stress.
	if (Strain > MyCompressionFailureStrain)
	{
		// Concrete fails at the section.
		Stress = 0.0;

		// TODO: Temporarily look into the effect of bringing out the stress-strain model for the hognestad parobala.
		// Use the hognestad equation.
		Stress = MyCompressionUltimateStress * ((2 * Strain / MyCompressionUltimateStrain) - pow((Strain / MyCompressionUltimateStrain),2));

		if (Stress < 0.0)
		{
			Stress = 0.0;
		};
	}
	else
	{
		// Use the hognestad equation.
		Stress = MyCompressionUltimateStress * ((2 * Strain / MyCompressionUltimateStrain) - pow((Strain / MyCompressionUltimateStrain),2));
	};

	return -Stress;
};




/*
	Tension Bi-Linear Curve - (Tension)


	^
	|             
	|            
	|           
	|                   *
	|                 *    *
	|               *         *
	|             *              *
	|           *					*
	|         *						   *
	|       *							  *
	|     *									 *
	|   *									    *
	| *											   *
	 ------------------|----------------------------|->
				 epsion_peak		          epsilon_max
*/
///<summary></summary>
///<param name="Strain"></param>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetStressWithTensionLinear(double Strain)
{
	// Initialize the return value.
	double Stress = 0.0;

	// Get the Absolute value of the strain.
	Strain = abs(Strain);

	// Find Compression Stress.
	if (Strain > MyTensionFailureStrain)
	{
		// Concrete fails at the section.
		Stress = 0.0;
	}
	else if (Strain > MyTensionUltimateStrain)
	{
		if (IncludeTensionStiffening)
		{
			// Concrete strain is in the descending branch.
			Stress = MyTensionUltimateStress - (MyTensionElasticModulus / 5.0) * (Strain - MyTensionUltimateStrain);
		}
		else
		{
			// Assume at this time that the concrete fails after reaching tensile rupture.
			Stress = 0.0;
		}
	}
	else
	{
		// Concrete strain is in the ascending branch.
		Stress = MyTensionElasticModulus * Strain;
	};
	
	return +Stress;
};

///<summary>Return the strain of the fiber that would designate yield failure.</summary>
///<returns>Returns zero because we do not use tension strain in concrete as a designation of yielding.  It is a brittle failure.</returns>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetTensionYieldStrain()
{
	return MyTensionUltimateStrain;
};

///<summary></summary>
///<returns>description</returns>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetTensionFailureStrain()
{
	return MyTensionFailureStrain;
};

///<summary></summary>
///<returns>description</returns>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetCompressionYieldStrain()
{
	return MyCompressionYieldStrain;
};

///<summary></summary>
///<returns>description</returns>
///<remarks>description</remarks>
double ConcreteMaterial2D::GetCompressionFailureStrain() {
	return MyCompressionFailureStrain;
};

///<summary>Determine if the strain passed in has reach yielded strain.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
bool ConcreteMaterial2D::IsStrainAtYield(double Strain)
{
	bool IsFiberYielded = false;

	if (Strain > 0)
	{
		// Strain is '+' and in Tension
		// There is no yielding in tension for concrete.
		// The material is brittle and complete failure of fiber.
		IsFiberYielded = false;
	}
	else
	{
		// Strain is '-' and in Compression.
		// The yield compressive Strain is returned.
		// If the strain is greater than the yield strain.
		if (MyCompressionYieldStrain <= abs(Strain))
		{
			IsFiberYielded = true;
		};
	}

	return IsFiberYielded;
};

///<summary>Determine if the strain passed in has reach the maximum allowable strain.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
bool ConcreteMaterial2D::IsStrainAtMaximum(double Strain)
{
	bool IsFiberAtMaximum = false;

	if (Strain > 0)
	{
		// Strain is '+' and in Tension
		// There is no yielding in tension for concrete.
		// The material is brittle and complete failure of fiber.
		IsFiberAtMaximum = false;
	}
	else
	{
		// Strain is '-' and in Compression.
		// The failure compressive Strain is compared with the present strain.
		if (MyCompressionFailureStrain <= abs(Strain))
		{
			IsFiberAtMaximum = true;
		};
	}

	return IsFiberAtMaximum;
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
void ConcreteMaterial2D::Print()
{
	// State the Strain vs. Stress.
	double StrainIncrement = 0.00002;

	// Output the title.
	cout << "Strain " << "\t\t" << "Stress" << endl;

	for (int i = -200; i < 100; i++)
	{
		cout << i * StrainIncrement << "\t\t" << this -> GetStress(StrainIncrement * i) << endl;
	};
};