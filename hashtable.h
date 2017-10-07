#include <vector>

#include "types.h"


namespace std {
  template<>
  class hash<position> {
  public:
      size_t operator()(const position & pos) const;
  };
}

class hte {
  public:
   hte() {
     hash = 0;
     besterZug = {};
     wert = 0;
     tiefe = 0;
     Zaehler = 0;
   }
   size_t hash;
   zuege besterZug;
   int wert;
   int tiefe;
   int Zaehler;
};

class transpositionTable {
  public:
    void groesseAendern(size_t ziel);
    void loeschen();
    void naechsteRunde() {Zaehler++; };
    void schreiben(const position & pos, zuege& besterZug, int& wert, int& tiefe, int hoehe);
    bool finden(const position & pos, zuege& besterZug, int& wert, int& tiefe, int hoehe);
  private:
    std::vector<hte> table;
    int Zaehler;
};

extern transpositionTable TT;
