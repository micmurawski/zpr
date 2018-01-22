# Kompilacja


Gra składa się z 2 komponentów z serwera i klienta które należy odzielnie skompilować
* Kompilacja klienta w folderze client_window należy uruchamić kolejno komendy qmake -makefile i make -j4 (przy kompilacji na 4 rdzeniach)
* Kompilacja serwera uruchamiamy komendę scons
### Przykład
* scons
* cd client_window
* qmake -makefile
* make -j4\
Wszystkie pliki zostaną skompilowane do katologu głównego

# Uruchomienie Gry
W celu uruchomienia gry należy urchomić serwer na następnie uruchomić klientów tak żeby jeden utworzył grę, a drugi do niej dołączył
* Uruchomienie serwera - ./server -s #host #port np. ./server -s 127.0.0.1 3002
* Urucomienie pliku ./server bez żadnych parametrów domyślnie uruchomi ./server -s 127.0.0.1 3002
* Uruchomienie klienta gry z utworzeniem gry - ./client -c 127.0.0.1 3002 #nazwa_gracza #nazwa_gry - Utworzenie gry o zadanej nazwie na serwerze o zadanym ip i porcie
* Uruchomienie klienta gry z dołączeniem do - ./client -j 127.0.0.1 3002 #nazwa_gracza #nazwa_gry - Dołączenie do gry o zadanej nazwie na serwerze o zadanym ip i porcie
* Wszystkie możlwości są opisane po uruchomieniu programu z parametrem -h
### Przykład
* ./server
* ./client -c 127.0.0.1 3002 gracz1 gra1 
* ./client -j 127.0.0.1 3002 gracz2 gra1 

# Opis Gry

Bedzię to turowa gra strategiczna odbywająca się na mapie w postaci grafu. Gracz będzie budował swoje statki wzamian za swoje zasoby i wysyłał je do węzłów grafu. W momencie kiedy dojdzie do spotkania staków przeciwnych graczy będzie następować wymiana ognia.

* Folder game_engine zawiera Klasy GameServer,GameClient, GameEngine.


GameServer jest to klasa dopowiedzialna za serwer gry.

 GameEngine odpowiada za przechowywanie stanu gry i generowanie nowego stanu na podstawie otrzymanych danych od graczy

GameClient  odpowiada za wastwę klienta gry

* Folder game_object zawiera klasy realizujące obiekty gry

Klasa GameObjectFactory działa jak fabryka skalowalna i generuje odpowiednie obiekty gry na podstawie otrzymanych stringów
* Folder game_order przechowuje klasę GameOrder która realizuje komendy wysyłane przez klientów gry
* Folder game_state przechowuje klasę GameState, która realizuje chwilowy stan gry, w póżniejszym czasie stan ten będzie renderowany na interfejsie gracza

* Biblioteka to osbługi TCP została pobrana, zmodyfikowana o potrzebną funkcjonalność i lokalnie skompilowana jako biblioteka statyczna z repozytorium github
https://github.com/Cylix/tacopie

* Interfejs uzytkownika będzie napisany przy wykorzystaniu biblioteki Qt w wersji 5.5
http://doc.qt.io/qt-5/linux-deployment.html

* Folder test_suite przechowuje przykładowe testy jednostkowe kompilowane do pliku wykonywalnego test_suite

