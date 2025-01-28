/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:45 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/28 14:10:42 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "colors.hpp"

#include "iostream"
#include <cstddef>
#include <ostream>
#include <vector>
#include <ctime>

int main(int argc, char **argv) {

	try {
		std::vector<int> tab;
		std::vector<std::pair<int, int> > tab_pairs;
		std::vector<int> final_tab;
		
		tab = parser_vector(argc, argv);
		
		clock_t start = clock();
		tab_pairs = make_pairs(tab);
		tab_pairs = sort_pairs_by_A(tab_pairs);
		final_tab = insert_B(tab, tab_pairs);
		clock_t end = clock();
		
		double time_exec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6;
		
		std::cout << BOLD_ON BLUE << "Before : " << BOLD_OFF;
		for (size_t i = 0; i < tab.size(); ++i) {
			std::cout << tab[i] << " ";
		}
		std::cout << std::endl;

		std::cout << BOLD_ON BLUE << "After : " << BOLD_OFF;
		for (size_t i = 0; i < final_tab.size(); ++i) {
			if (final_tab[i] == -1)
				continue;
			std::cout << final_tab[i] << BOLD_OFF << " ";
		}
		std::cout << std::endl;

		std::cout << "Time to process a range of " << tab.size() << " elements with std::" << BOLD_ON << "<vector> : " << BOLD_OFF << time_exec << "us." <<std::endl;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}

//./PmergeMe `shuf -i 1-100000 -n 100 | tr "\n" " "` >d1; diff d1 <(sort d1)