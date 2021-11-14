/* ***** LIBRARIES ***** */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ***** PROTOTYPES ***** */
/* 
	* Count a sum with specified parameters
	* Parameters:
	* Domain boundaries: first min, then max,
	* domain step, function error, range begin
*/
double doSum(double [], double, double, int);

/*
	* Count a mathematical function with specified parameters
	* Parameters:
	* Domain value, iteration number specifier
*/
double countFunc(double x, int k);