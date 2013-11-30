// y*log2(x)
// To set a specific set y to 1/log2(base) 
#if defined(_MSC_VER)

__forceinline __declspec(naked) float __cdecl log2(float x, float y=1.0f)
{
    __asm fld [esp+8];  // push y onto stack
    __asm fld [esp+4];  // push x onto the stack
    __asm fyl2x;        // calculate 
    __asm retn;         // exit function
}

#elif defined (__GNUC__)

__inline float log2(float x, float y=1.0f)
{
    float result;
    asm ("fyl2x" : "=t" (result) : "0" (x), "u" (y));
    return result;
}

#else

__inline float log2(float x, float y=1.0f)
{
    static const double _1_div_log_2 = 1.0/log(2.0);
    return (float)(_1_div_log_2*log(x)*y);
}

#endif

inline float ln(float x)
{
    static const float y = 0.69314718055994530941f; // 1/log2(e);
    return log2(x, y);
}

inline void __fastcall SinCos4(float angle,float & s,float & c) {
    __asm {
        fld  angle                      //Lädt den angle auf den floating point register stack
        fmul dword ptr[ToRadians]       //Multipliziert den winkel mit ToRadians um ihn ins Bogenmaß umzurechnen
        //Dies führt die eigentliche Berechnung durch und packt den cosinus ins ecx register und den sinus ins edx register
        fsincos                         
        mov ecx,[c]                     //Kopiert den berechneten cosinus in den cosinus parameter
        mov edx,[s]                     //Kopiert den berechneten sinus in den sinus parameter
        fstp  DWORD PTR[ecx]            //Räumt das verwendete ecx Register wieder auf
        fstp  DWORD PTR[edx]            //Räumt das verwendete edx Register wieder auf
    }
}

inline void fastSinCos(float radians,float & s,float & c) {

  __asm {

    fld   radians

    fsincos

    mov ecx,[c]

    mov edx,[s]

    fstp  DWORD PTR[ecx]

    fstp  DWORD PTR[edx]

  } // __asm

} // fastSinCos


void normalize(Vec3 * v) {
  __asm {
    mov   eax,v
    movss xmm0,[eax]Vec3.x
    movss xmm1,[eax]Vec3.y
    movss xmm2,[eax]Vec3.z

    mulss xmm0,xmm0
    mulss xmm1,xmm1
    mulss xmm2,xmm2

    addss xmm0,xmm1
    addss xmm2,xmm0

    movss xmm4,[eax]Vec3.x
    movss xmm5,[eax]Vec3.y
    movss xmm6,[eax]Vec3.z

    rsqrtss xmm2,xmm2

    mulss xmm4,xmm2
    mulss xmm5,xmm2
    mulss xmm6,xmm2

    movss [eax]Vec3.x,xmm4
    movss [eax]Vec3.y,xmm5
    movss [eax]Vec3.z,xmm6
  } // asm
} // normalize


// Intel's sqrtInverse:
inline __declspec(naked) float __fastcall _sqrtInverse(float a) {
  __asm {
    mov   eax,0be6eb508h
    mov   DWORD PTR [esp-12],03fc00000h // 1.5 on the stack
    sub   eax, DWORD PTR [esp+4]        // a
    sub   DWORD PTR [esp+4],800000h     // a/2 a=Y0
    shr   eax,1                         // first approx. in eax=R0
    mov   DWORD PTR [esp-8],eax

    fld   DWORD PTR [esp-8]              // r
    fmul  st,st                          // r*r
    fld   DWORD PTR [esp-8]              // r
    fxch  st(1)
    fmul  DWORD PTR [esp+4]              // a ; r*r*y0
    fld   DWORD PTR [esp-12]             // load 1.5
    fld   st(0)
    fsub  st,st(2)                       // r1 = 1.5 - y1
                                         // x1 = st(3)
                                         // y1 = st(2)
                                         // 1.5 = st(1)
                                         // r1 = st(0)

    fld   st(1)
    fxch  st(1)
    fmul  st(3),st	                 // y2=y1*r1*...
    fmul  st(3),st	                 // y2=y1*r1*r1
    fmulp st(4),st                       // x2=x1*r1
    fsub  st,st(2)                       // r2=1.5-y2
                                         // x2=st(3)
                                         // y2=st(2)
                                         // 1.5=st(1)
                                         // r2 = st(0)

    fmul  st(2),st	                 // y3=y2*r2*...
    fmul  st(3),st                       // x3=x2*r2
    fmulp st(2),st	                 // y3=y2*r2*r2
    fxch  st(1)
    fsubp st(1),st	                 // r3= 1.5 - y3
                                         // x3 = st(1)
                                         // r3 = st(0)
    fmulp  st(1),st
    ret 4
  }
}

// From http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
inline flt sqrtInverse2(flt n) { // Appears slower than ASM above.
  flt halfn = .5f*n;
  int i = *(int *)&n;
  i = 0x5f375a86 - (i>>1); // 0x5f3759df: original number.
  n = *(flt *)&i;
  n = n*(1.5f-halfn*n*n);
  return n;
} // sqrtInverse2

inline flt sqrtInverse(flt n) { if (n > RSQR(1.f/6.5192024e+018)) return _sqrtInverse(n); else return 0.f; }
inline flt rSqrt(flt n) { return n*sqrtInverse(n); }

// SSE

inline flt sqrtInverse(flt n) {
  __asm  {
    movss   xmm0,n
    rsqrtss xmm0,xmm0
    movss   n,   xmm0
  }
  return n;
} // sqrtInverse

inline bool lessThanOrEqualZero(flt f) {
  return (long &)f <= 0;
} // lessThanOrEqualZero

inline float rSqrt(float n) {
  //  if (n <= 0.f) return 0.f; // 859
  if (lessThanOrEqualZero(n)) return 0.f; // 844
  __asm {
    rsqrtss xmm0,n
    mulss   xmm0,n
    movss   n,xmm0
  }
  return n;
}

inline float ASMsqrt(float src)
{
	float t;
	_asm
	{
		fld src
		fsqrt
		fstp t
	}
	return t;
}

inline flt rSqrt(flt n) { // 875
  __asm  {
    movss   xmm0,n
//    rsqrtss xmm0,xmm0
//    rcpss   xmm0,xmm0 // The rcpss version might be slightly faster. Each version of SSE sqrt has about the same precision.
    sqrtss  xmm0,xmm0
    movss   n,   xmm0
  }
  return n;
} // rSqrt

#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>

static const int Count = 50000000;

typedef float (*tSqrtFunction) (float);

// From http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
inline float sqrtInverse2(float n)
{
  float halfn = 0.5f * n;
  int i = *(int*) &n;
  i = 0x5f375a86 - (i >> 1); // 0x5f3759df: original number.
  n = *(float*) &i;
  n = n * (1.5f - halfn * n * n);
  return 1.0f / n;
} 

//SSE1
float invsqrt(float n)
{
	_asm
	{
		movss   xmm0, n;
		rsqrtss xmm0, xmm0;
		movss   n, xmm0;
	}

	return 1.0f / n;
}

//SSE2
float SSE2sqrt(float src)
{
	float t;

	_asm
	{
		movupd xmm0, src;
		movupd xmm1, t;
		sqrtss xmm1, xmm0;
		movupd t, xmm1;
	}
	return t;
}

//ASM
float ASMsqrt(float src)
{
	float t;

	_asm
	{
		fld src;
		fsqrt;
		fstp t;
	}
	return t;
}

inline void TestFunction(const std::wstring& Name, tSqrtFunction SqrtFunction, int Count)
{
	float f;
	DWORD StartTime, EndTime, TotalTime;

	StartTime = GetTickCount();
	for (int i = 0;i < Count;i++)
	{
		f = SqrtFunction(10.f);
	}
	EndTime = GetTickCount();
	TotalTime = EndTime - StartTime;

	std::wcout << L"Function " << Name << L" f*f=" << f * f << L" took: " << TotalTime << std::endl;
}

int main(int argc, char* argv[])
{
	std::wcout << std::setprecision(10) << std::endl;

	TestFunction(L"sqrtf", sqrtf, Count);
	TestFunction(L"ASMsqrt", ASMsqrt, Count);
	TestFunction(L"invsqrt", invsqrt, Count);
	//TestFunction(L"SSE2sqrt", SSE2sqrt, Count);
	TestFunction(L"sqrtInverse2", sqrtInverse2, Count);

	return 0;
}



The results i got were:
Function sqrtf f*f=10 took: 1203
Function ASMsqrt f*f=10 took: 625
Function invsqrt f*f=10.0003 took: 641
Function sqrtInverse2 f*f=10.0344 took: 1125