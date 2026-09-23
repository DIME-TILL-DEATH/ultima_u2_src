#include "appdefs.h"

#ifndef SRC_APPLICATION_ATTRELENV_H_
#define SRC_APPLICATION_ATTRELENV_H_

class AttRelEnv {
public:
	AttRelEnv(){};
	virtual ~AttRelEnv(){};

	inline float attrel(float env,float coef_at,float coef_rel)
	{
		if ( env > envdB_ )envdB_ = env + coef_at * ( envdB_ - env );
		else envdB_ = env + coef_rel * ( envdB_ - env );

		return envdB_;
	}

	float DC_OFFSET = 1.0E-25;
	float envdB_ = DC_OFFSET;

private:

};

#endif /* SRC_APPLICATION_ATTRELENV_H_ */
