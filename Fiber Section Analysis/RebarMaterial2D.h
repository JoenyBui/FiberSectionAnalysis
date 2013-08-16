#pragma once

#include "Material2d.h"
#include "stdafx.h"

using namespace std;
using namespace arma;

#ifndef RebarMaterial2D_H
#define RebarMaterial2D_H

class RebarMaterial2D : public Material2D
{
	private:
		double GetTensileStress(double Strain);
		double GetCompressiveStress(double Strain);

		void Initialize(int ID, 
						double Density,
						double TensionElasticModulus,
			            double TensionYieldStress,
						double TensionYieldPlateauStrain,
						double TensionUltimateStress,
						double TensionUltimateStrain,
						double TensionFractureStrain,
						double CompressionElasticModulus,
			            double CompressionYieldStress,
						double CompressionYieldPlateauStrain,
						double CompressionUltimateStress,
						double CompressionUltimateStrain,
						double CompressionFractureStrain,
						bool StrainHardening,
						double DIF_Yield,
						double DIF_Ultimate);

		void Clone(const RebarMaterial2D &Material);


	protected:
		double MyTensionElasticModulus;
		double MyTensionYieldStress;
		double MyTensionYieldStrain;
		double MyTensionYieldPlateauStrain;
		double MyTensionUltimateStress;
		double MyTensionUltimateStrain;
		double MyTensionFailureStrain;

		double MyCompressionElasticModulus;
		double MyCompressionYieldStress;
		double MyCompressionYieldStrain;
		double MyCompressionYieldPlateauStrain;
		double MyCompressionUltimateStress;
		double MyCompressionUltimateStrain;
		double MyCompressionFailureStrain;

		bool IncludeStrainHardening;
	public:
		RebarMaterial2D(int ID, 
						double Density,
			            double ElasticModulus, 
						double YieldStress,
						bool StrainHardening);

		RebarMaterial2D(void);

		~RebarMaterial2D(void);

		RebarMaterial2D& operator= (const RebarMaterial2D &Material);

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