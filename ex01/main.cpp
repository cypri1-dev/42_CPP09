/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:07:31 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/29 13:22:25 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "colors.hpp"

#include <cctype>
#include <exception>
#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib> 

int main (int argc, char **argv) {
	
	if (argc != 2) {
		std::cerr << BOLD_ON YELLOW << "Usage: ./RPN <expression>" << BOLD_OFF << std::endl;
		return (1);
	}

	std::stack<int> stack;
	std::string token;
	std::istringstream iss(argv[1]);

	try {
		while(iss >> token) {
			if (isdigit(token[0])) {
				if (std::atoi(token.c_str()) < 0)
					throw OverflowError();
				stack.push(std::atoi(token.c_str()));
			}
			else if (token == "+" || token == "-" || token == "*" || token == "/") {
				if (stack.size() < 2)
					throw InvalidExpressionError();
				
				int b = stack.top(); stack.pop();
				int a = stack.top(); stack.pop();
				
				if (token == "+") {
					if (checkAdditionOverflow(a, b)) throw OverflowError();
					stack.push(a + b);
				}
				else if (token == "-") {
					if (checkSubtractionOverflow(a, b)) throw OverflowError();
					stack.push(a - b);
				}
				else if (token == "*") {
					if (checkMultiplicationOverflow(a, b)) throw OverflowError();
					stack.push(a * b);
				}
				else if (token == "/") {
					if (b == 0) throw DivisionBy0Error();
					if (checkDivisionOverflow(a, b)) throw OverflowError();
					stack.push(a / b);
				}	
			}
			else {
				throw InvalidTokenError();
			}
		}
		if (stack.size() != 1)
			throw InvalidExpressionError();
		std::cout << stack.top() << std::endl;
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}