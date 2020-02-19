#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int _round(float number) {
	return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

// Trig lookup tables
float sin_t[360];
float cos_t[360];

double mysin(double x, int n)
{
   double t = x;
   double sine = t;
   for ( int a=1; a<n; ++a)
   {
      double mult = -x*x/((2*a+1)*(2*a));
      t *= mult;
      sine += t;
   }
   return sine;
}

void setup_trig_lookup_tables() {
	for (int i = 0; i < 360; i++) {
		float rad_s = degToRad(i);
		float rad_c = degToRad((i + 90) % 360);
		sin_t[i] = mysin(rad_s, 10);
		cos_t[i] = mysin(rad_c, 10);
	}
}
