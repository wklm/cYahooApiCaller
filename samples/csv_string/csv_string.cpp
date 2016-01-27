#include <iostream>
#include "quote.h"
#include <string>
#include "black_scholes.h"
#include <sstream>
#include <cmath>

using namespace std;
double string_to_double( const std::string& s ) {
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

double standard_deviation(double data[], int n) {
    double mean=0.0, sum_deviation=0.0;
    int i;
    for(i=0; i<n;++i) {
        mean+=data[i];
    }
    mean=mean/n;
    for(i=0; i<n;++i)
        sum_deviation+=(data[i]-mean)*(data[i]-mean);
    return sqrt(sum_deviation/n);
}

class Date {
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
    if(argc < 9) {
        cerr << "Usage: " << argv[0] << " COMPANYNAME BEGINDAY BEGINMONTH BEGINYEAR ENDDAY ENDMONTH ENDYEAR STRIKE PRICE" << endl;
        return 1;
    }
    try {
        string companyName = argv[1];
        Date begin;
        Date end;

        int beginDay = argv[2];
        int beginMonth = argv[3];
        int beginYear = argv[4];

        int endDay = argv[5];
        int endMonth = argv[6];
        int endYear = argv[7];

        double S; // Option price
        double K = argv[8]; // Strike price
        double r = 0.05;
        double v;
        double T = 1.0;
        /*
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
        std::cin >> endYear;

        std::cout << "Strike price?" << std::endl;
        std::cin >> K;
        */

        begin.setDay(beginDay);
        begin.setMonth(beginMonth);
        begin.setYear(beginYear);

        end.setDay(endDay);
        end.setMonth(endMonth);
        end.setYear(endYear);

         S = string_to_double(quote::getLatestQuotesCsv(companyName, {quote::QuoteType::lastTradePriceOnly}));

        std::string petr4HistoricalPrices = quote::getHistoricalQuotesCsv(companyName,
                                                                          begin.getYear(), begin.getMonth(), begin.getDay(),
                                                                          end.getYear(), end.getMonth(), end.getDay(),
                                                                          quote::RangeType::daily);
        string line = petr4HistoricalPrices;
        stringstream ssin(line);
        string data = "";
        string temp = "";
        int i = 0;
        int j = 0;
        int size = 0;
        bool first = true;
        while(getline(ssin, data)) {
            if(first) {
                first = false;
                continue;
            }
            i = 0;
            stringstream ssil(data);
            while(getline(ssil, temp, ',')) {
                if(i == 6) {
                    continue;
                }
                ++i;
            }
            ++j;
            ++size;
        }
        first = true;
        i = 0;
        j = 0;
        ssin.str("");
        ssin.clear();
        ssin << line;
        double array[size];
        while(getline(ssin, data)) {
            if(first) {
                first = false;
                continue;
            }
            i = 0;
            stringstream ssil(data);
            while(getline(ssil, temp, ',')) {
                if(i == 6) {
                    array[j] = string_to_double(temp);
                    continue;
                }
                ++i;
            }
            ++j;
        }

        v = standard_deviation(array, size);

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

    } catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Error: unknown exception" << std::endl;
        return 1;
    }
    return 0;
}
