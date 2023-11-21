#include "ScalarConverter.hpp"

int main(int ac, char **av)
{
	(void)ac;

	try
	{
		ScalarConverter	test;

		test.converter(av[1]);
		std::cout << test.getType();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}