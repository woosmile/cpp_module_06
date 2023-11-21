#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <cctype>

# define CHAR 1
# define INT 2
# define FLOAT 3
# define DOUBLE 4

class ScalarConverter
{
	private:
		int		_type;
		void	checkType(const char *av);
	public:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter&	operator=(const ScalarConverter &other);
		int		getType() const;
		void	converter(const char *av);
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
};

#endif