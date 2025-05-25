# Dokumentacja techniczna — Projekt czatu klient-serwer (C++ / WinSock)

## Problem komunikacji klient–serwer

Problem polegający na zapewnieniu niezawodnej, dwukierunkowej komunikacji pomiędzy wieloma klientami a centralnym serwerem.

W tym przypadku klienci mają możliwość wysyłania wiadomości, które są przekazywane przez serwer do pozostałych uczestników czatu. Wymaga to obsługi wielu wątków oraz synchronizacji zasobów współdzielonych (lista klientów, dostęp do gniazdek sieciowych).

### Od strony informatycznej

Zadanie polega na stworzeniu aplikacji sieciowej TCP/IP, gdzie serwer akceptuje połączenia wielu klientów i przekazuje wiadomości od każdego z nich do pozostałych. Konieczne jest zapewnienie bezpieczeństwa danych (wielowątkowość), obsługa błędów oraz właściwe zarządzanie pamięcią i zasobami systemowymi (gniazda, mutexy).

### Rozwiązanie

Problem został rozwiązany przy użyciu **WinSock2** oraz **standardowej biblioteki C++**. Każdy klient jest obsługiwany w osobnym wątku. Synchronizacja dostępu do współdzielonej listy połączeń realizowana jest za pomocą `std::mutex`. Serwer przekazuje otrzymaną wiadomość do wszystkich klientów z wyjątkiem nadawcy.

---

## Dokumentacja

### Plik: `server.cpp`

**Opis:** Serwer czatu TCP. Obsługuje wielu klientów, zarządza połączeniami i rozsyła wiadomości między nimi.

#### Funkcje i główne elementy:

- `broadcast(const std::string&, SOCKET)`  
  Wysyła wiadomość do wszystkich klientów poza nadawcą. Dostęp do listy klientów zabezpieczony przez mutex.

- `handle_client(SOCKET)`  
  Funkcja uruchamiana w osobnym wątku dla każdego klienta. Odbiera wiadomości i przekazuje je do funkcji `broadcast`. Po rozłączeniu klienta usuwa jego socket z listy i zamyka go.

- `main()`  
  Inicjalizuje bibliotekę WinSock, tworzy socket serwera, bindowanie i nasłuch. Akceptuje nowych klientów i uruchamia dla nich wątki.

---

### Plik: `client.cpp`

**Opis:** Klient czatu TCP. Łączy się z serwerem, wysyła wiadomości i odbiera komunikaty od innych klientów.

#### Funkcje i główne elementy:

- `receive_messages(SOCKET)`  
  Działa w osobnym wątku. Nasłuchuje danych z serwera i wypisuje je na ekran. Bufor zabezpieczony i odświeżany za pomocą `std::cout.flush()`.

- `main()`  
  Inicjalizuje połączenie z serwerem. Uruchamia wątek nasłuchujący odpowiedzi. W pętli głównej pozwala użytkownikowi wpisywać wiadomości, które są następnie wysyłane do serwera. Komenda `/exit` rozłącza klienta.

---

## Użyte technologie i mechanizmy

- **WinSock2** — do obsługi połączeń TCP/IP.
- **std::thread** — do równoległego przetwarzania połączeń.
- **std::mutex** — synchronizacja przy wspólnej liście klientów.
- **std::vector<SOCKET> clients** — dynamiczna lista aktywnych klientów.
- **Multithreading** — serwer jednocześnie obsługuje wielu klientów.

