#include "Boost.h"

unsigned int Boost::strength = 0;
float Boost::velocity = 5000.0f;
Boost::Boost()
{
}
void Boost::addStrength(const unsigned int x)
{
	strength += x;
}
float Boost::Velocity()
{
	velocity += (strength * velocity / 20);
	strength = 0;
	if (velocity > 15000.0f) velocity = 15000.0f;
	return velocity;
}
unsigned int Boost::Transparency()
{
	return static_cast<int>(128- (velocity - 5000.0f) * 128 / 10000);
}
Boost::~Boost()
{
}
