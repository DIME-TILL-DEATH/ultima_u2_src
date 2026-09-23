#include <iostream>
#include <fstream>
#include <math.h>

const size_t N = 1024*10 ;

int main()
{
	std::ofstream outfile;
	outfile.open ("data.txt");
	outfile << "typedef struct\n{\n\tfloat s;\n\tfloat c;\n} sincos_point_t ;" << std::endl ;
	outfile << "const sincos_point_t sincos_table[]={" << std::endl ;
	outfile.precision(16);	
	for ( int i = 0 ; i < N ; i++ )
	{
		outfile << "\t{" <<  sin( 2.0*M_PI * i / N  ) << "," << cos( 2.0*M_PI * i / N  ) << "}," <<std::endl ;
	}
	outfile << "};" << std::endl ;
 	outfile.close();
	
}
