/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:22 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/07 17:37:45 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <exception>
#include <map>
#include <string>

#define CSV_FILE "data.csv"
#define INPUT_FILE "input.txt"
#define MAX_DOUBLE 1.79769e+308

/****************************************STRUCTURE*******************************************/

typedef struct s_data {
	std::map<std::string, double> mapCSV;
} t_data;

/****************************************PROTOTYPES*******************************************/

void	checker_args(int argc, char **argv);
void	export_csv(t_data &data);
double	parse_csv_data(std::string date, std::string value_str);
bool	isValidDate(std::string &date);
void	convert_btc(t_data &data);
std::map<std::string, double>	parse_line(std::string &line);
double	parse_input_data(std::string date, std::string amount_str);
void	dsiplay_amount(t_data &data, std::map<std::string, double> mapInput);

/****************************************EXCPETIONS*******************************************/

class NotEnoughtArgs : public std::exception {
	public:
		const char* what()const throw() {
			return "\033[31mError: This program needs 2 arguments!\033[0m";
		}
};

class WrongFormatInput : public std::exception {
	public:
		const char* what()const throw() {
			return "\033[31mError: Wrong extension in input\033[0m";
		}
};

class CsvFileSyntaxError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Can't load CSV data: bad_syntax\033[0m";
		}
};

class CsvFileNotFoundError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Can't load CSV data: file_not_found\033[0m";
		}
};

class CsvFileValueError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Can't load CSV data: wrong_value\033[0m";
		}
};

class CsvFileDateError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Can't load CSV data: wrong_date\033[0m";
		}
};

class InputFileNotFoundError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Can't load input.txt: file_not_found\033[0m";
		}
};

#endif