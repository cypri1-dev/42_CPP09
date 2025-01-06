/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:22 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/06 11:52:14 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <exception>
#include <map>
#include <string>

#define CSV_FILE "data.csv"

typedef struct s_data {
	std::map<std::string, double> mapCSV;
} t_data;

void	checker(int argc, char **argv);
void	export_csv(t_data &data);

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

class CsvFileError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Can't load CSV data!\033[0m";
		}
};

#endif