#include "StdAfx.h"
#include "RebarMaterial2D.h"

void RebarMaterial2D::Initialize(int ID = -1, 
								 double Density = 1.0, 
								 double TensionElasticModulus = 0.0,
								 double TensionYieldStress = 0.0,
								 double TensionYieldPlateauStrain = 0.0,
								 double TensionUltimateStress = 0.0,
								 double TensionUltimateStrain = 0.0,
								 double TensionFailureStrain = 0.0,
								 double CompressionElasticModulus = 0.0,
								 double CompressionYieldStress = 0.0,
								 double CompressionYieldPlateauStrain = 0.0,
								 double CompressionUltimateStress = 0.0,
								 double CompressionUltimateStrain = 0.0,
								 double CompressionFailureStrain = 0.0,
								 bool StrainHardening = true,
								 double DIF_Yield = 1.0,
								 double DIF_Ultimate = 1.0)
{
	// Set the Density.
	MyMassDensity = Density;

	// Set the Dynamic Increase Factor.
	IncludeDIF = false;
	MyYieldDIF = DIF_Yield;
	MyUltimateDIF = DIF_Ultimate;

	MyID = ID;

	MyTensionElasticModulus = TensionElasticModulus;
	MyTensionYieldStress = TensionYieldStress;
	MyTensionYieldPlateauStrain = TensionYieldPlateauStrain;
	MyTensionUltimateStress = TensionUltimateStress;
	MyTensionUltimateStrain = TensionUltimateStrain;
	MyTensionFailureStrain = TensionFailureStrain;

	MyCompressionElasticModulus = CompressionElasticModulus;
	MyCompressionYieldStress = CompressionYieldStress;
	MyCompressionYieldPlateauStrain = CompressionYieldPlateauStrain;
	MyCompressionUltimateStress = CompressionUltimateStress;
	MyCompressionUltimateStrain = CompressionUltimateStrain;
	MyCompressionFailureStrain = CompressionFailureStrain;

	// Solve for the Yield Strain.
	MyTensionYieldStrain = MyTensionYieldStress / MyTensionElasticModulus;
	MyCompressionYieldStrain = MyCompressionYieldStress / MyCompressionElasticModulus;

	IncludeStrainHardening = StrainHardening;
};

void RebarMaterial2D::Clone(const RebarMaterial2D &Material)
{
	// Base Class Properties.
	MyID = Material.MyID;

	MyMassDensity = Material.MyMassDensity;

	IncludeDIF = Material.IncludeDIF;
	MyYieldDIF = Material.MyYieldDIF;
	MyUltimateDIF = Material.MyUltimateDIF;

	IncludeSIF = Material.IncludeSIF;
	MyYieldSIF = Material.MyYieldSIF;
	MyUltimateSIF = Material.MyYieldSIF;

	MyTensionElasticModulus = Material.MyTensionElasticModulus;
	MyTensionYieldStress = Material.MyTensionYieldStress;
	MyTensionYieldStrain = Material.MyTensionYieldStrain;
	MyTensionYieldPlateauStrain = Material.MyTensionYieldPlateauStrain;
	MyTensionUltimateStress = Material.MyTensionUltimateStress;
	MyTensionUltimateStrain = Material.MyTensionUltimateStrain;
	MyTensionFailureStrain = Material.MyTensionFailureStrain;

	MyCompressionElasticModulus = Material.MyCompressionElasticModulus;
	MyCompressionYieldStress = Material.MyCompressionYieldStress;
	MyCompressionYieldStrain = Material.MyCompressionYieldStrain;
	MyCompressionYieldPlateauStrain = Material.MyCompressionYieldPlateauStrain;
	MyCompressionUltimateStress = Material.MyCompressionUltimateStress;
	MyCompressionUltimateStrain = Material.MyCompressionUltimateStrain;
	MyCompressionFailureStrain = Material.MyCompressionFailureStrain;

	IncludeStrainHardening = Material.IncludeStrainHardening;
};

RebarMaterial2D::RebarMaterial2D(void)
{
}

///<summary>Constructor: Set the Elasic Modulus and the Yield Stress of the Rebar Material.
/// the values are defaulted to the Grade 60 bar.  Values are not ensured for other grade, use
/// the other constructor for more specific strains.</summary>
///<param name="name"></param>
///<remarks>description</remarks>
RebarMaterial2D::RebarMaterial2D(int ID, 
								 double Density,
								 double ElasticModulus, 
								 double YieldStress,
								 bool StrainHardening = true)
{
	// Set the ID.
	MyID = ID;

	double YieldStrain = YieldStress / ElasticModulus;

	this -> Initialize(ID, 
					   Density,
					   ElasticModulus,
					   YieldStress, 
					   4 * YieldStrain,
					   1.5 * YieldStress,
					   35 * YieldStrain, 
					   40 * YieldStrain,
					   ElasticModulus,
					   YieldStress, 
					   4 * YieldStrain,
					   1.5 * YieldStress,
					   35 * YieldStrain, 
					   40 * YieldStrain,
					   StrainHardening);
};

RebarMaterial2D::~RebarMaterial2D(void)
{
}

RebarMaterial2D& RebarMaterial2D::operator= (const RebarMaterial2D &Material)
{
	this -> Clone(Material);

	return *this;
};

///<summary>Return the stress given the strain in the member.</summary>
///<param name="Strain">'+' strain is tension :: '-' strain is compression.</param>
///<remarks>description</remarks>
double RebarMaterial2D::GetStress(double Strain)
{
	// Initialize return variable.
	double Stress = 0.0;

	if (Strain > 0.0) 
	{
		Stress = this -> GetTensileStress(Strain);
	}
	else if (Strain < 0.0)
	{
		Stress = this -> GetCompressiveStress(Strain);
	}
	else
	{
		Stress = 0.0;
	};

	// Return variable.
	return Stress;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double RebarMaterial2D::GetTensileStress(double Strain)
{
	// Initialize return variable.
	double Stress = 0.0;

	// Change Strain.
	Strain = abs(Strain);

	if (Strain < MyTensionYieldStrain)
	{
		// Rebar remains elastic.
		Stress = MyTensionElasticModulus * Strain;

		// Include Dynamic Increase Factor.
		if (IncludeDIF)
		{
			Stress *= MyYieldDIF;
		};
	}
	else if(Strain < MyTensionYieldPlateauStrain)
	{
		// Rebar is in the Plateau Region.
		Stress = MyTensionYieldStress;

		// Include Dynamic Increase Factor.
		if (IncludeDIF)
		{
			Stress *= MyYieldDIF;
		};
	}
	else if(Strain < MyTensionUltimateStrain)
	{
		if (IncludeStrainHardening)
		{
			// Parabolic Stress Strain Curve.
			double e_sf = Strain;
			double e_sh = MyTensionYieldStrain;
			double e_su = MyTensionUltimateStrain;
		
			double f_sy = MyTensionYieldStress;
			double f_su = MyTensionUltimateStress;

			Stress = (1 / pow(e_su - e_sh,2)) * ((f_sy - f_su) * e_sf * e_sf 
												+ (2 * e_su * f_su - 2 * e_su * f_sy) * e_sf 
												+ e_su * e_su * f_sy 
												- 2 * e_su * e_sh * f_su 
												+ e_sh * e_sh * f_su);

			// Include Dynamic Increase Factor.
			if (IncludeDIF)
			{
				Stress *= MyUltimateDIF;
			};
		}
		else
		{
			// Rebar is in the Plateau Region.
			Stress = MyTensionYieldStress;

			// Include Dynamic Increase Factor.
			if (IncludeDIF)
			{
				Stress *= MyYieldDIF;
			};
		};
		
	}
	else
	{
		// Rebar failed.
		Stress = 0.0;
	};

	// Return variable.
	return +Stress;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double RebarMaterial2D::GetCompressiveStress(double Strain)
{
	// Initialize return variable.
	double Stress = 0.0;

	// Change Strain.
	Strain = abs(Strain);

	if (Strain < MyCompressionYieldStrain)
	{
		// Rebar remains elastic.
		Stress = MyCompressionElasticModulus * Strain;

		// Include Dynamic Increase Factor.
		if (IncludeDIF)
		{
			Stress *= MyYieldDIF;
		};
	}
	else if(Strain < MyCompressionYieldPlateauStrain)
	{
		// Rebar is in the Plateau Region.
		Stress = MyCompressionYieldStress;

		// Include Dynamic Increase Factor.
		if (IncludeDIF)
		{
			Stress *= MyYieldDIF;
		};
	}
	else if(Strain < MyCompressionUltimateStrain)
	{
		if (IncludeStrainHardening)
		{
			// Parabolic Stress Strain Curve.
			double e_sf = Strain;
			double e_sh = MyCompressionYieldStrain;
			double e_su = MyCompressionUltimateStrain;
			
			double f_sy = MyCompressionYieldStress;
			double f_su = MyCompressionUltimateStress;

			Stress = (1 / pow(e_su - e_sh,2)) * ((f_sy - f_su) * e_sf * e_sf 
												 + (2 * e_su * f_su - 2 * e_su * f_sy) * e_sf 
												 + e_su * e_su * f_sy 
												 - 2 * e_su * e_sh * f_su 
												 + e_sh * e_sh * f_su);

			// Include Dynamic Increase Factor.
			if (IncludeDIF)
			{
				Stress *= MyUltimateDIF;
			};
		}
		else
		{
			Stress = MyCompressionYieldStress;

			// Include Dynamic Increase Factor.
			if (IncludeDIF)
			{
				Stress *= MyYieldDIF;
			};
		};
	}
	else
	{
		// Rebar failed.
		Stress = 0.0;
	};

	// Return variable.
	return -Stress;
};

///<summary></summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
double RebarMaterial2D::GetTensionYieldStrain() 
{
	return MyTensionYieldStrain;
};

double RebarMaterial2D::GetTensionFailureStrain() 
{
	return MyTensionFailureStrain;
};

///<summary></summary>
///<param name="name"></param>
///<remarks>description</remarks>
double RebarMaterial2D::GetCompressionYieldStrain() 
{
	return MyCompressionYieldStrain;
};

double RebarMaterial2D::GetCompressionFailureStrain()
{
	return MyCompressionFailureStrain;
};

///<summary>Determine if the strain passed in has reach yielded strain.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
bool RebarMaterial2D::IsStrainAtYield(double Strain)
{
	bool IsFiberYielded = false;

	if (Strain > 0)
	{
		// Strain is '+' and in Tension
		if (MyTensionYieldStrain <= abs(Strain))
		{
			IsFiberYielded = true;
		};
	}
	else
	{
		// Strain is '-' and in Compression
		if (MyCompressionYieldStrain <= abs(Strain))
		{
			IsFiberYielded = true;
		};
	}

	return IsFiberYielded;
};

///<summary>Determine if the strain passed in has reach maximum allowable strain.</summary>
///<param name="name"></param>
///<returns>description</returns>
///<remarks>description</remarks>
bool RebarMaterial2D::IsStrainAtMaximum(double Strain)
{
	bool IsFiberAtMaximum = false;

	if (Strain > 0)
	{
		// Strain is '+' and in Tension
		// Did the strain goes beyond fracture strain.
		if (MyTensionFailureStrain <= abs(Strain))
		{
			IsFiberAtMaximum = true;
		};
	}
	else
	{
		// Strain is '-' and in Compression.
		// Did the strain goes beyond fracture strain.
		if (MyCompressionFailureStrain <= abs(Strain))
		{
			IsFiberAtMaximum = true;
		};
	}

	return IsFiberAtMaximum;
};

void RebarMaterial2D::Print()
{
	// State the Strain vs. Stress.
	double StrainIncrement = 0.0005;

	// Output the title.
	cout << "Strain " << "\t\t" << "Stress" << endl;

	for (int i = -100; i < 100; i++)
	{
		cout << i * StrainIncrement << "\t\t" << this -> GetStress(StrainIncrement * i) << endl;
	};
};