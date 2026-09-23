#include <stdio.h>
#include <stdlib.h>
#include "vdt/vdt.h"

float atan2_approximation1(float y, float x);
float atan2_approximation2(float y, float x);



float atan2_approximation1(float y, float x)
{
    //http://pubs.opengroup.org/onlinepubs/009695399/functions/atan2.html
    //Volkan SALMA

    const float quarters_pi = vdt::details::VDT_PI_4_F;
    const float three_quarters_pi = 3.0f * vdt::details::VDT_PI_F / 4.0f;
	float r, angle;
	float abs_y = vabs(y) + 1e-10f;      // kludge to prevent 0/0 condition
	if ( x < 0.0f )
	{
		r = (x + abs_y) / (abs_y - x);
		angle = three_quarters_pi;
	}
	else
	{
		r = (x - abs_y) / (x + abs_y);
		angle = quarters_pi;
	}
	angle += (0.1963f * r * r - 0.9817f) * r;
	if ( y < 0.0f )
		return( -angle );     // negate if in quad III or IV
	else
		return( angle );


}


// |error| < 0.005
float atan2_approximation2( float y, float x )
{
        const float pi  = vdt::details::VDT_PI_F ;
        const float half_pi = vdt::details::VDT_PI_2_F ;

        if ( x == 0.0f )
	{
		if ( y > 0.0f ) return half_pi;
		if ( y == 0.0f ) return 0.0f;
		return -half_pi;
	}
	float atan;
	float z = y/x;

	if ( vabs( z ) < 1.0f )
	{
		atan = z/(1.0f + 0.28086f*z*z);
		if ( x < 0.0f )
		{
			if ( y < 0.0f ) return atan - pi;
			return atan + pi;
		}
	}
	else
	{
		atan = half_pi - z/(z*z + 0.28086f);
		if ( y < 0.0f ) return atan - pi;
	}
	return atan;
}
