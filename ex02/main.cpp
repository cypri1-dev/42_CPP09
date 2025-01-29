/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:45 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/29 13:35:12 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include "iostream"
#include <cstddef>
#include <ostream>
#include <utility>
#include <vector>
#include <ctime>
#include <list>

int main(int argc, char **argv) {

	try {

		// ? VECTOR PART
		
		std::vector<int> tab;
		std::vector<std::pair<int, int> > tab_pairs;
		std::vector<int> final_tab;
		
		tab = parser_vector(argc, argv);
		
		clock_t start_v = clock();
		tab_pairs = make_pairs(tab);
		tab_pairs = sort_pairs_by_A(tab_pairs);
		final_tab = insert_B(tab, tab_pairs);
		clock_t end_v = clock();
		
		double time_exec = static_cast<double>(end_v - start_v) / CLOCKS_PER_SEC * 1e6;
		print_result_vector(tab, final_tab);
		print_execution_time("<vector>", time_exec);

		// ? LIST PART

		std::list<int> list;
		std::list<std::pair<int, int> > list_pairs;
		std::list<int> final_list;
		
		list = parser_list(argc, argv);
		clock_t start_l = clock();
		list_pairs = make_pairs_list(list);
		list_pairs = sort_pairs_by_A_list(list_pairs);
		final_list = insert_B_list(list, list_pairs);
		clock_t end_l = clock();

		double time_exec_list = static_cast<double>(end_l - start_l) / CLOCKS_PER_SEC * 1e6;
		print_result_list(list, final_list);
		print_execution_time("<list>", time_exec_list);

	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}