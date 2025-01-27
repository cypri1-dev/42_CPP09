/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:45 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/27 19:34:15 by cyferrei         ###   ########.fr       */
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
		std::vector<int> final_tab;
		
		tab = parser_vector(argc, argv);
		tab_pairs = make_pairs(tab);
		std::cout << BOLD_ON << "Making pairs ...." << BOLD_OFF << std::endl;
		print_list(tab, tab_pairs);
		std::cout << BOLD_ON << "Sorting pairs by A...." << BOLD_OFF << std::endl;
		tab_pairs = sort_pairs_by_A(tab_pairs);
		print_list(tab, tab_pairs);
		final_tab = insert_B(tab_pairs);
		for (size_t i = 0; i < final_tab.size(); ++i) {
			if (final_tab[i] == -1)
				continue;
			std::cout << BOLD_ON GREEN << final_tab[i] << BOLD_OFF << " ";
		}
		std::cout << std::endl; 
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}