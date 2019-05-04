#include "annealing.h"

namespace AnnealingProcess {
    Annealing::Annealing() : temp(100), finish(0.05) { }
    Annealing::Annealing(double init, double finish) : temp(init), finish(finish) { }
};