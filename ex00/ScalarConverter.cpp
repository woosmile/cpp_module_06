#include "ScalarConverter.hpp"

int ScalarConverter::_type = 0;
int ScalarConverter::_precision_len = 1;

char ScalarConverter::_var_char = 0;
int ScalarConverter::_var_int = 0;
float ScalarConverter::_var_float = 0;
double ScalarConverter::_var_double = 0;

int ScalarConverter::_convert_char = SUCCESS;
int ScalarConverter::_convert_int = SUCCESS;
int ScalarConverter::_convert_float = SUCCESS;

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return (*this);
}

void	ScalarConverter::checkType(const char *av)
{
	int	i = 0;

	if (av == NULL)
	{
		throw (ScalarConverter::Impossible());
	}
	else if (std::strcmp(av, "inf") == 0 || std::strcmp(av, "+inf") == 0 || \
		std::strcmp(av, "inff") == 0 || std::strcmp(av, "+inff") == 0)
	{
		throw (ScalarConverter::PositiveInfinity());
	}
	else if (std::strcmp(av, "-inf") == 0 || std::strcmp(av, "-inff") == 0)
	{
		throw (ScalarConverter::NegativeInfinity());
	}
	else if (std::strcmp(av, "nan") == 0)
	{
		throw (ScalarConverter::NotaNumber());
	}
	
	if (std::isdigit(av[i]) > 0 || av[i] == '-' || av[i] == '+')
	{
		_type = INT;
		i++;
		while (av[i] != '\0')
		{
			if (av[i] == '.')
			{
				if (_type >= FLOAT)
					throw (ScalarConverter::Impossible());
				else
					_type = DOUBLE;
				i++;
				continue;
			}
			if (av[i] == 'f')
			{
				if (_type < FLOAT || av[i + 1] != '\0')
					throw (ScalarConverter::Impossible());
				else
					_type = FLOAT;
				i++;
				continue;
			}
			if (std::isdigit(av[i]) == 0)
				throw (ScalarConverter::Impossible());
			i++;
		}
		if (av[i - 1] == '-' || av[i - 1] == '+')
			_type = CHAR;
	}
	else
	{
		if (av[i + 1] == '\0')
			_type = CHAR;
		else
			throw (ScalarConverter::Impossible());
	}
}

int	ScalarConverter::getType()
{
	return (_type);
}

void	ScalarConverter::convertChar(const char *av)
{
	_var_char = av[0];
	_var_int = static_cast<int>(_var_char);
	_var_float = static_cast<float>(_var_char);
	_var_double = static_cast<double>(_var_char);
}

void	ScalarConverter::convertInt(const char *av)
{
	long	_var_long = std::strtol(av, NULL, 10);
	
	if (_var_long < std::numeric_limits<int>::min() || _var_long > std::numeric_limits<int>::max() || errno == ERANGE)
		throw (ScalarConverter::Impossible());
	_var_int = std::atoi(av);
	if (_var_int < std::numeric_limits<char>::min() || _var_int > std::numeric_limits<char>::max())
		_convert_char = FAILURE;
	else 	
	{
		_var_char = static_cast<char>(_var_int);
		if (!((_var_char >= 9 && _var_int <= 13) || (_var_char >= 32 && _var_int <= 126)))
			_convert_char = NOPRINT;
	}
	_var_float = static_cast<float>(_var_int);
	_var_double = static_cast<double>(_var_int);
}

void	ScalarConverter::convertFloat(const char *av)
{
	double	_var_double_temp = std::strtod(av, NULL);

	if (_var_double_temp < -std::numeric_limits<float>::max() || _var_double_temp > std::numeric_limits<float>::max() || errno == ERANGE)
		throw (ScalarConverter::Impossible());
	_var_float = static_cast<float>(std::strtod(av, NULL));
	if (_var_float < std::numeric_limits<char>::min() || _var_float > std::numeric_limits<char>::max())
		_convert_char = FAILURE;
	else 	
	{
		_var_char = static_cast<char>(_var_float);
		if (!((_var_char >= 9 && _var_int <= 13) || (_var_char >= 32 && _var_int <= 126)))
			_convert_char = NOPRINT;
	}
	if (_var_float < std::numeric_limits<int>::min() || _var_float > std::numeric_limits<int>::max())
		_convert_int = FAILURE;
	else 	
		_var_int = static_cast<int>(_var_float);
	_var_double = static_cast<double>(_var_float);
}

void	ScalarConverter::convertDouble(const char *av)
{
	_var_double = std::strtod(av, NULL);
	if (errno == ERANGE)
		throw (ScalarConverter::Impossible());
	if (_var_double < std::numeric_limits<char>::min() || _var_double > std::numeric_limits<char>::max())
		_convert_char = FAILURE;
	else 	
	{
		_var_char = static_cast<char>(_var_double);
		if (!((_var_char >= 9 && _var_int <= 13) || (_var_char >= 32 && _var_int <= 126)))
			_convert_char = NOPRINT;
	}
	if (_var_double < std::numeric_limits<int>::min() || _var_double > std::numeric_limits<int>::max())
		_convert_int = FAILURE;
	else 	
		_var_int = static_cast<int>(_var_double);
	if (_var_double < -std::numeric_limits<float>::max() || _var_double > std::numeric_limits<float>::max())
		_convert_float = FAILURE;
	else
		_var_float = static_cast<float>(_var_double);
}

void	ScalarConverter::printValue(const char *av)
{
	if (_convert_char == SUCCESS)
		std::cout << "char: \'" << _var_char << '\'' << std::endl;
	else if (_convert_char == NOPRINT)
		std::cout << "char: Non displayable" << std::endl;
	else if (_convert_char == FAILURE)
		std::cout << "char: impossible" << std::endl;
	
	if (_convert_int == SUCCESS)
		std::cout << "int: " << _var_int << std::endl;
	else if (_convert_int == FAILURE)
		std::cout << "int: impossible" << std::endl;

	if (_type == FLOAT || _type == DOUBLE)
	{
		std::string	num_str = av;
		_precision_len = num_str.length() - num_str.find('.') - (_type == FLOAT) - 1;
	}
	std::cout.precision(_precision_len);
	std::cout << std::fixed;

	if (_convert_float == SUCCESS)
		std::cout << "float: " << _var_float << "f" << std::endl;
	else if (_convert_float == FAILURE)
		std::cout << "float: impossible" << std::endl;

	std::cout << "double: " << _var_double << std::endl;
}

void	ScalarConverter::converter(const char *av)
{
	try
	{
		checkType(av);
		switch(_type)
		{
			case CHAR:
			{
				convertChar(av);
				break;
			}
			case INT:
			{
				convertInt(av);
				break;
			}
			case FLOAT:
			{
				convertFloat(av);
				break;
			}
			case DOUBLE:
			{
				convertDouble(av);
				break;
			}
			default:
			{
				throw (ScalarConverter::Impossible());
			}
		}
		printValue(av);
	}
	catch(const ScalarConverter::PositiveInfinity& e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: inff" << std::endl;
		std::cout << "double: inf" << std::endl;
	}
	catch(const ScalarConverter::NegativeInfinity& e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
	catch(const ScalarConverter::NotaNumber& e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	catch(const ScalarConverter::Impossible& e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}

const char* ScalarConverter::PositiveInfinity::what() const throw()
{
	return ("Positive Infinity");
}

const char* ScalarConverter::NegativeInfinity::what() const throw()
{
	return ("Negative Infinity");
}

const char* ScalarConverter::NotaNumber::what() const throw()
{
	return ("Not a Number");
}

const char* ScalarConverter::Impossible::what() const throw()
{
	return ("Impossible");
}