/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:49 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/22 11:41:07 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib> 
#include <iostream>

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
	
	std::string token;
	std::size_t i = 1;
	while (argv[i]) {
		std::istringstream iss(argv[i]);
		iss >> token;
		std::cout << token << std::endl;
		if (!ft_isdigit(token) || std::atoi(token.c_str()) < 0)
			throw IsNotDigits();
		i++;
	}
}