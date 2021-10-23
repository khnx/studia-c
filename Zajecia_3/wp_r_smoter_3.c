#include "stdio.h"
#include "stdlib.h"

/* 
	* Count a sum with specified parameters
	* Domain boundaries: first min, then max;
	* Domain step
	* Function error
	* Range begin; for sum
*/
float doSum(float [], float, float, int);

int main(void)
{
  // Sum consts
  const float error = .000016; // Function error
  const float step = .01; // Domain step
  const float domain[] = { 3., 4. }; // Domain boundaries

  float sum = doSum(domain, step, error, 1);

  return 0;
}

float doSum(float domain[], float step, float error, int k) {

	float sum;

	for (float i = domain[0]; i < domain[1]; i++) {



	}

	return;
}

float countSin() {



	return;
}

float countCos() {

	

	return;
}