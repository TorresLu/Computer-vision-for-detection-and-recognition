#pragma once
#include <list>

class Predictor {
public:
    Predictor(int _history_size = 5)
        : history_size(_history_size){}

    bool setRecord(double value, double time);

    // Using history data to predict the query value
    // (fit the data using quadratic curve at min MSE criterion)
    double predict(double time);
    void clear(){
        history_value.clear();
        history_time.clear();
    }

private:
    std::list<double> history_value;
    std::list<double> history_time;
    int history_size;
};
