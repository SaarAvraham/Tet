#include "GlobalFunctions.h"

 char upperToLowerCase(char a)
{ 
	return a + LOWER_TO_UPPERCASE; 
}
 bool isUpperCase(char a)
{ 
	return (((a >= UPPER_CASE_BOTTOM) && (a <= UPPER_CASE_TOP)));
}