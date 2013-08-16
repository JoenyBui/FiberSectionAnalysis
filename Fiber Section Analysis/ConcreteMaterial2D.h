#pragma once

#include "Material2d.h"

using namespace std;
using namespace arma;

#ifndef ConcreteMaterial2D_H
#define ConcreteMaterial2D_H

class ConcreteMaterial2D : public Material2D
{
	private:
		double GetStressWithThorenfeldtParabola(double Strain);
		double GetStressWithTensionStiffening(double Strain, 
											  bool BindingReinforcement);

		double GetStressWithHognestadParabola(double Strain);
		double GetStressWithTensionLinear(double Strain);

		void Initialize(int ID,
						double Density,
						double UltimateStress,
						double FailureStrain,
						double YieldStrain,
						bool TensionStiffening,
						double Alpha1,
						double Alpha2,
						double DIF_Yield,
						double DIF_Ultimate);

		void Clone(const ConcreteMaterial2D &Material);
	protected:
		double MyCompressionElasticModulus;
        double MyCompressionYieldStrain;
        double MyCompressionUltimateStress;
        double MyCompressionUltimateStrain;
		double MyCompressionFailureStrain;

		// Thorenfeldt, Tomaszewicz, and Jensen Parameter. (TTJ)
		double MyTTJ_CompressionCurveFittingFactor;
		double MyTTJ_CompressionPostPeakDecayFactor;
		double MyTTJ_CompressionUltimateStrain;

		double MyTensionElasticModulus;
        double MyTensionUltimateStress;
        double MyTensionUltimateStrain;
		double MyTensionFailureStrain;

		// Tension Stiffening Parameter. (See Collins and Mitchell for more information)
		double MyTS_TensionAlpha1;
		double MyTS_TensionAlpha2;

		bool IncludeTensionStiffening;
	public:
		ConcreteMaterial2D(void);

		ConcreteMaterial2D(int ID,
						   double Density,
						   double UltimateStress,
						   double FailureStrain,
						   bool TensionStiffening);

		~ConcreteMaterial2D(void);

		ConcreteMaterial2D& operator= (const ConcreteMaterial2D &Material);

		double GetStress(double Strain);

		double GetStress(double Strain,
			             bool BindingReinforcement);

		double GetTensionYieldStrain();
		
		double GetTensionFailureStrain();

		double GetCompressionYieldStrain();

		double GetCompressionFailureStrain();

		bool IsStrainAtYield(double Strain);

		bool IsStrainAtMaximum(double Strain);

		void Print();
};

#endif