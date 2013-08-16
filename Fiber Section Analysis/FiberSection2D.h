#pragma once

#ifndef FiberSection2D_H
#define FiberSection2D_H

#include "stdafx.h"
#include "Fiber2D.h"

// Material Class
#include "Section2D.h"
#include "Material2D.h"
#include "ConcreteMaterial2D.h"
#include "RebarMaterial2D.h"
#include "PrestressStrandMaterial2D.h"

using namespace std;
using namespace arma;

class FiberSection2D
{
	private:
		
	protected:
		int MyID;

		vector <Fiber2D> MyFibers;

		vector <Material2D*> MyMaterials;

		// Centroid of the (X, Y) axis.
		double MyCentroidX;
		double MyCentroidY;

		double MyInertiaX;
		double MyInertiaY;

		double MyArea;

		// Tolerance for Sum of Forces.
		double MyForceTolerance;

		vector <vector<double>> MyPositiveCurvatureY;
		vector <vector<double>> MyNegativeCurvatureY;

	public:
		FiberSection2D(void);

		~FiberSection2D(void);

		FiberSection2D& operator= (const FiberSection2D &Section);

		FiberSection2D(const FiberSection2D& Section);

		int GetID();

		virtual void Analyze();

		virtual void CalculateFullMomentCurvatureX();
		virtual void CalculateFullMomentCurvatureY();

		virtual void CalculateCentroid();
		virtual void CalculateInertia();
		virtual void CalculateArea();

		vector <vector<double>> GetMomentCurvatureY();

		virtual Section2D GetBiLinearSection();

		void SetTolerance(double Tolerance);

		virtual double GetMassDensity();

		double GetMassPerUnitLength();
};

#endif