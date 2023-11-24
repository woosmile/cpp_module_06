#include "Serializer.hpp"
#include <iostream>

int main(void)
{
	Data		origin;
	Data		*deserialize;
	uintptr_t	addr;

	origin.var = 10;

	addr = Serializer::serialize(&origin);

	std::cout << "Origin Addr : " << &origin << std::endl;
	std::cout << "Serialize Addr : " << addr << std::endl;

	deserialize = Serializer::deserialize(addr);

	std::cout << "Deserialize Addr : " << deserialize << std::endl;

	return (0);
}