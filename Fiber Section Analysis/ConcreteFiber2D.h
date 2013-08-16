#pragma once

#ifndef ConcreteFiber2D_H
#define ConcreteFiber2D_H

#include "Fiber2d.h"
#include "ConcreteMaterial2D.h"

using namespace std;
using namespace arma;

class ConcreteFiber2D : public Fiber2D
{
	private:
		vector <Fiber2D*> MyVectorReinforcement;

	protected:

		double MyWidth;
		double MyThickness;
	public:
		void Initialize(int ID, 
						double X, 
						double Y, 
						double Width,
						double Thickness);

		ConcreteFiber2D(int ID, 
						Material2D& Material,
						double X, 
						double Y, 
						double Width, 
						double Thickness);

		ConcreteFiber2D(void);

		~ConcreteFiber2D(void);

		ConcreteFiber2D& operator= (const ConcreteFiber2D &Fiber);

		void AddBindingReinforcement(Fiber2D* Fiber);

		double GetForce(double Strain,
						double Curvature);
};

#endif
