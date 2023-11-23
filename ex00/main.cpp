#include "ScalarConverter.hpp"

int main(int ac, char **av)
{
	(void)ac;
	
	try
	{
		ScalarConverter::converter(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}