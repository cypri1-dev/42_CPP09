/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:19 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/03 13:55:57 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

bool is_txt_file(const std::string &file) {
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