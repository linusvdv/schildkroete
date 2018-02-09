EXE=schildkroete
LDLIBS=-lpthread
RM=rm -f

CPPFLAGS=-std=c++11
ifeq ($(opt),no)
    CXXFLAGS=-Wall -Wextra -g3 -O0 -std=c++11
else
  ifeq ($(opt),nolto)
    CXXFLAGS=-Wall -Wextra -g3 -O3 -std=c++11
  else
    CXXFLAGS=-Wall -Wextra -g3 -O3 -flto -std=c++11
  endif
endif
LDFLAGS=$(CXXFLAGS)


SRCS=mensch.cpp istRemis.cpp rokade.cpp feld.cpp main.cpp zugmacher.cpp hashtable.cpp\
     FEN_leser.cpp FEN_schreiber.cpp echt_zug.cpp perft.cpp stet_der_koenig_schach.cpp alleZuege.cpp suche.cpp bewertung.cpp

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
