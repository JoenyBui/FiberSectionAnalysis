#pragma once
#include "Material2d.h"

using namespace std;
using namespace arma;

#ifndef PrestressStrandMaterial2D_H
#define PrestressStrandMaterial2D_H

class PrestressStrandMaterial2D : public Material2D
{
	private:
		void SetPowerLawConstants(int Type);

		void Initialize(int ID,
						string TypeOfStrand,
						double Density,
						double TensionElasticModulus,
						double TensionYieldStress,
						double TensionYieldStrain,
						double TensionUltimateStress,
						double TensionUltimateStrain,
						double PowerConstantA,
						double PowerConstantB,
						double PowerConstantC,
						double PowerConstantD,
						double TensionInitialStrain,
						double DIF_Yield,
						double DIF_Ultimate);

		void Clone(const PrestressStrandMaterial2D &Material);
	protected:
		string MyTypeOfStrand;

		double MyTensionInitialStrain;

		double MyTensionElasticModulus;
		double MyTensionYieldStress;
		double MyTensionYieldStrain;
		double MyTensionUltimateStress;
		double MyTensionUltimateStrain;

		double MyPowerConstantA;
		double MyPowerConstantB;
		double MyPowerConstantC;
		double MyPowerConstantD;
	public:
		static const int Type270ksiStrand = 1;
		static const int Type250ksiStrand = 2;
		static const int Type250ksiWire = 3;
		static const int Type235ksiWire = 4;
		static const int Type150ksiBar = 5;

		PrestressStrandMaterial2D(int ID,
			                      int TypeOfStrand,
								  double Density,
								  double InitialStrain);

		PrestressStrandMaterial2D(void);

		~PrestressStrandMaterial2D(void);
		
		PrestressStrandMaterial2D& operator= (const PrestressStrandMaterial2D &Material);

		double GetStress(double Strain);

		double GetTensionYieldStrain();
		double GetTensionFailureStrain();

		double GetCompressionYieldStrain();
		double GetCompressionFailureStrain();

		bool IsStrainAtYield(double Strain);

		bool IsStrainAtMaximum(double Strain);

		void Print();
};

#endif