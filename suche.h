#include <atomic>

#include "types.h"

int miniMax(position& pos, int tiefe, int hoehe, zuege& besterZug, int alpha, int beta, std::atomic<bool>& sucheStop);

void newGame();

extern int seldepth;
