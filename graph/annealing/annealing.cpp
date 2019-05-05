#include "annealing.h"

namespace AnnealingProcess {
    Annealing::Annealing() : temp(1000), finish(1.05) { }
    Annealing::Annealing(double init, double finish) : temp(init), finish(finish) { }
};