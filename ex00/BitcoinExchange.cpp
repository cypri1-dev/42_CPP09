/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:19 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/06 11:57:45 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <fstream>
#include <sstream>

bool	is_txt_file(const std::string &file) {
	size_t pos = file.rfind(".txt");
	return (pos != std::string::npos) && (file.substr(0, pos).find(".txt") == std::string::npos);
}

void	checker(int argc, char **argv) {
	if (argc != 2)
		throw NotEnoughtArgs();
	
	std::string tmp(argv[1]);
	if (!is_txt_file(tmp))
		throw WrongFormatInput();
}

void	export_csv(t_data &data) {

	std::string csv_file = CSV_FILE;
	std::ifstream file(csv_file.c_str());
	if (!file.is_open())
		throw CsvFileError();

	std::string line;
	bool first_line = true;
	while(std::getline(file, line)) {
		if (first_line) {
			first_line = false;
			continue;
		}
		size_t comma_pos = line.find(",");
		if (comma_pos == std::string::npos) {
			dprintf(2, "Error!\n");
			throw CsvFileError();
		}
		std::string date = line.substr(0, comma_pos);
		std::string value_str = line.substr(comma_pos + 1);

		std::istringstream iss(value_str);
		double value;
		if (!(iss >> value))
			throw CsvFileError();
		
		data.mapCSV[date] = value;
	}
	file.close();
}