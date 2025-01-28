/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:52 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/28 12:38:35 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <exception>
#include <utility>
#include <vector>
#include <string>

std::vector<int>	parser_vector(int argc, char **argv);
bool	ft_isdigit(std::string token);
std::vector<std::pair<int, int> >	make_pairs(std::vector<int> tab);
void	print_list(std::vector<int> tab, std::vector<std::pair<int, int> > tab_pairs);
std::vector<std::pair<int, int> >	sort_pairs_by_A(std::vector<std::pair<int, int> > tab_pairs);
std::vector<std::pair<int, int> >	merge(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right);
std::vector<int>	generate_JBST_order(size_t n);
void	insert_binary(std::vector<int> &main_chain, int b);
std::vector<int> insert_B(std::vector<int>, std::vector<std::pair<int, int> > tab_pairs);

class NotEnoughtArgs : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: This program needs 1 argument!\033[0m";
		}
};

class IsNotDigits : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: This argument must contains only positive numbers!\033[0m";
		}
};

class DoubleValueError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: This argument must not contains same values!\033[0m";
		}
};

#endif