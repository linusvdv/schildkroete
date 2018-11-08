# Schildkroete

Schildkroete ist ein Schachprogramm geschrieben von linusvdv in C++. Linus ist 12 Jahre alt.

Um gegen Schildkroete zu spielen brauchst du ein UCI GUI. 

Mein Schachprogramm ist langsam, deshalb heisst sie [Schildkroete](https://de.wikipedia.org/wiki/Schildkr%C3%B6ten). Trotzdem ist es nicht leicht gegen Schildkroete zu gewinnen.

## kompilieren auf Linux

```
git clone https://github.com/linusvdv/schildkroete.git
cd schildkroete
make -j opt=yes
```

## gegen schildkroete spielen

xboard muss installiert sein.

```xboard -fUCI -fcp ./schildkroete  -sUCI -scp ./schildkroete```
