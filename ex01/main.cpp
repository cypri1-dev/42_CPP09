/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:07:31 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/13 11:36:53 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "colors.hpp"

#include <cctype>
#include <exception>
#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
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
				stack.push(std::atoi(token.c_str()));
			}
			else if (token == "+" || token == "-" || token == "*" || token == "/") {
				if (stack.size() < 2)
					throw std::runtime_error(BOLD_ON RED"Invalid expression" BOLD_OFF);
				
				int b = stack.top(); stack.pop();
				int a = stack.top(); stack.pop();
				
				if (token == "+")
					stack.push(a + b);
				else if (token == "-")
					stack.push(a - b);
				else if (token == "*")
					stack.push(a * b);
				else if (token == "/") {
					if (b == 0)
						throw std::runtime_error(BOLD_ON RED "Division by 0!" BOLD_OFF);
					stack.push(a / b);
				}	
			}
			else {
				throw std::runtime_error(BOLD_ON RED "Invalid token" BOLD_OFF);
			}
		}
		if (stack.size() != 1)
			throw std::runtime_error(BOLD_ON RED"Invalid expression" BOLD_OFF);
		std::cout << stack.top() << std::endl;
	}
	catch (const std::exception &e) {
		std::cerr << BOLD_ON RED "Error: " << BOLD_OFF << e.what() << std::endl;
		return (1);
	}
	return (0);
}