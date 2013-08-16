#pragma once

#include "Material2D.h"

using namespace std;
using namespace arma;

#ifndef Fiber2D_H
#define Fiber2D_H

class Fiber2D
{
	private:

	protected:
		Material2D* MyMaterial;

		int MyID;

		// Centroid of Fiber.
		double MyX;
		double MyY;

		// Area of Fiber.
		double MyArea;
		
		// Inertia about the X-X axis.
		double MyInertiaX;

		// Inertia about the Y-Y axis.
		double MyInertiaY;

	public:
		Fiber2D(void);

		~Fiber2D(void);

		Fiber2D& operator= (const Fiber2D &Fiber);

		void SetMaterial(Material2D &Material);

		int GetID();

		double GetX();

		double GetY();

		double GetArea();

		double GetInertiaX();
		
		double GetInertiaY();

		double GetDensity();

		int GetMaterialID();

		virtual double GetForce(double Strain);

		virtual bool IsStrainAtYield(double Strain);

		virtual bool IsStrainAtMaximum(double Strain);

		virtual void Print();
};

#endif