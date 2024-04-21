#ifndef STOCKTYPE_H
#define STOCKTYPE_H

#include <string>

class stockType {
private:
    std::string symbol;
    double openingPrice;
    double closingPrice;
    double todayHigh;
    double todayLow;
    double prevClose;
    int volume;
    double percGain;

public:
    stockType() {
        symbol = "";
        openingPrice = 0.0;
        closingPrice = 0.0;
        todayHigh = 0.0;
        todayLow = 0.0;
        prevClose = 0.0;
        volume = 0;
        percGain = 0.0;
    }

    ~stockType() {
        // No dynamic memory allocation, so no cleanup needed
    }

    void setStockInfo(std::string sym, double open, double close, double high, double low, double prev, int vol) {
        symbol = sym;
        openingPrice = open;
        closingPrice = close;
        todayHigh = high;
        todayLow = low;
        prevClose = prev;
        volume = vol;
        calcPercGain();
    }

    void printStockInfo() const {
        std::cout << symbol << " " << openingPrice << " " << closingPrice
            << " " << todayHigh << " " << todayLow << " " << prevClose
            << " " << percGain << "%" << " " << volume << std::endl;
    }

    void showPrices() const {
        std::cout << "Opening Price: " << openingPrice << std::endl;
        std::cout << "Closing Price: " << closingPrice << std::endl;
        std::cout << "Today's High: " << todayHigh << std::endl;
        std::cout << "Today's Low: " << todayLow << std::endl;
        std::cout << "Previous Close: " << prevClose << std::endl;
    }

    void calcPercGain() {
        if (prevClose != 0.0) {
            percGain = ((closingPrice - prevClose) / prevClose) * 100.0;
        }
        else {
            percGain = 0.0;
        }
    }

    void showVolume() const {
        std::cout << "Volume: " << volume << std::endl;
    }

    std::string getSymbol() const {
        return symbol;
    }

    double getOpeningPrice() const {
        return openingPrice;
    }

    double getClosingPrice() const {
        return closingPrice;
    }

    double getTodayHigh() const {
        return todayHigh;
    }

    double getTodayLow() const {
        return todayLow;
    }

    double getPrevClose() const {
        return prevClose;
    }

    int getVolume() const {
        return volume;
    }

    double getPercGain() const {
        return percGain;
    }

    bool operator<(const stockType& other) const {
        return symbol < other.symbol;
    }

    friend std::istream& operator>>(std::istream& is, stockType& stock) {
        is >> stock.symbol >> stock.openingPrice >> stock.closingPrice >> stock.todayHigh
            >> stock.todayLow >> stock.prevClose >> stock.volume;
        stock.calcPercGain();
        return is;
    }
};

#endif