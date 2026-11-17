@echo off
set CXX="C:\Users\kubao\Documents\sfml\mingw64\bin\g++"
set SFML="C:\Users\kubao\Documents\sfml\SFML-3.1.0"


%CXX% -std=c++17 -c main.cpp -I%SFML%\include


%CXX% main.o -o sfml-app -L%SFML%\lib -lsfml-graphics -lsfml-window -lsfml-system

pause