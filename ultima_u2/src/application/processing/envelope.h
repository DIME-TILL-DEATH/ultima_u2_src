#include "appdefs.h"

#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_

class Envelope
{
public:
	Envelope(){};

	inline float process(float env, float coef_attack, float coef_release)
	{
		if(env > m_envdB)
			m_envdB = env + coef_attack * (m_envdB - env);
		else
			m_envdB = env + coef_release * (m_envdB - env);

		return m_envdB;
	}

	float DC_OFFSET = 1.0E-25;
	float m_envdB = DC_OFFSET;
private:

};

#endif /* _ENVELOPE_H_ */
