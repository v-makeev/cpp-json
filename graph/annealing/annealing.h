#pragma once
#include <cmath>

namespace AnnealingProcess {
    class Annealing {
        double temp;
        double finish;
    public:
        Annealing();
        Annealing(double init_temp, double finish);
        template <class Random, class TemperatureGen, class StateGen>
        auto solve(StateGen sg) {
            typename StateGen::value_type cur = sg.first_state();
            typename StateGen::value_type next;
            sg.get_next(cur, next);
            double energy = sg.estimate(cur);
            while (temp > finish) {
                double nE = sg.estimate(next);
                double prob = exp((energy - nE) / temp);
                if (Random::random() < prob) {
                    energy = nE;
                    cur = next;
                }
                temp = TemperatureGen::next_temperature(temp);
            }
            return cur;
        }
    };
};