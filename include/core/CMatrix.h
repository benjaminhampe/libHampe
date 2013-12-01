#ifndef __IRR_C_DYNAMIC_RECTANGLE_MATRIX_H__
#define __IRR_C_DYNAMIC_RECTANGLE_MATRIX_H__

#include <irrlicht.h>
#include <cstdlib>
#include <cstdio>

namespace irr
{
namespace core
{
    class CMatrix : public IReferenceCounted
	{
	public:
		template <class T> T** ALLOC_2D_ARRAY(u32 rows, u32 cols)
		{
			// fill with zeros with memset
			const u32 byte_count = (u32)sizeof(T);

			// allocate memory for vector that stores vectors of rows
			T **p=new T*[rows];

			// allocate memory for each row vector
			for (u32 y=0; y<rows; y++)
			{
				p[y]=new T[cols];
			}

			memset( dynamic_cast<T**>(p[0][0]), 0, byte_count );

			// bytesize = sizeof(T);

		//	// sizeof(T)
		//	for (y=0; y<rows; y++)
		//		for (x=0; x<cols; x++)
		//			p[y][x]=T(0);


			return p;
		}

	private:
		/// default constructor ( private = forbidden to be called -> force to always call value-ctr of class )
		CMatrix( ) {};

	public:
		/// value constructor
		CMatrix( u32 rows, u32 cols );

		/// copy constructor
		CMatrix( const CMatrix& other );

		/// destructor
		virtual ~CMatrix();

		/// clear all
		void clear();

		/// fill with constants and random numbers
		virtual void fill(f32 value);

		virtual void fillRandom(f32 minRandom, f32 maxRandom);

        virtual void fillRandomNormalized();

		virtual core::vector2df getMinMax() const;

		virtual bool empty()
		{
			return false;
		}

		/// math functions Part I
//		CMatrix& toIdentity();
//		bool isIdentity();

				/// create IdentityMatrix ( all zero but diagonale-elements filled with 1, Einheitsmatrix E / IdentityMatrix I == neutral element of matrix-multiplication )
		virtual void makeIdentity()
		{
			fill( 0.0f );

			u32 min_xy = core::min_<u32>( Rows, Cols );

			for (u32 diagonale=0; diagonale<min_xy; diagonale++)
			{
				Data[diagonale][diagonale] = 1.0f;
			}

			IsIdentity = true;
		}

		/// allocator ( reserve new memory if needed for new matrix with dimension rows x cols
		bool resize( u32 rows, u32 cols, bool keepData = true, bool canShrink = true );

		/// copy function
		CMatrix& assign( const CMatrix& other );

		/// copy operator ( copy content of existing class CMatrix to this class instance )
		virtual CMatrix& operator= ( const CMatrix& other );

		/// clone function ( create new instance of CMatrix with same content as this class instance )
		virtual CMatrix clone() const;

		/// get access ( public ) to raw data
		virtual f32** getData() { return Data; }

		/// get Number of rows i have (y-dir)
		virtual u32 getRows() const { return Rows; }

		/// get Number of columns i have (x-dir)
		virtual u32 getCols() const { return Cols; }

		/// get Product of Rows and Colums for linear memory access, its elementcount not the bytesize of allocated mem
		virtual u32 getSize() const { return Size; }

		/// get Matrix-Size
		virtual core::dimension2du getDimension() const
		{
			return core::dimension2du( Rows, Cols );
		}

		/// get my Name
		virtual core::stringc getName() const
		{
			return Name;
		}

		/// get my Name
		virtual void setName( const core::stringc& name = "CMatrix" )
		{
			#ifdef _DEBUG
			printf( "CMatrix::setName(\"%s\")\n", name.c_str() );
			#endif // _DEBUG

			Name = name;
		}

		/// set row-data ( replace ) with array-values
		template <class T>
		bool setRow( u32 row, const T* data, u32 elem_count, f32 fillSpace = 0.0f )
		{
			if (!data)
			{
				printf("CMatrix::fillRow() - ERROR Cant set row of empty CMatrix, return false.\n");
				return false;
			}

			if (row >= Rows)
				return false;

			u32 i_max = core::min_<u32>( elem_count, Cols);

			T* p = const_cast<T*>(data);

			for (u32 i=0; i<i_max; i++)
			{
				if (p)
				{
					f32 value = (f32)(*p);
					Data[row][i] = value;
					p++;
				}
				else
				{
					break;
				}
			}

			if (i_max < Cols)
			{
				for (u32 i=i_max; i<Cols; i++)
				{
					Data[row][i] = fillSpace;
				}
			}

			return true;
		}

		/// set row-data ( replace ) with array-values
		template <class T>
		bool setRow( u32 row, const core::array<T>& data, bool bFillBounds = false, f32 fillSpace = 0.0f )
		{
			if (!Data)
			{
				printf("CMatrix::fillRow() - ERROR Cant set row of empty CMatrix, return false.\n");
				return false;
			}

			if (row >= Rows)
				return false;

			u32 i_max = core::min_<u32>( data.size(), Cols);

			for (u32 i=0; i<i_max; i++)
			{
				Data[row][i] = (f32)data[i];
			}

			if (bFillBounds)
			{
				if (i_max < Cols)
				{
					for (u32 i=i_max; i<Cols; i++)
					{
						Data[row][i] = fillSpace;
					}
				}
			}
			return true;
		}

		/// CMatrix IO
		virtual core::stringc toString() const;

		virtual void print( FILE* out ) const;

		virtual bool load( const core::stringc& filename ) const;

		virtual bool save( const core::stringc& filename ) const;

				/// element access functions
		virtual f32 getElement(u32 row, u32 col) const;

		virtual f32 getElement(u32 index) const;

		virtual bool setElement(u32 row, u32 col, f32 element);

		virtual bool setElement(u32 index, f32 element);

		/// element access operators
		// virtual const f32& operator() (u32 index) const;
		// virtual f32& operator() (u32 index);
		// virtual const f32& operator() (u32 row, u32 col) const;
		// virtual f32& operator() (u32 row, u32 col);

		/// exchange rows circularly
		virtual bool swapRows( u32 row_a, u32 row_b );

		/// exchange rows circularly
		virtual bool shiftRow();

		/// exchange rows circularly
		virtual bool shiftRows( s32 rows );

		/// create Software-image
		virtual video::IImage* createImage( ) const;

		/// create Software-image
		virtual video::IImage* createHeightMap( ) const
		{
			return this->createImage();
		}

		/// create Hardware-image
		virtual video::ITexture* createTexture( video::IVideoDriver* driver ) const;


		/// boolean operators
		virtual bool operator==(const CMatrix& other);
		virtual bool operator!=(const CMatrix& other);

//
//		virtual f32 det() const;
//		virtual f32 subMatrix( u32 y, u32 x ) const;
//		virtual f32 subDet( u32 y, u32 x ) const;

		/// arithmetic operators
		CMatrix& operator+= ( const CMatrix& other );
		CMatrix& operator-= ( const CMatrix& other );
//		CMatrix operator*= ( const CMatrix& other );
//		CMatrix operator/= ( const CMatrix& other );
//		CMatrix operator* ( const CMatrix& other ) const;
//		CMatrix operator/ ( const CMatrix& other ) const;
//
		/// scale operator '*'
		template <class T>
		CMatrix& operator* ( const T& value )
		{
			for (u32 y=0; y<Rows; y++)
			{
				for (u32 x=0; x<Cols; x++)
				{
					Data[y][x] = Data[y][x] * (f32)value;
				}
			}
			return *this;
		}

		/// scale operator '/'
		template <class T>
		CMatrix& operator/ ( const T& value )
		{
			const f32 v = (f32)value;

			if (!core::equals( v, 0.0f ))
			{
				for (u32 y=0; y<Rows; y++)
				{
					for (u32 x=0; x<Cols; x++)
					{
						Data[y][x] = Data[y][x] / v;
					}
				}
			}

			return *this;
		}

		/// translation operator '+'
		template <class T>
		CMatrix& operator+ ( const T& value )
		{
			for (u32 y=0; y<Rows; y++)
			{
				for (u32 x=0; x<Cols; x++)
				{
					Data[y][x] = Data[y][x] + (f32)value;
				}
			}

			return *this;
		}

		/// translation operator '-'
		template <class T>
		CMatrix& operator- ( const T& value )
		{
			for (u32 y=0; y<Rows; y++)
			{
				for (u32 x=0; x<Cols; x++)
				{
					Data[y][x] = Data[y][x] - (f32)value;
				}
			}
			return *this;
		}

	private:
		u32 Rows;	/// number of rows ( y-direction )
		u32 Cols;	/// number of columns ( x-direction )
		u32 Size;	/// number of elements in matrix ( == Rows * Cols )
		f32** Data;	/// pointer to 2d field == array of rows ( each row is an arrays with "Cols" elements )
		core::stringc Name;
		bool IsIdentity;
		bool IsDeterminantDirty;
		u32 Rank; // ( Rank always lower or equal then the minimum of (Rows,Cols) == number of linear independant basevectors)
		f32 Determinant;

	};

} // end namespace core

} // end namespace irr

#endif // MATRIX_H
