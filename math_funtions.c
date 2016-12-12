/* Just a random program to sum sin(pi), cos(pi) and
 * tan(pi) a zillion times */
#include <math.h>

#define PI acos(-1.0)

int main(){

	unsigned long long i;
	double sine, cosine, tangent;
	double sum;

	for(i = 0; i < 18446744073; i++){
		sine = sin(PI);
		cosine = cos(PI);
		tangent = tan(PI);

		sum = sine + cosine + tangent;
	}

	return 0;

}
