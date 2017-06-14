#!/bin/bash

function perft {
  echo "test $1, tiefe $2"
  zuege=`printf "position fen $1\nperft $2\nquit\n" | ./schildkroete | grep "= perft" | awk '{print $1}'`
  echo "schildkroete: $zuege , echt $3"
  if [ "$zuege" != "$3" ]; then
     echo "Falsch!"
     exit 1
  else
     printf "OK\n\n"
  fi
}

perft "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" "3" 8902
perft "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" "4" 197281
perft "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" "5" 4865609
perft "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0" "3" 97862
perft "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0" "4" 4085603
perft "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0"  5 674624
perft "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1" 4 422333
perft "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8" 4 2103487
perft "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10" 4 3894594
