/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:07:38 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/29 13:21:04 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <exception>

bool checkAdditionOverflow(int a, int b);
bool checkSubtractionOverflow(int a, int b);
bool checkMultiplicationOverflow(int a, int b);
bool checkDivisionOverflow(int a, int b);

class InvalidExpressionError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Invalid Expression!\033[0m";
		}
};

class DivisionBy0Error : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Division by 0!\033[0m";
		}
};

class InvalidTokenError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Invalid token!\033[0m";
		}
};

class OverflowError : public std::exception {
	public:
		const char *what()const throw() {
			return "\033[31mError: Overflow detected!\033[0m";
		}
};
#endif