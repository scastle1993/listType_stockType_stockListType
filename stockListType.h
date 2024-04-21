#ifndef STOCKLISTTYPE_H
#define STOCKLISTTYPE_H

#include "listType.h"
#include "stockType.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>

class stockListType : public listType<stockType> {
private:
    int* sortIndicesGainLoss;

public:
    stockListType() {
        sortIndicesGainLoss = nullptr;
    }

    ~stockListType() {
        delete[] sortIndicesGainLoss;
    }

    bool isEmpty() const {
        return listType<stockType>::isEmpty();
    }

    int lengthIs() const {
        return listType<stockType>::lengthIs();
    }

    void printBySymbol() const {
        std::cout << "********* First Investor's Heaven **********" << std::endl;
        std::cout << "*********    Financial Report     **********" << std::endl;
        std::cout << std::setw(8) << "Stock" << std::setw(16) << "Today" << std::setw(27) << "Previous" << std::setw(12) << "Percent" << std::endl;
        std::cout << std::setw(8) << "Symbol" << std::setw(7) << "Open" << std::setw(8) << "Close" << std::setw(8) << "High" << std::setw(8) << "Low" << std::setw(10) << "Close" << std::setw(12) << "Gain" << std::setw(12) << "Volume" << std::endl;
        std::cout << "------   -----    -----   -----   -----  --------  -------    ------" << std::endl;

        nodeType<stockType>* current = head;
        while (current != nullptr) {
            std::cout << std::setw(6) << current->info.getSymbol() << std::setw(10) << current->info.getOpeningPrice()
                << std::setw(10) << current->info.getClosingPrice() << std::setw(10) << current->info.getTodayHigh()
                << std::setw(10) << current->info.getTodayLow() << std::setw(10) << current->info.getPrevClose()
                << std::setw(12) << current->info.getPercGain() << "%" << std::setw(12) << current->info.getVolume() << std::endl;
            current = current->next;
        }

        double totalAssets = 0.0;
        current = head;
        while (current != nullptr) {
            totalAssets += current->info.getClosingPrice() * current->info.getVolume();
            current = current->next;
        }

        std::cout << "Closing Assets: $" << std::fixed << std::setprecision(2) << totalAssets << std::endl;
        std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    }

    void printByGainLoss() const {
        if (sortIndicesGainLoss == nullptr) {
            std::cout << "List not sorted by gain/loss." << std::endl;
            return;
        }

        std::cout << "********* First Investor's Heaven **********" << std::endl;
        std::cout << "*********    Financial Report     **********" << std::endl;
        std::cout << std::setw(8) << "Stock" << std::setw(16) << "Today" << std::setw(27) << "Previous" << std::setw(12) << "Percent" << std::endl;
        std::cout << std::setw(8) << "Symbol" << std::setw(7) << "Open" << std::setw(8) << "Close" << std::setw(8) << "High" << std::setw(8) << "Low" << std::setw(10) << "Close" << std::setw(12) << "Gain" << std::setw(12) << "Volume" << std::endl;
        std::cout << "------   -----    -----   -----   -----  --------  -------    ------" << std::endl;

        nodeType<stockType>* current = head;
        for (int i = 0; i < length; i++) {
            int index = sortIndicesGainLoss[i];
            for (int j = 0; j < index; j++) {
                current = current->next;
            }
            std::cout << std::setw(6) << current->info.getSymbol() << std::setw(10) << current->info.getOpeningPrice()
                << std::setw(10) << current->info.getClosingPrice() << std::setw(10) << current->info.getTodayHigh()
                << std::setw(10) << current->info.getTodayLow() << std::setw(10) << current->info.getPrevClose()
                << std::setw(12) << current->info.getPercGain() << "%" << std::setw(12) << current->info.getVolume() << std::endl;
            current = head;
        }

        std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    }

    void insertStock(const stockType& newStock) {
        listType<stockType>::insertLast(newStock);
        sortByGainLoss();
    }

    void deleteStock(const std::string& symbol) {
        nodeType<stockType>* current = head;
        nodeType<stockType>* trailCurrent = nullptr;

        while (current != nullptr) {
            if (current->info.getSymbol() == symbol) {
                break;
            }
            trailCurrent = current;
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Stock " << symbol << " not found in the list." << std::endl;
        }
        else {
            if (trailCurrent == nullptr) {
                head = head->next;
            }
            else {
                trailCurrent->next = current->next;
            }
            delete current;
            length--;
            sortByGainLoss();
        }
    }

    void sortByGainLoss() {
        delete[] sortIndicesGainLoss;
        sortIndicesGainLoss = new int[length];

        std::vector<std::pair<double, int>> gainLossIndices(length);
        nodeType<stockType>* current = head;
        for (int i = 0; i < length; i++) {
            double percGain;
            current->info.calcPercGain();
            percGain = current->info.getPercGain();
            gainLossIndices[i] = std::make_pair(percGain, i);
            current = current->next;
        }

        std::sort(gainLossIndices.begin(), gainLossIndices.end(), std::greater<std::pair<double, int>>());

        for (int i = 0; i < length; i++) {
            sortIndicesGainLoss[i] = gainLossIndices[i].second;
        }
    }
};

#endif