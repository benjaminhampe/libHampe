// Quelltext von BenjaminHampe@gmx.de (c) 2009 - 2010
// Anleitung: definiere Ax=b und rufe Solve() auf, dann lese Vektor x aus

#ifndef __IRR_EXTENSION_GAUSS_LINEAR_SYSTEM_SOLVER_H__
#define __IRR_EXTENSION_GAUSS_LINEAR_SYSTEM_SOLVER_H__

#include <irrTypes.h>
#include <irrMath.h>

namespace irr
{

/// simple Linear-System solver ( does Gauss Elimination and LU decomposition,
/// but no direct inverse calculation so far )
/// entstand zur Lösung von Schnittpunkten von mehdimensionalen ( >4 dim ) Vektoren

/// example:

/// geg:    E1 = A1 + r*v1 + s*v2 ( Ebene )
///         E2 = A2 + r*w1 + s*w2 ( Ebene )

///------------------------------------------------
/// ges:    suche Schnittpunkt E1 = E2
///
/// A1 + r*v1 + s*v2 = A2 + r*w1 + s*w2
///
/// r*v1 + s*v2 - r*w1 - s*w2 = A2 - A1
///
/// r*(v1-w1) + s*(v2-w2) = A2 - A1
///
/// [(v1-w1) (v2-w2)] * (r s)^T = A2 - A1
///
/// finales LGS:
///                           ->          ->
///           A           *   x   =       b
///           |               |           |
/// [(v10-w10) (v20-w20)]           [ A20 - A10 ]
/// [(v11-w11) (v21-w21)] * ( r ) = [ A21 - A11 ]
/// [   ... 	     ...  ]   ( s )   [    ...    ]
/// [(v1m-w1m) (v2m-w2m)]           [ A2m - A1m ]
///
///
/// input A,b to get x at (A,b)
///

class Gauss
{
	static f64 **ALLOC_2D_ARRAY_OF_DOUBLE	(s32 dx, s32 dy);
	static f64  *ALLOC_1D_ARRAY_OF_DOUBLE	(s32 dy);
	static s32 **ALLOC_2D_ARRAY_OF_INTEGER	(s32 dx, s32 dy);
	static s32  *ALLOC_1D_ARRAY_OF_INTEGER	(s32 dy);
	static bool *ALLOC_1D_ARRAY_OF_BOOLEAN	(s32 dy);

	static void FREE_2D_ARRAY_OF_DOUBLE	(f64 **p, s32 dx);
	static void FREE_1D_ARRAY_OF_DOUBLE	(f64 *p);
	static void FREE_2D_ARRAY_OF_INTEGER	(s32 **p, s32 dx);
	static void FREE_1D_ARRAY_OF_INTEGER	(s32 *p);
	static void FREE_1D_ARRAY_OF_BOOLEAN	(bool *p);

	public:
		// Konstruktor - Destruktor
		 Gauss(s32 xy); //` Malloc()
		~Gauss();		//` Delete()

		// Initialisierung und Reservierung von Speicher
		void Malloc(s32 xy);				//` allokiert A,x(p),b
		void Delete();						//` deallokiert A,x(p),b
		void Reset(s32 xy);					//` deallokiert und allokiert A,x(p),b neu

		// Input-Output
		void	SetA(s32 x, s32 y, f64 e);	//` setzt Element in Matrix A
		void	Setb(s32 y, f64 e);			//` setzt Element in Vektor b
		f64		GetA(s32 x, s32 y);				//` return Element in Matrix A
		f64		Getb(s32 y);					//` return Element in Vektor b
		f64		Getx(s32 y);					//` return Element in Vektor x
		bool	GetxBool(s32 y);				//` return Flag ob x zur lösung beiträgt

		// Lösen eines linearen LGS Ax=b
		void Pivotiere(s32 x);					//` Wird in jeder Iteration einmal aufgerufen um die Matrix nach Pivot zu ordnen
		void VertauscheZeile(s32 y0, s32 y1);	//` Vertauscht die Zeilen y0 und y1 [y element 0..n-1]
		void VertauscheSpalte(s32 x0, s32 x1);	//` Vertauscht die Spalten x0 und x1 [x element 0..n-1]
		void EliminiereSpalte(s32 x);			//` lässt alle Elemente einer Spalte unter der diagonalen zu null werden
		void Check_Zeile(s32 y);				//` Prüft Lösbarkeit einer Zeile y
		void Check_System(s32 x);				//` Prüft Lösbarkeit des Systems ab Spalte/Zeile x
		void Solve();							//` Löst das LSG vollständig durch obere Dreiecksmatrix
		s32  GetLoesung();						//` Gibt Lösungsmenge an (0=keine, 1=eine, 2=unendlich)
		s32  GetRang();							//` Gibt den Lösungsraum an (Anzahl linear unabhängiger Zeilen)

		// Inverse einer Matrix
		f64 det();							//` Berechnet Determinante der gesammten Matrix
		f64 subDet(s32 x, s32 y);				//` Berechnet Unterdeterminante -> rekursiv für n>3
		void inverse();							//` Berechnet die Inverse Matrix
		bool inverse_exist();					//` Wert 1 wenn determinante != 0 ist, sonst 0

	private:
		// A(x;y)*x(P(y))=b(y)
		s32 	n;			// Matrix Dimension
		f64** 	A;		// Matrix
		f64* 	x;			// Lösungen
		bool* 	xbool;		// Flags der Lösungen
		f64* 	b;			// Konstanten
		s32* 	P;			// Reihenfolge der Lösungen
		f64		epsilon;	// minimale Differenz, alles darunter wird null gesetzt
		s32		loesung;	// 0 = unlösbar (Rang = 0), 1 = eindeutig (Rang = n), 2 mehrdeutig (Rang < n)
		s32		rang;		// gibt den Lösungsraum an, z.B. n=3 -> mögliche Ränge 0D,1D,2D,3D
		f64		determinante;	// gibt Auskunft über die Existenz einer Inversen Matrix A^-1
		bool	bInverse_exist; // gibt Auskunft über die Existenz einer Inversen Matrix A^-1
};

} // end namespace irr


#endif
