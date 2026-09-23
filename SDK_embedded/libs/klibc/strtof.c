int isspace(int c);

/*  ---------- EXAMPLE -----------
int main ()
{
  char szOrbits[] = "686.97 365.24";
  char* pEnd;
  float f1, f2;
  f1 = strtof (szOrbits, &pEnd);
  f2 = strtof (pEnd, NULL);
  printf ("One martian year takes %.2f Earth years.\n", f1/f2);
  return 0;
}
*/

float strtof(const char* s, char** endptr) {
    register const char*  p     = s;
    register float        value = 0.;
    int                   sign  = +1;
    float                 factor;
    unsigned int          expo;

    while ( isspace( (int)*p ) )
        p++;

    switch (*p) {
    case '-': sign = -1; p++; break ;
    case '+': p++;
    default : break;
    }

    while ( (unsigned int)(*p - '0') < 10u )
        value = value*10 + (*p++ - '0');

    if ( *p == '.' ) {
        factor = 1.;

        p++;
        while ( (unsigned int)(*p - '0') < 10u ) {
            factor *= 0.1;
            value  += (*p++ - '0') * factor;
        }
    }

    if ( (*p | 32) == 'e' ) {
        expo   = 0;
        factor = 10.L;

        switch (*++p) {                 // ja hier weiß ich nicht, was mindestens nach einem 'E' folgenden MUSS.
        case '-': factor = 0.1; p++; break;
        case '+': p++;
                  break;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                  break;
        default : value = 0.L;
                  p     = s;
                  goto done;
        }

        while ( (unsigned int)(*p - '0') < 10u )
            expo = 10 * expo + (*p++ - '0');

        while ( 1 ) {
            if ( expo & 1 )
                value *= factor;
            if ( (expo >>= 1) == 0 )
                break;
            factor *= factor;
        }
    }

done:
    if ( endptr != (void*) 0 )
        *endptr = (char*)p;

    return value * sign;
}
