#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <cctype>
# include <limits>
# include <cstdlib>
# include <cerrno>

# define CHAR 1
# define INT 2
# define FLOAT 3
# define DOUBLE 4

# define SUCCESS 5
# define FAILURE 6
# define NOPRINT 7

class ScalarConverter
{
	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter&	operator=(const ScalarConverter &other);
	private:
		static int		_type;
		static int		_precision_len;
		static char		_var_char;
		static int		_var_int;
		static float	_var_float;
		static double	_var_double;
		static int		_convert_char;
		static int		_convert_int;
		static int		_convert_float;
		static void		checkType(const char *av);
		static int		getType();
		static void		convertChar(const char *av);
		static void		convertInt(const char *av);
		static void		convertFloat(const char *av);
		static void		convertDouble(const char *av);
		static void		printValue(const char *av);
	public:
		static void	converter(const char *av);
	public:
		class NegativeInfinity: public std::exception
		{
			public:
				const char*	what() const throw();
		};
		class PositiveInfinity: public std::exception
		{
			public:
				const char*	what() const throw();
		};
		class NotaNumber: public std::exception
		{
			public:
				const char*	what() const throw();
		};
		class Impossible: public std::exception
		{
			public:
				const char*	what() const throw();
		};
};

#endif