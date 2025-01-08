/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:19 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/08 14:35:34 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "colors.hpp"

#include <climits>
#include <ctime>
#include <fstream>
#include <iterator>
#include <sstream>
#include <cmath>
#include <iostream>
#include <utility>

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

bool isLeapYear(int year) {
	
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

time_t dateToTimeStamp(std::string &date) {

	const std::string fmt = "%Y-%m-%d";
	std::tm tm = {};
	char buffer[100] = {0};

	// ? Parse la date avec strptime
	char *to_timestamp = strptime(date.c_str(), fmt.c_str(), &tm);
	if (!to_timestamp) {
		return -1;
	}

	// ? Validation du jour du mois en fonction du mois et de l'année
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int year = tm.tm_year + 1900; // L'année dans struct tm commence à 1900
	int month = tm.tm_mon;		// 0 = Janvier, 11 = Décembre

	// ? Correction pour le mois de février en cas d'année bissextile
	if (isLeapYear(year)) {
		daysInMonth[1] = 29; // Février a 29 jours dans une année bissextile
	}

	if (month < 0 || month > 11 || tm.tm_mday < 1 || tm.tm_mday > daysInMonth[month]) {
		std::cerr << "Date invalide !\n";
		return -1;
	}

	// ? Convertir la date de nouveau en chaîne pour comparaison
	size_t timestamp = strftime(buffer, 100, fmt.c_str(), &tm);

	// ? Comparaison entre la date formatée et la date d'entrée
	if (std::string(buffer) != date) {
		std::cerr << "Date formatée différente de la date d'entrée.\n";
		return -1;
	}

	(void)timestamp;
	return std::mktime(&tm);
}

std::pair<time_t, std::pair<std::string, double> > parse_csv_data(std::string date, std::string value_str) {
	
	std::pair<time_t, std::pair<std::string, double> > ret;
	std::istringstream iss(value_str);
	ret.second.first = date;
	if (!(iss >> ret.second.second))
		throw CsvFileValueError();
	else if (std::isnan(ret.second.second) || std::isinf(ret.second.second) || ret.second.second < 0)
		throw CsvFileValueError();
	ret.first = dateToTimeStamp(date);
	return (ret);
}

double	parse_input_data(std::string date, std::string amount_str) {
	double tmp = -1;
	std::istringstream iss(amount_str);
	if (!(iss >> tmp))
		std::cout << "\033[31mError: error_value\033[0m" << std::endl;
	else if (std::isnan(tmp) || std::isinf(tmp) || tmp < 0 || tmp > 1000)
		std::cout << "\033[31mError: wrong_value\033[0m" << std::endl;
	(void)date;
	return (tmp);
}

std::map<time_t, std::pair<std::string, double> >	parse_line(std::string &line) {
	
	std::map<time_t, std::pair<std::string, double> > inputMap;
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
	
	time_t timestamp = dateToTimeStamp(date);
	if (amount < 0 || amount > 1000 || timestamp == -1)
		return inputMap;
	
	inputMap[timestamp] = std::make_pair(date, amount);
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
		std::pair<time_t, std::pair<std::string, double> > pair = parse_csv_data(date, value_str);
		data.mapCSV[pair.first] = pair.second;
	}
	file.close();
}

/****************************************DISPLAY TOTAL*******************************************/

void	display_amount(t_data &data, std::map<time_t, std::pair<std::string, double> > mapInput) {
	time_t input_date = mapInput.begin()->first;
	double input_amount = mapInput.begin()->second.second;

	std::map<time_t, std::pair<std::string, double> >::iterator it;
	if ((it = data.mapCSV.find(input_date)) != data.mapCSV.end()) {
		std::cout << GREEN << "Date: " << it->second.first << ", Exchange rate: " << it->second.second << ", Amount: " << input_amount << ", Result: " << (it->second.second * input_amount) << BOLD_OFF << std::endl;
	} else {
		it = data.mapCSV.lower_bound(input_date);
		it = (it == data.mapCSV.begin() ? it : --it);
		// std::cout << input_date << " | "  << it->first << " | " << mapInput.begin()->second.first << std::endl;
		std::cout << YELLOW << "Date: " << it->second.first << ", Exchange rate: " << it->second.second << ", Amount: " << input_amount << ", Result: " << (it->second.second * input_amount) << BOLD_OFF <<std::endl;
	}
}

/****************************************PARSE LINE TXT - DISPLAY AMOUNT - ERROR*******************************************/

void	convert_btc(t_data &data, char **argv) {
	
	std::map<time_t, std::pair<std::string, double> > mapInput;
	std::string input_file = argv[1];
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