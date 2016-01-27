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

        int beginDay = atoi(argv[2]);
        int beginMonth = atoi(argv[3]);
        int beginYear = atoi(argv[4]);

        int endDay = atoi(argv[5]);
        int endMonth = atoi(argv[6]);
        int endYear = atoi(argv[7]);

        double S; // Option price
        double K = atof(argv[8]); // Strike price
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

        std::cout << "<html><head><title>Index</title><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\"><script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js\"></script><script src=\"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js\"></script></head><body> ";

        std::cout << "<div class= \"panel panel-primary\">  <div class=\"panel-heading\"><h3 class=\"panel-title\">GREEKS</h3></div><div class=\"list-group\">";

        std::cout << "<p class=\"list-group-item\"><big>Underlying:      " << S << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Strike:          " << K << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Risk-Free Rate:  " << r << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Volatility:      " << v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Maturity:        " << T << "</big></p>";

        std::cout << "<p class=\"list-group-item\"><big>Call Price:      " << call << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Call Delta:      " << call_delta_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Call Gamma:      " << call_gamma_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Call Vega:       " << call_vega_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Call Theta:      " << call_theta_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Call Rho:        " << call_rho_v << "</big></p>";

        std::cout << "<p class=\"list-group-item\"><big>Put Price:       " << put << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Put Delta:       " << put_delta_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Put Gamma:       " << put_gamma_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Put Vega:        " << put_vega_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Put Theta:       " << put_theta_v << "</big></p>";
        std::cout << "<p class=\"list-group-item\"><big>Put Rho:         " << put_rho_v << "</big></p>";

        std::cout << "</div></body></html>";

    } catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Error: unknown exception" << std::endl;
        return 1;
    }
    return 0;
}
