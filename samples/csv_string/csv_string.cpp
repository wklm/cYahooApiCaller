//
//  csv_string.cpp
//  quote
//
//  Copyright (C) 2013, 2014  André Pereira Henriques
//  aphenriques (at) outlook (dot) com
//
//  This file is part of quote.
//
//  quote is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  quote is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with quote.  If not, see <http://www.gnu.org/licenses/>.
//

#include <iostream>
//#include <curl/curl.h>
#include "quote.h"
#include <string>
#include "black_scholes.h"

class Date
{
public:
    int day;
    int month;
    int year;

    int getDay() {
        return this->day;
    }

    void setDay(int day) {
        this->day = day;
    }
    int getMonth() {
        return this->month;
    }

    void setMonth(int month) {
        this->month = month;
    }

    int getYear() {
        return this->year;
    }

    void setYear(int year) {
        this->year = year;
    }







};


int main(int argc, const char * argv[]) {
    try {
        std::string companyName = "";
        Date begin;
        Date end;

        int beginDay;
        int beginMonth;
        int beginYear;

        int endDay;
        int endMonth;
        int endYear;

        double S = 100.0;  // Option price
        double K = 100.0;  // Strike price
        double r = 0.05;   // Risk-free rate (5%)
        double v = 0.2;    // Volatility of the underlying (20%)
        double T = 1.0;    // One year until expiry

        // Then we calculate the call/put values and the Greeks
        double call = call_price(S, K, r, v, T);
        double call_delta_v = call_delta(S, K, r, v, T);
        double call_gamma_v = call_gamma(S, K, r, v, T);
        double call_vega_v = call_vega(S, K, r, v, T);
        double call_theta_v = call_theta(S, K, r, v, T);
        double call_rho_v = call_rho(S, K, r, v, T);

        double put = put_price(S, K, r, v, T);
        double put_delta_v = put_delta(S, K, r, v, T);
        double put_gamma_v = put_gamma(S, K, r, v, T);
        double put_vega_v = put_vega(S, K, r, v, T);
        double put_theta_v = put_theta(S, K, r, v, T);
        double put_rho_v = put_rho(S, K, r, v, T);


        std::cout << "company?" << std::endl;
        std::cin >> companyName;

        std::cout << "Begin day?" << std::endl;
        std::cin >> beginDay;
        std::cout << "Begin month?" << std::endl;
        std::cin >> beginMonth;
        std::cout << "Begin year?" << std::endl;
        std::cin >> beginYear;

        std::cout << "End day?" << std::endl;
        std::cin >> endDay;
        std::cout << "End month?" << std::endl;
        std::cin >> endMonth;
        std::cout << "End year?" << std::endl;
        std::cin >> endMonth;


        begin.setDay(beginDay);
        begin.setMonth(beginMonth);
        begin.setYear(beginYear);

        end.setDay(endDay);
        end.setMonth(endMonth);
        end.setYear(endYear);

        std::cout << quote::getLatestQuotesCsv(companyName, {quote::QuoteType::symbol, quote::QuoteType::name, quote::QuoteType::lastTradePriceOnly, quote::QuoteType::lastTradeDate, quote::QuoteType::lastTradeTime, quote::QuoteType::open, quote::QuoteType::dayLow, quote::QuoteType::dayHigh, quote::QuoteType::dayRange, quote::QuoteType::dividendShare, quote::QuoteType::peRatio}) << std::endl;
        std::cout << quote::getLatestQuotesCsv<quote::QuoteType::symbol, quote::QuoteType::name, quote::QuoteType::lastTradePriceOnly, quote::QuoteType::lastTradeDate, quote::QuoteType::lastTradeTime, quote::QuoteType::open, quote::QuoteType::dayLow, quote::QuoteType::dayHigh, quote::QuoteType::dayRange, quote::QuoteType::dividendShare, quote::QuoteType::peRatio>("MSFT") << std::endl;
        std::cout << quote::getHistoricalQuotesCsv(companyName, begin.getYear(), begin.getMonth(), begin.getDay(), end.getYear(), end.getMonth(), end.getDay(), quote::RangeType::dividendsOnly) << std::endl;
    } catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Error: unknown exception" << std::endl;
        return 1;
    }
    std::cout << "end of sample" << std::endl;


    // Finally we output the parameters and prices
    std::cout << "Underlying:      " << S << std::endl;
    std::cout << "Strike:          " << K << std::endl;
    std::cout << "Risk-Free Rate:  " << r << std::endl;
    std::cout << "Volatility:      " << v << std::endl;
    std::cout << "Maturity:        " << T << std::endl << std::endl;

    std::cout << "Call Price:      " << call << std::endl;
    std::cout << "Call Delta:      " << call_delta_v << std::endl;
    std::cout << "Call Gamma:      " << call_gamma_v << std::endl;
    std::cout << "Call Vega:       " << call_vega_v << std::endl;
    std::cout << "Call Theta:      " << call_theta_v << std::endl;
    std::cout << "Call Rho:        " << call_rho_v << std::endl << std::endl;

    std::cout << "Put Price:       " << put << std::endl;
    std::cout << "Put Delta:       " << put_delta_v << std::endl;
    std::cout << "Put Gamma:       " << put_gamma_v << std::endl;
    std::cout << "Put Vega:        " << put_vega_v << std::endl;
    std::cout << "Put Theta:       " << put_theta_v << std::endl;
    std::cout << "Put Rho:         " << put_rho_v << std::endl;
    return 0;
}
