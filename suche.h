#include <atomic>

#include "types.h"

int miniMax(position& pos, int tiefe, int hoehe, zuege& besterZug, int alpha, int beta, std::atomic<bool>& sucheStop, int voheriger_zug);

void newGame();

extern int seldepth;
