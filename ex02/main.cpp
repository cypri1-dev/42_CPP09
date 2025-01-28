/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:45 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/28 14:17:02 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "colors.hpp"

#include "iostream"
// #include <cstddef>
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
		print_result_vector(tab, final_tab, time_exec);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}

//./PmergeMe `shuf -i 1-100000 -n 100 | tr "\n" " "` >d1; diff d1 <(sort d1)