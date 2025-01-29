/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:52 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/29 13:31:25 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <exception>
#include <utility>
#include <vector>
#include <string>
#include <list>

std::vector<int>	parser_vector(int argc, char **argv);
bool	ft_isdigit(std::string token);
std::vector<std::pair<int, int> >	make_pairs(std::vector<int> tab);
void	print_result_vector(std::vector<int> tab, std::vector<int> final_tab);
std::vector<std::pair<int, int> >	sort_pairs_by_A(std::vector<std::pair<int, int> > tab_pairs);
std::vector<std::pair<int, int> >	merge(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right);
void	insert_binary(std::vector<int> &main_chain, int b);
std::vector<int> insert_B(std::vector<int>, std::vector<std::pair<int, int> > tab_pairs);

std::list<int>	parser_list(int argc, char **argv);
std::list<std::pair<int, int> >	make_pairs_list(std::list<int> list);
std::list<std::pair<int, int> >	sort_pairs_by_A_list(std::list<std::pair<int, int> > tab_pairs);
std::list<std::pair<int, int> >	merge_list(std::list<std::pair<int, int> > left, std::list<std::pair<int, int> > right);
void	insert_binary_list(std::list<int> &main_chain, int b);
std::list<int> insert_B_list(std::list<int>& tab, std::list<std::pair<int, int> >& tab_pairs);
void	print_result_list(std::list<int> tab, std::list<int> final_tab);

void print_execution_time(const std::string &container_name, double time_exec);

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

class OverflowError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Overflow detected!\033[0m";
		}
};

#endif