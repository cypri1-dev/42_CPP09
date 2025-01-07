/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:19 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/07 18:34:39 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "colors.hpp"

#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>

/****************************************CHECKERS_ARGS*******************************************/

bool	is_txt_file(const std::string &file) {

	size_t pos = file.rfind(".txt");
	return (pos != std::string::npos) && (file.substr(0, pos).find(".txt") == std::string::npos);
}

void	checker_args(int argc, char **argv) {

	if (argc != 2)
		throw NotEnoughtArgs();
	
	std::string tmp(argv[1]);
	if (!is_txt_file(tmp))
		throw WrongFormatInput();
}

/****************************************PARSERS*******************************************/

bool	isValidDate(std::string &date) {

	if (date.size() != 10)
		return false;
	
	int year, month, day;
	char sep1, sep2;
	std::istringstream iss(date);

	iss >> year >> sep1 >> month >> sep2 >> day;
	if (sep1 != '-' || sep2 != '-' || iss.fail())
		return false;

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	return (true);
}

double	parse_csv_data(std::string date, std::string value_str) {
	
	double tmp;
	std::istringstream iss(value_str);
	if (!(iss >> tmp))
		throw CsvFileValueError();
	else if (std::isnan(tmp) || std::isinf(tmp) || tmp < 0 || tmp > MAX_DOUBLE)
		throw CsvFileValueError();
	else if (!isValidDate(date))
		throw CsvFileDateError();
	return (tmp);
}

double	parse_input_data(std::string date, std::string amount_str) {
	double tmp = -1;
	std::istringstream iss(amount_str);
	if (!(iss >> tmp))
		std::cout << "\033[31mError: wrong_value\033[0m" << std::endl;
	else if (std::isnan(tmp) || std::isinf(tmp) || tmp < 0 || tmp > MAX_DOUBLE)
		std::cout << "\033[31mError: wrong_value\033[0m" << std::endl;
	else if (!isValidDate(date))
		std::cout << "\033[31mError: wrong_date\033[0m" << std::endl;
	return (tmp);
}

std::map<std::string, double>	parse_line(std::string &line) {
	
	std::map<std::string, double> inputMap;
	size_t sep_pos = line.find("|");
	if (sep_pos == std::string::npos) {
		std::cout << "\033[31mError: bad_syntax\033[0m" << std::endl;
		return inputMap;
	}

	std::string date = line.substr(0, sep_pos - 1);
	if (sep_pos + 2 >= line.size()) {
		std::cout << "\033[31mError: missing_value\033[0m" << std::endl;
		return inputMap; // Retourne une map vide
	}
	std::string amount_str = line.substr(sep_pos + 2);
	double amount = parse_input_data(date, amount_str);
	if (amount < 0 || !isValidDate(date))
		return inputMap;
	inputMap[date] = amount;
	return (inputMap);
}

/****************************************EXPORT CSV TO MAP*******************************************/

void	export_csv(t_data &data) {
	
	std::string csv_file = CSV_FILE;
	std::ifstream file(csv_file.c_str());
	if (!file.is_open())
		throw CsvFileNotFoundError();

	std::string line;
	bool first_line = true;
	while(std::getline(file, line)) {
		if (first_line) {
			first_line = false;
			continue;
		}
		size_t comma_pos = line.find(",");
		if (comma_pos == std::string::npos) {
			throw CsvFileSyntaxError();
		}
		std::string date = line.substr(0, comma_pos);
		std::string value_str = line.substr(comma_pos + 1);

		double value = parse_csv_data(date, value_str);
		data.mapCSV[date] = value;
	}
	file.close();
}

/****************************************DISPLAY TOTAL*******************************************/

void	display_amount(t_data &data, std::map<std::string, double> mapInput) {
	std::string input_data = mapInput.begin()->first;
	double input_amount = mapInput.begin()->second;
	std::map<std::string, double>::iterator it_closest = data.mapCSV.end();

	for (std::map<std::string, double>::iterator it = data.mapCSV.begin(); it != data.mapCSV.end(); ++it) {
		if (it->first == input_data) {
			// std::cout << input_data << std::endl;
			std::cout << GREEN << "Date: " << it->first << ", Exchange rate: " << it->second << ", Amount: " << input_amount << ", Result: " << (it->second * input_amount) << BOLD_OFF << std::endl;
			return;
		}
		else if (it->first < input_data) {
			it_closest = it;
		}
	}
	if (it_closest != data.mapCSV.end())
		std::cout << "Date: " << it_closest->first << ", Exchange rate: " << it_closest->second << ", Amount: " << input_amount << ", Result: " << (it_closest->second * input_amount) << std::endl;
}

/****************************************PARSE LINE TXT - DISPLAY AMOUNT - ERROR*******************************************/

void	convert_btc(t_data &data) {
	
	(void)data;
	std::map<std::string, double> mapInput;
	std::string input_file = INPUT_FILE;
	std::ifstream file(input_file.c_str());
	if (!file.is_open())
		throw InputFileNotFoundError();

	std::string line;
	bool first_line = true;
	while (std::getline(file, line)) {
		if (first_line) {
			first_line = false;
			continue;
		}
		mapInput = parse_line(line);
		if (mapInput.empty())
			continue;
		else
			display_amount(data, mapInput);
	}
	file.close();
}