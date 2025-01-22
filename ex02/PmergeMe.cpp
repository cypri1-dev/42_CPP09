/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:49 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/22 12:01:32 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <string>
#include <sstream>
#include <cstdlib> 
#include <iostream>
#include <vector>
#include <algorithm>

bool	ft_isdigit(std::string token) {
	size_t i = 0;
	while (token[i]) {
		if (!isdigit(token[i]))
			return false;
		i++;
	}
	return true;
}

void	parser(int argc, char **argv) {
	
	if (argc < 2)
		throw NotEnoughtArgs();
	
	std::vector<int> tab;
	std::string token;
	std::size_t i = 1;
	
	while (argv[i]) {
		std::istringstream iss(argv[i]);
		int tmp = -1;
		iss >> token;
		std::cout << token << std::endl;
		if (!ft_isdigit(token) || (tmp = std::atoi(token.c_str())) < 0)
			throw IsNotDigits();
		if (std::find(tab.begin(), tab.end(), tmp) == tab.end())
			tab.push_back(tmp);
		else
			throw DoubleValueError();
		i++;
	}
}