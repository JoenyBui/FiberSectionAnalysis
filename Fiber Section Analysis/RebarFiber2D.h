#pragma once

#ifndef RebarFiber2D_H
#define RebarFiber2D_H

#include "Fiber2d.h"
#include "RebarMaterial2D.h"

class RebarFiber2D : public Fiber2D
{
	private:

	protected:
		double MyDiameter;


	public:
		void Initialize(int ID,
						double X,
						double Y,
						double Diameter);

		RebarFiber2D(int ID, 
					 Material2D& Material,
					 double X,
					 double Y,
					 double Diameter);

		RebarFiber2D(int ID, 
					 Material2D& Material,
					 double X,
					 double Y,
					 int BarType);

		RebarFiber2D(int ID,
					 Material2D *Material,
					 double X,
					 double Y,
					 double Diameter);

		RebarFiber2D(int ID,
					 Material2D *Material,
					 double X,
					 double Y,
					 int BarType);
					
		RebarFiber2D(void);

		~RebarFiber2D(void);

		RebarFiber2D& operator= (const RebarFiber2D &Fiber);

		static const int Type_No3 = 0;
		static const int Type_No4 = 1;
		static const int Type_No5 = 2;
		static const int Type_No6 = 3;
		static const int Type_No7 = 4;
		static const int Type_No8 = 5;
		static const int Type_No9 = 6;
		static const int Type_No10 = 7;
		static const int Type_No11 = 8;
		static const int Type_No14 = 9;
		static const int Type_No18 = 10;

		void SetBarType(int BarType);

		double GetDiameter();
};

#endif