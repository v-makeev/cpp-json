#pragma once
#include <cmath>
#include <iostream>

namespace AnnealingProcess {
    class Annealing {
        double temp;
        double finish;
    public:
        Annealing();
        Annealing(double init_temp, double finish);
        template <class Random, class TemperatureGen, class StateGen>
        auto solve(StateGen sg, TemperatureGen gen) {
            typename StateGen::value_type cur = sg.first_state();
            typename StateGen::value_type next;
            double energy = sg.estimate(cur);
            while (temp > finish) {
                sg.get_next(cur, next);
                double nE = sg.estimate(next);
                double prob = exp((energy - nE) / temp);
                if (Random::random() < prob) {
                    energy = nE;
                    cur = next;
                }
                temp = gen.next_temperature(temp);
            }
            return cur;
        }
    };
};