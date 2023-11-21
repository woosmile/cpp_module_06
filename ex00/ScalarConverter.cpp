#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(): _type(0)
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other): _type(other._type)
{
}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter &other)
{
	if (this != &other)
	{
		_type = other._type;
	}
	return (*this);
}

void	ScalarConverter::checkType(const char *av)
{
	int	i = 0;

	if (av == NULL)
		throw (ScalarConverter::NotaNumber());
	if (std::isalpha(av[i]) > 0)
	{
		if (av[i + 1] == '\0')
			_type = CHAR;
		else
			throw (ScalarConverter::NotaNumber());
	}
	else if (std::isdigit(av[i]) > 0)
	{
		_type = INT;
		i++;
		while (av[i] != '\0')
		{
			if (av[i] == '.')
			{
				if (_type >= FLOAT)
					throw (ScalarConverter::NotaNumber());
				else
					_type = DOUBLE;
				i++;
				continue;
			}
			if (av[i] == 'f')
			{
				if (_type < FLOAT || av[i + 1] != '\0')
					throw (ScalarConverter::NotaNumber());
				else
					_type = FLOAT;
				i++;
				continue;
			}
			if (std::isdigit(av[i]) == 0)
				throw (ScalarConverter::NotaNumber());
			i++;
		}
	}
	else
	{
		throw (ScalarConverter::NotaNumber());
	}
}

int	ScalarConverter::getType() const
{
	return (_type);
}

void	ScalarConverter::converter(const char *av)
{
	checkType(av);
}

const char* ScalarConverter::NotaNumber::what() const throw()
{
	return ("Not a Number");
}