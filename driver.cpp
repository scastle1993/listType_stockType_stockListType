/**********************************************************************************************
 *
 * CIS269 - Data Structures
 * Pima College - Spring 2024
 * Chapter 13 - Pg 1003 - Ex #21
 * Stock Market - "driver.cpp"
 *
 * This program creates and tests the functionalities of listType, stockType, and stockListType.
 *
 * Author: Sean Castle
 *
**********************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "stockListType.h"

int main() {
    stockListType stockList;
    std::ifstream inputFile("data.txt");

    // Read stock data from file and insert into the list
    if (inputFile.is_open()) {
        stockType stock;
        while (inputFile >> stock) {
            stockList.insertStock(stock);
        }
        inputFile.close();
    }
    else {
        std::cout << "Unable to open the input file." << std::endl;
        return 1;
    }

    int choice;
    std::string symbol;
    do {
        std::cout << "\nStock List Menu:\n";
        std::cout << "1. Print list by symbol\n";
        std::cout << "2. Print list by percent gain/loss\n";
        std::cout << "3. Delete a stock\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            stockList.printBySymbol();
            break;
        case 2:
            stockList.printByGainLoss();
            break;
        case 3:
            std::cout << "Enter the stock symbol to delete: ";
            std::cin >> symbol;
            stockList.deleteStock(symbol);
            break;
        case 4:
            std::cout << "Exiting program..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 4);

    return 0;
}// End main