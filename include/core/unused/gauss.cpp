
#include "gauss.h"

namespace irr
{

/////////////////////////////////////////////////////////////////////

f64** Gauss::ALLOC_2D_ARRAY_OF_DOUBLE(s32 dx, s32 dy)
{
	f64 **p=new f64*[dx];
	s32 i,j;
	for (i=0; i<dx; i++)
	{
		p[i]=new f64[dy];
	}
	for (i=0; i<dx; i++)
		for (j=0; j<dy; j++)
			p[i][j]=0.0;
	return p;
}

/////////////////////////////////////////////////////////////////////

f64* Gauss::ALLOC_1D_ARRAY_OF_DOUBLE(s32 dy)
{
	f64 *p=new f64[dy];
	for (s32 i=0; i<dy; i++)	p[i]=0;
	return p;
}

/////////////////////////////////////////////////////////////////////

s32** Gauss::ALLOC_2D_ARRAY_OF_INTEGER(s32 dx, s32 dy)
{
	s32 **p=new s32*[dx];
	s32 i,j;
	for (i=0; i<dx; i++)
	{
		p[i]=new s32[dy];
	}
	for (i=0; i<dx; i++)
		for (j=0; j<dy; j++)
			p[i][j]=0;
	return p;
}

/////////////////////////////////////////////////////////////////////

s32* Gauss::ALLOC_1D_ARRAY_OF_INTEGER(s32 dy)
{
	s32 *p=new s32[dy];
	for (s32 i=0; i<dy; i++)	p[i]=0;
	return p;
}

/////////////////////////////////////////////////////////////////////

bool* Gauss::ALLOC_1D_ARRAY_OF_BOOLEAN(s32 dy)
{
	bool *p=new bool[dy];
	for (s32 i=0; i<dy; i++)	p[i]=false;
	return p;
}

/////////////////////////////////////////////////////////////////////

void Gauss::FREE_1D_ARRAY_OF_BOOLEAN(bool *p) { if (!p) return;	delete [] p; p = NULL; }

void Gauss::FREE_1D_ARRAY_OF_INTEGER(s32 *p) { if (!p) return; delete [] p; p = NULL; }

void Gauss::FREE_1D_ARRAY_OF_DOUBLE(f64 *p) { if (!p) return; delete [] p; p = NULL; }

void Gauss::FREE_2D_ARRAY_OF_INTEGER(s32 **p, s32 dx)
{
	if (!p) return;
	s32 i;
	for (i=0; i<dx; i++)
		delete [] p[i];
	delete [] p;
	p = NULL;
}

void Gauss::FREE_2D_ARRAY_OF_DOUBLE(f64 **p, s32 dx)
{
	if (!p) return;
	for (s32 i=0; i<dx; i++)
		delete [] p[i];
	delete [] p;
	p = NULL;
}


/////////////////////////////////////////////////////////////////////////////

Gauss::Gauss(s32 xy)
{
	Malloc(xy);
}

/////////////////////////////////////////////////////////////////////////////

Gauss::~Gauss()
{
	Delete();
}


/////////////////////////////////////////////////////////////////////////////

void Gauss::Reset(int xy)
{
	Delete();
	Malloc(xy);
}

/////////////////////////////////////////////////////////////////////////////

void Gauss::SetA(s32 x, s32 y, f64 e)
{
	if ((x<0) || (x>n-1) || (y<0) || (y>n-1)) return;
	if (abs(e)<epsilon) A[x][y]=0.0;
	else				A[x][y]=e;
}
/////////////////////////////////////////////////////////////////////////////
void Gauss::Setb(s32 y, f64 e)
/////////////////////////////////////////////////////////////////////////////
{
	if ((y<0) || (y>n-1)) return;
	if (abs(e)<epsilon) b[y]=0.0;
	else		   b[y]=e;
}
/////////////////////////////////////////////////////////////////////
s32  Gauss::GetLoesung()
/////////////////////////////////////////////////////////////////////
{
	return loesung;
}
/////////////////////////////////////////////////////////////////////
s32  Gauss::GetRang()
/////////////////////////////////////////////////////////////////////
{
	return rang;
}
/////////////////////////////////////////////////////////////////////////////
f64 Gauss::GetA(s32 x, s32 y)
/////////////////////////////////////////////////////////////////////////////
{
	if ((x<0) || (x>n-1) || (y<0) || (y>n-1)) return 0.0;
	return A[x][y];
}
/////////////////////////////////////////////////////////////////////////////
f64 Gauss::Getb(s32 y)
/////////////////////////////////////////////////////////////////////////////
{
	if ((y<0) || (y>n-1)) return 0.0;
	return b[y];
}
/////////////////////////////////////////////////////////////////////
f64 Gauss::Getx(s32 y)
/////////////////////////////////////////////////////////////////////
{
	if ((y<0) || (y>=n)) return false;
	return x[P[y]];
}
/////////////////////////////////////////////////////////////////////
bool Gauss::GetxBool(s32 y)
/////////////////////////////////////////////////////////////////////
{
	if ((y<0) || (y>=n)) return false;
	return xbool[P[y]];
}


/////////////////////////////////////////////////////////////////////////////

void Gauss::Malloc(s32 xy)
{
	if (xy<1) return;
	if (xy<0) loesung=0;
	n=xy;			// Größe des LGS
	rang=xy;		// Default : n -> Anz. Unbekannte die zur Lösung beitragen == Anz. Gleichungen
	loesung=1;		// Default : 1 -> LGS eindeutig lösbar
	epsilon=1e-15;
	determinante=0.0;

	// Allokiere Speicher für LGS
	A=ALLOC_2D_ARRAY_OF_DOUBLE(n,n);
	x=ALLOC_1D_ARRAY_OF_DOUBLE(n);
	b=ALLOC_1D_ARRAY_OF_DOUBLE(n);
	P=ALLOC_1D_ARRAY_OF_INTEGER(n);
	xbool=ALLOC_1D_ARRAY_OF_BOOLEAN(n);

	// Setze Reihenfolge der Unbekannten
	for (s32 y=0; y<n; y++)
	{
		P[y]=y;			// Reihenfolge der Unbekannten ( verändert sich durch VertauscheSpalte() )
		xbool[y]=true;	// Flag ob Unbekannte x[P[y]] an Lösung teilnehmen
	}
}

/////////////////////////////////////////////////////////////////////////////

void Gauss::Delete()
{
	FREE_2D_ARRAY_OF_DOUBLE(A,n);
	FREE_1D_ARRAY_OF_DOUBLE(x);
	FREE_1D_ARRAY_OF_DOUBLE(b);
	FREE_1D_ARRAY_OF_INTEGER(P);
	FREE_1D_ARRAY_OF_BOOLEAN(xbool);
}
/////////////////////////////////////////////////////////////////////////////
void Gauss::Check_System(s32 x)
/////////////////////////////////////////////////////////////////////////////
{
//
//  Abbruchbedingungen
	if (loesung==0) return;
//
//  Setze Rang auf Matrixgröße
	rang=n;
//
//  Prüfe alle Zeilen
	s32 y;
	for (y=x; y<n; y++)
	{
		Check_Zeile(y);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Gauss::Check_Zeile(s32 y)
/////////////////////////////////////////////////////////////////////////////
{
//
//  Abbruchbedingungen
//
	if (loesung==0) return;
	if ((y<0) || (y>=n)) return;
//
//  locals
//
	s32 x;
	bool only_zero=true;
// #--------------------------------------------------------------------------------#
// # Prüfe ob alle Elemente von der Zeile null sind, wenn nein, dann flag auf false #
// #--------------------------------------------------------------------------------#
	for (x=0; x<n; x++)
	{
		if (A[x][y]!=0.0)
			only_zero=false;
	}
// #-----------------------------------------------------------------------------------------------#
// # Wenn die Zeile der Matrix nur aus nullen besteht, dann prüfe lösbarkeit, und verkleinere rang #
// #-----------------------------------------------------------------------------------------------#
	if (only_zero==true)
	{
		if (b[y]==0.0)	// z.B. 0,0,0,0|0
		{
			loesung=2;	// SYSTEM mehrdeutig
			rang--;		// RANG = RANG - 1
		}
		else			// z.B. 0,0,0,0|15
		{
			loesung=0;  // SYSTEM unlösbar
			rang=0;		// RANG = 0
		}
		xbool[P[y]]=false;	// Flag ob Variable zur Lösung beiträgt auf "nein"
	}
	else
	{
		xbool[P[y]]=true;   // Flag ob Variable zur Lösung beiträgt auf "ja"
	}
}

/////////////////////////////////////////////////////////////////////////////
void Gauss::Pivotiere(s32 x)
/////////////////////////////////////////////////////////////////////////////
{
//
//  Abbruchbedingungen
//
	if (loesung==0) return;
	if ((x<0) || (x>=n-1)) return;
//
//  vars, die für die gesamte funktion gültig sind
//
	int y=x;
	s32 pivot_zeile=y;
	f64 pivot=A[x][y];

// #---------------#
// # IF pivot == 0 #
// #---------------#
	if (pivot == 0.0)
	{
		int ix,iy;
		s32 pivot_spalte=x;
		bool only_zero=true;

//		#-----------------------------------------------#
// 		# dann suche zuerst in y - richtung nach ersatz #
//		#-----------------------------------------------#
		for (iy=y; iy<n; iy++)
		{
			if (A[x][iy]!=0.0)
			{
	            only_zero=false;
  				pivot = A[x][iy];
			    pivot_spalte = x;
			    pivot_zeile  = iy;
				break;
			}
		}
//		#----------------------------------------------------------------------#
//		# wenn pivot immer noch null ist, dann durchsuche die komplette matrix #
//		#----------------------------------------------------------------------#
		if (only_zero==true)
		{
			for (ix=x; ix<n; ix++)
			{
				for (iy=y; iy<n; iy++)
				{
					if (A[ix][iy]!=0.0)
					{
						only_zero=false;
  						pivot = A[ix][iy];
						pivot_spalte = ix;
						pivot_zeile  = iy;
						break;
					}
				}
			}
		}

//		# --------#--------------------------------#
//		# ABBRUCH # wenn pivot immer noch null ist #
//		# --------#--------------------------------#
		if (only_zero==true)
		{
			return;
		}

//		# --------------------------------------------------------------#
//		# verschiebe neues pivot an diagonale,							#
//		# wenn koordinate pivot(x,y) gleich koordinate diagonale (x,y)  #
//		# dann werden die funktion abbgebrochen							#
//		# --------------------------------------------------------------#
		VertauscheSpalte(pivot_spalte,x);
		VertauscheZeile(pivot_zeile,y);
	}
// #-------#
// # ENDIF #
// #-------#

//	# --------------------------------------#
//	# jetzt ist pivot verschieden 0,		#
// # und es wird nach einem größeren pivot	#
//	# in der gleichen Spalte gesucht		#
//	# --------------------------------------#

	pivot_zeile=x;
	for (y=x; y<n; y++)
	{
		if ((A[x][y]>pivot) && (A[x][y]!=0.0))
		{
			pivot=A[x][y];
			pivot_zeile = y;
		}
	}
//	# --------------------------------------#
//	# wenn neues pivot > altes pivot dann	#
// # tausche zeilen, ansonsten bleibt das	#
//	# alte pivot erhalten					#
//	# --------------------------------------#
	VertauscheZeile(pivot_zeile,x);
}
/////////////////////////////////////////////////////////////////////////////
void Gauss::VertauscheZeile(int y0, s32 y1) // vertauscht auch Vektor b
/////////////////////////////////////////////////////////////////////////////
{
	if (y0==y1) return;
	if ((y0<0) || (y1<0) || (y0>n-1) || (y1>n-1)) return;
	double temp;
	s32 x;
	for (x=0; x<n; x++)
	{
		temp=A[x][y0];		// vertausche
		A[x][y0]=A[x][y1];	// Matrix
		A[x][y1]=temp;		// Elemente
	}
	temp=b[y0];		// vertausche
	b[y0]=b[y1];	// Vektor
	b[y1]=temp;		// b
}
/////////////////////////////////////////////////////////////////////////////
void Gauss::VertauscheSpalte(s32 x0, s32 x1) // vertauscht auch Vektor P
/////////////////////////////////////////////////////////////////////////////
{
	if (x0==x1) return;
	if ((x0<0) || (x1<0) || (x0>n-1) || (x1>n-1)) return;
	f64 temp;
	s32 y;
	for (y=0; y<n; y++)
	{
		temp=A[x0][y];		// vertausche
		A[x0][y]=A[x1][y];	// Matrix
		A[x1][y]=temp;		// Elemente
	}
	s32 iTemp;
	iTemp=P[x0];		// vertausche
	P[x0]=P[x1];	// Indices
	P[x1]=iTemp;     // der Unbekannten
}
/////////////////////////////////////////////////////////////////////////////
void Gauss::EliminiereSpalte(s32 x)
/////////////////////////////////////////////////////////////////////////////
{
	if (loesung==0) return;
	if (x>=n-1) return;
	s32 y,k;
	f64 m;
	// Multipliziere Zeilen unter der Diagonalen mit Factor
	for (y=x+1; y<n; y++)
	{
		// Prüfe ob Element unter Pivot <> 0.0	// KORREKTUR
		if (A[x][y]!=0.0)			// KORREKTUR
		{					// KORREKTUR
			// Factor
			m=-A[x][x]/A[x][y];
			// Factor * A
			for (k=x; k<n; k++)
			{
				A[k][y] *= m;
			}
			// Factor * b
			b[y] *= m;
		}					// KORREKTUR
	}
	// Addiere Zeilen unter Diagonalen zu Pivotzeile und speichere in Zeilen unter Diagonale
	for (y=x+1; y<n; y++)
	{
		// Prüfe ob Element unter Pivot <> 0.0	// KORREKTUR
		if (A[x][y]!=0.0)			// KORREKTUR
		{					// KORREKTUR
			// Ay = Ay + Ax
			for (k=x; k<n; k++)
			{
				A[k][y] += A[k][x];
			}
			b[y] += b[x]; //A[y][x];	// KORREKTUR
		}					// KORREKTUR
	}
}
/////////////////////////////////////////////////////////////////////
void Gauss::Solve()
/////////////////////////////////////////////////////////////////////
{
	////////////////////////////////////////////////////
	// Prüfe System auf Lösbarkeit
	////////////////////////////////////////////////////

	Check_System(0);

	////////////////////////////////////////////////////
	// Solve System
	////////////////////////////////////////////////////
	s32 ix,iy;
	for (ix=0; ix<n; ix++)
	{
	Pivotiere(ix);
	EliminiereSpalte(ix);
	Check_System(ix);
	}

	Check_System(0);

	////////////////////////////////////////////////////
	// Rückwärts-Elimination Wx=b
	////////////////////////////////////////////////////
	//
	// ( w00 w10 w20 w30 || b0 )
	// (   0 w11 w21 w31 || b1 )
	// (   0   0 w22 w32 || b2 )
	// (   0   0   0 w33 || b3 )
	//
	////////////////////////////////////////////////////
	//
	// x0 = [b0 - w30 * x3 - w20 * x2 - w10 * x1] / w00
	// x1 = [b1 - w31 * x3 - w21 * x2			] / w11
	// x2 = [b2 - w32 * x3						] / w22
	// x3 = [b3									] / w33
	//
	////////////////////////////////////////////////////
	if (loesung>0)
	{
		///////////////////
		// Berechne Lösung
		///////////////////
		f64 m;
		for (iy=n-1; iy>-1; iy--)
		{
			m=b[iy];
			if (iy<n-1)
			{
				for (ix=iy; ix<n; ix++)
				{
					m -= A[ix][iy]*x[P[ix]];
				}
			}
			if (A[iy][iy]!=0.0)	m /= A[iy][iy];
			//if (s<epsilon) s=0.0;
			x[P[iy]]=m;
		}
	}
}
/////////////////////////////////////////////////////////////////////
f64 Gauss::det( void )
/////////////////////////////////////////////////////////////////////
{
	return 0.0;
}
/////////////////////////////////////////////////////////////////////
f64 Gauss::subDet( s32 x, s32 y )
/////////////////////////////////////////////////////////////////////
{
	return 0.0;
}
/////////////////////////////////////////////////////////////////////
void Gauss::inverse( void )
/////////////////////////////////////////////////////////////////////
{

}
/////////////////////////////////////////////////////////////////////
bool Gauss::inverse_exist( void )
/////////////////////////////////////////////////////////////////////
{
	if ( !core::equals( determinante, 0.0 ) )
		return true;

	return false;
}


} // end namespace irr
