/// ----------------------------

/// BASIC DIALECT MACROS

/// ----------------------------

#ifdef BEGIN_FUNCTION
	#undef BEGIN_FUNCTION
#endif // BEGIN_FUNCTION

#ifndef BEGIN_FUNCTION
	#define BEGIN_FUNCTION {
#endif // BEGIN_FUNCTION

#ifdef END_FUNCTION
	#undef END_FUNCTION
#endif // END_FUNCTION

#ifndef END_FUNCTION
	#define END_FUNCTION }
#endif // END_FUNCTION

/// ----------------------------

#ifdef IF
	#undef IF
#endif // IF

#ifndef IF
	#define IF if (
#endif // IF

#ifdef THEN
	#undef THEN
#endif // THEN

#ifndef THEN
	#define THEN ) {
#endif // THEN

#ifdef ENDIF
	#undef ENDIF
#endif // ENDIF

#ifndef ENDIF
	#define ENDIF }
#endif // ENDIF

#ifdef ELSE
	#undef ELSE
#endif // ELSE

#ifndef ELSE
	#define ELSE } else {
#endif // ELSE

#ifdef ELIF
	#undef ELIF
#endif // ELIF

#ifndef ELIF
	#define ELIF } else if (
#endif // ELIF

/// ----------------------------

#ifdef WHILE
	#undef WHILE
#endif // WHILE

#ifndef WHILE
	#define WHILE while (
#endif // WHILE

#ifdef END_WHILE
	#undef END_WHILE
#endif // END_WHILE

#ifndef END_WHILE
	#define END_WHILE }
#endif // END_WHILE

/// ----------------------------

#ifdef AND
	#undef AND
#endif // AND

#ifndef AND
	#define AND &&
#endif // AND

#ifdef OR
	#undef OR
#endif // OR

#ifndef OR
	#define OR ||
#endif // OR

/// ----------------------------

#ifdef BEGIN
	#undef BEGIN
#endif // BEGIN

#ifndef BEGIN
	#define BEGIN {
#endif // BEGIN

#ifdef END
	#undef END
#endif // END

#ifndef END
	#define END }
#endif // END