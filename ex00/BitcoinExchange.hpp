/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:59:22 by cyferrei          #+#    #+#             */
/*   Updated: 2025/01/03 13:40:58 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <exception>

void	checker(int argc, char **argv);

class NotEnoughtArgs : public std::exception {
	public:
		const char* what()const throw() {
			return "\033[31mError: This program needs 2 arguments!\033[0m";
		}
};

class WrongFormatInput : public std::exception {
	public:
		const char* what()const throw() {
			return "\033[31mError: Wrong extension in input\033[0m";
		}
};

#endif