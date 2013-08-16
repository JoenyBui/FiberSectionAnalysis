#pragma once

#ifndef GirderSection2D_H
#define GirderSection2D_H

using namespace std;
using namespace arma;

#include "FiberSection2d.h"

#include "ForceFiber2D.h"
#include "ConcreteFiber2D.h"
#include "RebarFiber2D.h"
#include "StrandFiber2D.h"

/*
                                               |<--- W5 -->|
                   |<-----             W1      ----------->|
        -------    *****************************************   [Z6]
           D2      *                                       *
        ------     *                                       *   [Z5]
           D3          *                               *
                           *                       *
        -------                  *             *               [Z4]
           D4                     *          *
        -------                    *       *                   [Z3]
                                   *       *
                                   *<- W3->* |<-- W4
                                   *       *
                                   *       *
           D7                      *       *
                                   *       *
                                   *       *
                                   *       *
                                   *       *|--|<--W6
                                   *       *
        -------                    *       *                   [Z2]
           D5                    *           *
        -------                *               *               [Z1]
           D6                  *               *
        -------                *****************               [Z0]
                               <--     W2    -->
*/

class GirderSection2D :	public FiberSection2D
{
	private:
		string MyGirderType;

		double MyD1;
		double MyD2;
		double MyD3;
		double MyD4;
		double MyD5;
		double MyD6;
		double MyD7;

		double MyW1;
		double MyW2;
		double MyW3;
		double MyW4;
		double MyW5;
		double MyW6;

		double MyDesiredFiberIncrement;
	protected:
		// Materials.
		ConcreteMaterial2D MyConcreteMaterial;

		vector <RebarMaterial2D> MyRebarMaterials;
		vector <PrestressStrandMaterial2D> MyPrestressStrandsMaterials;

		// Array of Fibers.
		vector <ForceFiber2D> MyForceFibers;
		vector <ConcreteFiber2D> MyConcreteFibers;
		vector <RebarFiber2D> MyRebarFibers;
		vector <StrandFiber2D> MyStrandFibers;

	public:
		static const int ID_TypeI = 1;
		static const int ID_TypeII = 2;
		static const int ID_TypeIII = 3;
		static const int ID_TypeIV = 4;
		static const int ID_TypeV = 5;
		static const int ID_TypeVI = 6;

		void Initialize(double D1,
						double D2,
						double D3, 
						double D4,
						double D5,
						double D6,
						double W1,
						double W2, 
						double W3, 
						double W4,
						double W5,
						double W6,
						string GirderType,
						double DesiredFiberIncrement,
						double Tolerance);

		void Clone(const GirderSection2D &Section);

		GirderSection2D(int TypeOfGirder);

		GirderSection2D(vector <double> Widths,
						vector <double> Depths, 
						double DesiredIncrement,
						double Tolerance);

		GirderSection2D(vector <double> *Widths,
						vector <double> *Depths, 
						double DesiredIncrement,
						double Tolerance);

		GirderSection2D(void);

		~GirderSection2D(void);

		GirderSection2D& operator= (const GirderSection2D &Section);

		GirderSection2D(const GirderSection2D& Section);

		// Force 
		void AddForceFiber(ForceFiber2D Fiber);

		// Concrete Section
		void SetGirderDimension(int TypeOfGirder);

		void AddConcreteMaterial(ConcreteMaterial2D Material);
		void AddConcreteMaterial(ConcreteMaterial2D *Material);

		void SetDesiredFiberIncrement(double DesiredIncrement);

		void MeshConcreteFiber();

		// Rebar Section
		void AddRebarMaterial(RebarMaterial2D Material);
		void AddRebarMaterial(RebarMaterial2D *Material);

		void AddRebar(RebarFiber2D Fiber);
		void AddRebar(RebarFiber2D *Fiber);

		int GetRebarIndex(int ID);

		// Strand Section
		void AddStrandMaterial(PrestressStrandMaterial2D Material);
		void AddStrandMaterial(PrestressStrandMaterial2D *Material);

		void AddStrand(StrandFiber2D Fiber);
		void AddStrand(StrandFiber2D *Fiber);
			
		int GetStrandIndex(int ID);

		void SetBindingReinforcements();
		void SetBindingReinforcement(Fiber2D* Fiber, 
									 double EffectiveRange);

		void CalculateFullMomentCurvatureX();
		void CalculateFullMomentCurvatureY();

		void CalculateCentroid();
		void CalculateInertia();
		void CalculateArea();

		vector <vector<double>> GetCurvatureVectorY(double CurvatureIncrement,
													int MaxCurvatureCounter);

		double GetNextStrainIncrement(double Curvature,
									  double Strain,
									  double StrainIncrement);

		double GetStrainDirection(double PositiveStrainForce, 
			                      double NeutralStrainForce,
								  double NegativeStrainForce);

		double GetCurvatureIncrement(double Curvature);

		double GetForce(double Curvature,
			            double StrainAtCentroid);

		double GetMoment(double Curvature,
						 double StrainAtCentroid);

		double GetMassDensity();

		// Return the Bi-Linear Section of the Girder.
		Section2D GetBiLinearSection();

		vector <vector<double>>  GetBiLinearSectionPoints(vector <vector<double>> Curvature);

		vector <vector<double>>  GetLinearSectionPoints(vector <vector<double>> Curvature);

		bool IsSectionYielding(double Curvature,
			                   double StrainAtCentroid);

		bool IsSectionAtMaximumCapacity(double Curvature,
										double StrainAtCentroid);

		double GetInitialForce();
		double GetInitialMoment();

		double GetTopFlangeWidth();
		double GetBottomFlangeWidth();
		double GetDepth();
};

#endif