# Race-trening-simulation
Symulacja treningu przed wyścigiem z wykorzystaniem wielowątkowości oraz biblioteki ncurses

### Opis projektu
W treningu przed wyścigiem biorą udział różne narodowości, każda z nich ma ograniczoną liczbę samochodów, natomiast kierowców danego kraju jest zawsze więcej niż
przydzielonych im samochodów. Na tor wyścigowy może wjechać i przebywać tam ograniczona liczba pojazdów. Przed wjechaniem i po zjechaniu z toru należy przejechać przez
obszar mechanika, który sprawdza stan techniczny pojazdu. W obszarze tym może na raz znajdować się maksymalnie 1 samochód.

Na podstawie powyższego opisu można wydzielić poszczególne części programu:
- **Wątkami** będą kierowcy rajdowi;
- **Zasobem** będzie pojazd, miejsce u mechanika oraz miejsce na torze;
- **Sekcje krytyczne**: wejście do samochodu przez kierowcę, wjazd do obszaru mechanika oraz
wjazd na tor;
- **Zmienne warunkowe**: sygnalizacja zwolnienia się miejsca na torze, u mechanika oraz
informacja o zwolnieniu samochodu przez kierowcę;
- **Zagłodzenie** może wystąpić w przypadku, gdy kierowca nie wsiada do samochodu od
dłuższego czasu, bądź samochód nie jest w stanie wjechać na tor;
- **Zakleszczenie**: sytuacja, w której tor jest zapełniony, 1 samochód czeka u mechanika na
wjazd natomiast drugi chce zjechać lecz nie może z powodu braku miejsca.

Poglądowe działanie programu:

https://user-images.githubusercontent.com/49610728/195554368-4e723a59-7fb9-4eed-82bd-2b27b052e4b4.mp4

