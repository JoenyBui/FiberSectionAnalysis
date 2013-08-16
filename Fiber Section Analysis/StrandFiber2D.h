#pragma once

#ifndef StrandFiber2D_H
#define StrandFiber2D_H

#include "Fiber2d.h"
#include "PrestressStrandMaterial2D.h"

using namespace std;
using namespace arma;

class StrandFiber2D : public Fiber2D
{
	private:

	protected:
		double MyDiameter;

	public:
		void Initialize(int ID,
						double X,
						double Y,
						double Diameter);

		StrandFiber2D(int ID, 
					  Material2D& Material,
					  double X,
					  double Y,
					  double Diameter);

		StrandFiber2D(int ID,
					  Material2D *Material,
					  double X,
					  double Y,
					  double Diameter);

		StrandFiber2D(void);

		~StrandFiber2D(void);

		StrandFiber2D& operator= (const StrandFiber2D &Fiber);

		double GetDiameter();
};

#endif
