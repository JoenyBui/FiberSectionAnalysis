#include "StdAfx.h"

#pragma once

using namespace std;
using namespace arma;

#ifndef Material2D_H
#define Material2D_H

class Material2D
{
	private:

	protected:
		int MyID;

		// Density or Unit Weight of Fiber.
		double MyMassDensity;

		double MyYieldDIF;
		double MyUltimateDIF;

		double MyYieldSIF;
		double MyUltimateSIF;

	public:
		bool IncludeDIF;
		bool IncludeSIF;

		Material2D(void);

		~Material2D(void);

		Material2D& operator =(const Material2D &Material);

		void SetID(int ID);

		void SetDensity(double Density);

		int GetID();

		double GetDensity();

		void IncludeDynamicIncreaseFactor(double YieldDIF, 
										  double UltimateDIF);

		virtual double GetStress(double Strain) = 0;

		virtual double GetTensionYieldStrain() = 0;

		virtual double GetCompressionYieldStrain() = 0;

		virtual bool IsStrainAtYield(double Strain) = 0;

		virtual bool IsStrainAtMaximum(double Strain) = 0;

		virtual void Print();
};

#endif