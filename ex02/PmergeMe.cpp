/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:49 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/28 14:16:49 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "colors.hpp"

#include <cstddef>
#include <sstream>
#include <cstdlib> 
#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>

/************************************************VECTOR PART************************************************/

std::vector<int>	generate_JBST_seq(size_t n) {
	
	std::vector<int> seq;
	int a = 1;
	int b = 3;

	while(a <= static_cast<int>(n)) {
		seq.push_back(a);
		int tmp = a;
		a = b;
		b = tmp +b;
	}
	std::reverse(seq.begin(), seq.end());
	return seq;
}

void	insert_binary(std::vector<int> &main_chain, int b) {
	std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), b);
	main_chain.insert(it, b);
}

const size_t J[] = {1,  3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525 };

std::vector<int> insert_B(std::vector<int> tab, std::vector<std::pair<int, int> > tab_pairs) {
	
	std::vector<int> main_chain;
	for (size_t i = 0; i < tab_pairs.size() - (tab.size() % 2 == 1); ++i)
		main_chain.push_back(tab_pairs[i].first);

	if ((tab.size() % 2) == 1) {
		std::swap(tab_pairs[tab_pairs.size() - 1].first, tab_pairs[tab_pairs.size() -1].second);
	}

	//Insert b1 de facto
	insert_binary(main_chain, tab_pairs[0].second);
	
	size_t pushed_count = 1;
	for (int i = 1; i > -1; i++) {
		if (pushed_count >= tab_pairs.size())
			break;
		
		int j = J[i] - 1 > tab_pairs.size() ? tab_pairs.size() : J[i] - 1;
		int jm1 = J[i - 1] - 1;

		for (int idx = j; idx > jm1; idx--) {
			int b = tab_pairs[idx].second;
			pushed_count++;
			if (idx >= (int)tab_pairs.size())
				continue;
			insert_binary(main_chain, b);
		}
	}
	return (main_chain);
}

/************************************************************************************************/

std::vector<std::pair<int, int> >	merge(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right) {
	
	std::vector<std::pair<int, int> > res;
	
	while(!left.empty() && !right.empty()) {
		if (left.front().first < right.front().first) {
			res.push_back(left.front());
			left.erase(left.begin());
		}
		else {
			res.push_back(right.front());
			right.erase(right.begin());
		}
	}
	while(!left.empty()) {
		res.push_back(left.front());
		left.erase(left.begin());
	}
	while (!right.empty()) {
		res.push_back(right.front());
		right.erase(right.begin());
	}
	return (res);
}

std::vector<std::pair<int, int> >	sort_pairs_by_A(std::vector<std::pair<int, int> > tab_pairs) {
	
	if (tab_pairs.size() <= 1)
		return tab_pairs;


	size_t mid = tab_pairs.size() / 2;
	std::vector<std::pair<int, int> > left(tab_pairs.begin(), tab_pairs.begin() + mid);
	std::vector<std::pair<int, int> > right(tab_pairs.begin() + mid, tab_pairs.end());

	left = sort_pairs_by_A(left);
	right = sort_pairs_by_A(right);

	return merge(left, right);
}

/************************************************************************************************/

std::vector<std::pair<int, int> >	make_pairs(std::vector<int> tab) {
	
	std::vector<std::pair<int, int> > pairs;

	for (size_t i = 0; i + 1 < tab.size(); i+=2) {
		if (tab[i] > tab[i + 1])
			pairs.push_back(std::make_pair(tab[i], tab[i + 1]));
		else
		 	pairs.push_back(std::make_pair(tab[i + 1], tab[i]));
	}
	if (tab.size() % 2 != 0)
		pairs.push_back(std::make_pair(tab.back(), -1));
	return (pairs);
}

/************************************************************************************************/

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

/********************************************PRINT RESULT****************************************************/

void	print_result_vector(std::vector<int> tab, std::vector<int> final_tab, double time_exec) {
	
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
