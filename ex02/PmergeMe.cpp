/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:49 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/27 19:35:03 by cyferrei         ###   ########.fr       */
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

std::vector<int> insert_B(std::vector<std::pair<int, int> > tab_pairs) {
	
	std::vector<int> main_chain;
	for (size_t i = 0; i < tab_pairs.size(); ++i)
		main_chain.push_back(tab_pairs[i].first);
	
	std::vector<int> JBST_seq = generate_JBST_seq(main_chain.size());
	
	for (size_t i = 0; i < JBST_seq.size(); ++i) {
		int idx = JBST_seq[i] - 1;
		int b = tab_pairs[idx].second;
		insert_binary(main_chain, b);
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

/************************************************************************************************/

void	print_list(std::vector<int> tab, std::vector<std::pair<int, int> > tab_pairs) {
	
	for (std::vector<int>::iterator it = tab.begin(); it != tab.end(); ++it)
		std::cout << BLUE << *it << " " << BOLD_OFF;
	std::cout << std::endl;
	
	for (size_t i = 0; i < tab_pairs.size(); ++i) {
		std::cout << "(" << tab_pairs[i].first << ", ";
		if (tab_pairs[i].second == -1)
			std::cout << RED << "NULL" << BOLD_OFF;
		else
			std::cout << tab_pairs[i].second;
		std::cout << ")" << std::endl;
	}
}