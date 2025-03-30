# Problem Filozofów - Dokumentacja

## Wstęp
Celem tego programu jest rozwiązanie klasycznego problemu filozofów, w którym kilku filozofów dzieli się widelcami podczas posiłku. Program używa wątków do symulacji działań filozofów (myślenie i jedzenie), zapewniając synchronizację między nimi oraz unikanie zakleszczeń.

## Opis problemu
Problem filozofów polega na tym, że kilku filozofów siedzi przy stole i na przemian myśli i je, ale do jedzenia potrzebują dwóch widelców, które muszą dzielić z innymi filozofami. Problemem jest zapewnienie, by nie doszło do zakleszczenia (deadlock) lub głodzenia (starvation) filozofów.

## Instrukcje uruchomienia
Aby uruchomić program:
1. Zainstaluj kompilator obsługujący C++11 lub nowszy.
2. Skompiluj program:
    g++ main.cpp Table.cpp Philosopher.cpp -o philosophers -pthread
3. Uruchom program z liczbą filozofów jako argumentem:
    ./philosophers 5
4. Program będzie symulował filozofów przez 30 sekund.

## Opis programu
Program składa się z trzech głównych plików:
- **main.cpp** - zawiera funkcję główną, inicjalizującą liczbę filozofów i rozpoczynającą symulację.
- **Table.cpp** - klasa `Table`, która zarządza filozofami i widelcami, zapewniając synchronizację.
- **Philosopher.cpp** - klasa `Philosopher`, która symuluje życie filozofa (myślenie, jedzenie).

## Wątki i ich reprezentacja
Program używa wątków do reprezentacji filozofów. Każdy filozof działa w osobnym wątku:
```c++
philosophers.emplace_back([this, i]() {
    Philosopher p(i, forks[i], forks[(i + 1) % numPhilosophers]);
    p.philosopherLife();
});
```

## Sekcje krytyczne i ich rozwiązanie
- **Mutexy dla widelców**: Każdy widelec jest reprezentowany przez mutex, co zapewnia, że filozofowie nie będą jednocześnie go używać.
- **Zapobieganie zakleszczeniu**: Filozofowie używają std::lock() do równoczesnego podnoszenia dwóch widelców, co zapobiega zakleszczeniu.
- **Użycie std::lock_guard**: Zamyka widelce na czas jedzenia, zapewniając automatyczne zwolnienie mutexów po zakończeniu jedzenia.

## Wnioski
Program implementuje rozwiązanie problemu filozofów za pomocą wątków i mutexów, zapewniając synchronizację i unikanie zakleszczenia. Można go rozbudować o zmienne warunkowe, które pozwolą filozofom czekać na dostępność widelca, co mogłoby poprawić efektywność.
