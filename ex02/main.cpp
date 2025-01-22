/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:45 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/22 19:13:46 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "colors.hpp"

#include "iostream"
#include <ostream>
#include <vector>

int main(int argc, char **argv) {

	try {
		std::vector<int> tab;
		std::vector<std::pair<int, int> > tab_pairs; 
		
		tab = parser_vector(argc, argv);
		tab_pairs = make_pairs(tab);
		
		for (std::vector<int>::iterator it = tab.begin(); it != tab.end(); ++it)
			std::cout << BLUE << *it << " " << BOLD_OFF;
		std::cout << std::endl;
		
		for (size_t i = 0; i < tab_pairs.size(); ++i) {
			std::cout << "(" << tab_pairs[i].first << ", ";
			if (tab_pairs[i].second == -1)
				std::cout << "NULL";
			else
				std::cout << tab_pairs[i].second;
			std::cout << ")" << std::endl;
		}
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}