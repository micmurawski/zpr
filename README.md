* Opis Gry

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