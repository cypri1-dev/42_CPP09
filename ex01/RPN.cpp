/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:07:36 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/29 13:19:29 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "limits"

bool checkAdditionOverflow(int a, int b) {
	return (b > 0 && a > std::numeric_limits<int>::max() - b) || (b < 0 && a < std::numeric_limits<int>::min() - b);
}

bool checkSubtractionOverflow(int a, int b) {
	return (b < 0 && a > std::numeric_limits<int>::max() + b) || (b > 0 && a < std::numeric_limits<int>::min() + b);
}

bool checkMultiplicationOverflow(int a, int b) {
	if (a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) return true;
	if (a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a) return true;
	if (a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b) return true;
	if (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b) return true;
	return false;
}

bool checkDivisionOverflow(int a, int b) {
	return (a == std::numeric_limits<int>::min() && b == -1);
}