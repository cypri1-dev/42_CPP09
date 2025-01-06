/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:24 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/06 11:51:30 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
	
	t_data data;
	try {
		// ? little parsing
		checker(argc, argv);
		// TODO: check permissions
		// TODO: export .csv in a map
		export_csv(data);
		for (std::map<std::string, double>::iterator it = data.mapCSV.begin(); it != data.mapCSV.end(); ++it) {
					std::cout << "Date: " << it->first << ", Taux de change: " << it->second << std::endl;
				}
	}
	// ! if fail throw exception
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	
	return (0);
}