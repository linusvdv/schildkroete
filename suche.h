#include <atomic>
#include <chrono>

#include "types.h"

int miniMax(position& pos, int tiefe, int hoehe, zuege& besterZug, int alpha, int beta, std::atomic<bool>& sucheStop, int voheriger_zug, int spielzeit, const std::chrono::time_point<std::chrono::high_resolution_clock>& start);

void newGame();

extern int seldepth;
