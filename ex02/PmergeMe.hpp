/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:52 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/22 19:07:03 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <exception>
#include <vector>
#include <string>

std::vector<int>	parser_vector(int argc, char **argv);
bool	ft_isdigit(std::string token);
std::vector<std::pair<int, int> >	make_pairs(std::vector<int> tab);

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