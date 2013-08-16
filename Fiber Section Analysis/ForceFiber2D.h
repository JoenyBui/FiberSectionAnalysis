#pragma once

#ifndef ForceFiber2D_H
#define ForceFiber2D_H

#include "stdafx.h"

using namespace std;
using namespace arma;

class ForceFiber2D
{
	private:
	protected:
		int MyID;

		double MyX;
		double MyY;

		double MyMagnitude;
	public:
		void Initialize(int ID,
						double Magnitude,
						double X,
						double Y);

		ForceFiber2D(int ID,
					 double Magnitude, 
					 double X, 
					 double Y);

		ForceFiber2D(void);
		
		~ForceFiber2D(void);

		ForceFiber2D& operator= (const ForceFiber2D &Section);

		ForceFiber2D(const ForceFiber2D &Section);

		double GetX();

		double GetY();

		double GetMagnitude();
};

#endif