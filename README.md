## 
<h1><img src="https://raw.githubusercontent.com/ayogun/42-project-badges/refs/heads/main/covers/cover-cpp-bonus.png"</h1>

## Description
C++ Module 09 focuses on mastering STL containers. It includes creating a Bitcoin exchange system, processing Reverse Polish Notation expressions, and implementing a merge-insert sort algorithm. This is a crucial step in refining advanced programming skills!

## 📖 **Project Overview**  

This module consists of three exercises that focus on STL usage and algorithm implementation:  

## 1️⃣ Exercise 00: Bitcoin Exchange  
- **Objective:** Implement a program that calculates Bitcoin values using historical exchange rates stored in a CSV file.  
- **Container:** `std::map`  
- **Key Points:**  
  - Parse a database with dates and Bitcoin prices.  
  - Handle input errors gracefully.  
  - Match input dates to the closest lower date in the database.  

## 2️⃣ Exercise 01: Reverse Polish Notation (RPN)  
- **Objective:** Create a calculator for expressions in Reverse Polish Notation.  
- **Container:** `std::stack`  
- **Key Points:**  
  - Process mathematical expressions using a stack.  
  - Supported operations: `+`, `-`, `*`, `/`.  
  - Handle errors, such as invalid input.  

## 3️⃣ Exercise 02: PmergeMe  
- **Objective:** Implement the merge-insert sort algorithm (Ford-Johnson) to sort sequences of integers.  
- **Containers:** `std::vector` and one additional container of your choice.  
- **Key Points:**  
  - Process large integer sequences (e.g., 3000+ numbers).  
  - Measure and compare sorting times for both containers.  
  - Display results with precision.

## 📋 **Mandatory Rules**  

- Follow the Orthodox Canonical Form for all classes.  
- Use at least one STL container per exercise (two for Exercise 02).  
- Containers used in one exercise are forbidden in the next.  
- Handle errors appropriately and ensure no memory leaks.  
- Code must compile with `-std=c++98` and `-Wall -Wextra -Werror` flags.
 
