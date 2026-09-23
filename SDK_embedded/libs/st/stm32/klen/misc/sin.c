
/*
int get_shift (int qantuty)
{
  int i = 0 ;
  int div = 45 ;
  while ( qantuty / div > 1 )
    {
       div *= 2 ;
       i+= 2 ;
    }
  return i ;
}



sin:
  int quantity = 45 ;
  int shift = get_shift (quantity) ;

  int t = 0  ; // time
  while (t<2*quantity)
  {
	int arg =   t % quantity ;
	int sign =  t / quantity ;
	s[t] = (arg * ( arg - quantity)) >> shift ;
	if ( sign & 0x1 )
		s[t] = -s[t];
   t++ ;
  }
  */
