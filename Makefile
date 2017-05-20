CC=gcc
CXX=g++
RM=rm -f
CXXFLAGS=-g3 -O3 -flto -std=c++11
CPPFLAGS=-std=c++11
LDFLAGS=-g3 -O3 -flto -std=c++11
LDLIBS=
EXE=schildkroete
RM=rm -f

SRCS=mensch.cpp uuebersetzer.cpp drei_zuege_wiederholung.cpp rokade.cpp feld.cpp main.cpp\
     FEN_leser.cpp  echt_zug.cpp random_namber_zuege.cpp perft.cpp stet_der_koenig_schach.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^ >>./.depend;

clean:
	$(RM) $(OBJS) $(EXE) .depend

distclean: clean
	$(RM) *~ .depend

include .depend
