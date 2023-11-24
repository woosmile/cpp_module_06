#include "generate.hpp"

Base*	generate(void)
{
	int random;

	srand(static_cast<unsigned int>(time(NULL)));
	random = rand() % 3;

	switch(random)
	{
		case 0:
			return (new A());
		case 1:
			return (new B());
		case 2:
			return (new C());
		default:
			return (new A());
	}
	return (new A());
}