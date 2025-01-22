/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:49 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/22 13:59:06 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <sstream>
#include <cstdlib> 
#include <algorithm>

void	make_pairs(std::vector<int> tab) {
	
}

bool	ft_isdigit(std::string token) {
	
	size_t i = 0;
	
	while (token[i]) {
		if (!isdigit(token[i]))
			return false;
		i++;
	}
	return true;
}

std::vector<int>	parser_vector(int argc, char **argv) {
	
	if (argc < 2)
		throw NotEnoughtArgs();
	
	std::vector<int> tab;
	std::string token;
	std::size_t i = 1;
	
	while (argv[i]) {
		
		std::istringstream iss(argv[i]);
		int tmp = -1;
		iss >> token;
		
		if (!ft_isdigit(token) || (tmp = std::atoi(token.c_str())) < 0)
			throw IsNotDigits();
		if (std::find(tab.begin(), tab.end(), tmp) == tab.end())
			tab.push_back(tmp);
		else
			throw DoubleValueError();
		i++;
	}
	return (tab);
}