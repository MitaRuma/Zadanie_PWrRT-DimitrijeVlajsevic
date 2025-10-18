# Jak to wszystko działa?

## Zadania z C++:  
Konkretne komentarze dotyczące poszczególnych części programu są w komentarzach w samych plikach .cpp lub .h, tutaj tylko wytłumacze ogólny sposób myślenia oraz algorytmy stosowane w rozwiązaniu zadań.  
### Zadanie 1 - Otoczka  
"Znajdź najmniejszy (najmniej liczny) podzbiór takich punktów, które otaczają wszystkie inne punkty."  
Do realizacji tego zadania użyłem algorytm ["quickhull"](https://en.wikipedia.org/wiki/Quickhull) (metoda "dziel i zwyciężaj").  
W zasadzie to jest po prostu quicksort na płaszczyźnie 2D. Szukamy skrajne 2 punkty które na pewno są na otoczce (lewy i prawy lub górny i dolny), nazwijmy je A i B. Potem dzielimy reszte punktów na te po jednej oraz drugiej stronie odcinka wyznaczonego przez te punkty. Po kazdej stronie szukamy punkt C najdalszy od odcinka AB (C dodajemy do otoczki). Powstaje trójkąt ABC w środku którego punkty można pominąć. Powtarzamy wszystko, tylko że zamiast odcinka AB bierzamy odcinki AC, CB. Dostajemy nowe najdalsze punkty itd. dopóki nie zostanie żaden punkt.  
Zapisuję punkty otoczki w tablicy. Sortuję ją tak, żeby sąsiadujące punkty otoczki były obok siebie (raczej i tak będą posortowane, ale lepiej się upewnić), ponieważ to znacznie ułatwi iteracje w kolejnym zadaniu.  
  
### Zadanie 2 - Punkty  
"Znajdź najbliższe (najmniej oddalone od siebie nawzajem) dwie proste równoległe takie, że wszystkie punkty w zbiorze leżą dokładnie na nich lub między nimi."  
Można od razu zauważyć, że jak już znaleźliśmy otoczke, to ona wystarczy do zrobienia tego zadania, nie trzeba działać na całym zbiorze punktów. Jesli cała otoczka się zawiera pomiedzy prostymi, to reszta punktów też. Podszedłem do tego zadania w następujący sposób: Prostą można prosto zdefiniować przez 2 punkty, więc w tym przypadku można wziąc kolejne odcinki tworzące otoczke (pary sąsiadujących punktow w posortowanymi punktami z pierwszego zadania), znaleść najdalszy punkt od każdego odcinka, a potem policzyc odległość między tym punktem a odcinkiem. Najmniejsza taka odległość jest rozwiązaniem zadania.  
  
### Zadanie 3 - Najbliższe punkty
"Znajdź dwa najbliżej siebie położone punkty w zbiorze. Skup się na osiągnięciu jak najniższej złożoności obliczeniowej."  
Jest to [znany problem](https://en.wikipedia.org/wiki/Closest_pair_of_points_problem).  
Tutaj, podobnie jak w zadaniu 1, użyłem metody "dziel i zwyciężaj". Sortujemy punky wg ich wartości X i bierzemy ten środkowy. Dzielimy zbiór punktow na te po lewej oraz po prawej od tej wartości. Powtarzamy rekurencyjnie dopóki nie dostaniemy max. 3 punkty po jednej stronie. W takim zbiorze szukamy najkrótszej odległosci sprawdzając ich po kolei (bruteforce). Wychodząc z rekurencji, porównujemy minimalne odległości po lewej i prawej stronie. Na koniec dostajemy odległość minimalną w lewej oraz prawej połowie zbioru punktów. Trzeba jednak sprawdzić czy akurat 2 najbliższe punkty nie są w różnych połowach zbioru (jeden po lewej a drugi po prawej). Robi się to w ten sposób, że bierzemy obecna najkrótszą długość, i uwzględniamy tylko punkty oddalone co najwyżej o tą długość od środka dzielącego zbiór na 2 części. Teraz te punkty trzeba posortować wg. ich wartości Y, a zatem dla każdego punktu sprawdzić tylko 7 najbliższych sąsiadów (jest udowodnione geometrycznie dlaczego tak jest ale nie chce mi się tutaj rozpisywać). Jest to bardzo ważne ponieważ wtedy złożóność obliczeniowa tego ostatniego kroku jest O(n), zamiast O(n^2) jeśli sprawdziamy wszystkie.  
Niech T(n) to czas działania tego algorytmu dla n punktów. Wtedy rekursywna cześć algorytmu dzieje się w takim czasie: T(n) = 2T(n/2) + O(n) => T(n) = O(nlogn). Lepiej się chyba nie da.  
  
## Zadanie STM32CubeIDE  
  
Sczerze, pierwszy raz w życiu odpaliłem ten program, więc głownie się kierowałem dokumentacją czy różnymi tutorialami na youtube. Nie za bardzo byłbym w stanie teraz powtórzyć to co zrobiłem ale ważne że działa (chyba).  
Krok po kroku co robiłem:  
1) Utworzenie projektu z mikrokontrolerem STM32F205RGT6  
2) W zakładce "System core" => RCC ustawiłem HSE na "Crystal/Ceramic Resonator"  
3) Potem w "Clock Configuration" ustawilem częstotliwość na wejściu obok HSE na 16 MHz  
4) Na takim dużym schemacie mikrokontrolera wszedłem w pin PA5 -> GPIO_Output, zostawiłem tam domyślne ustawienia/konfiguracje  
5) Potem włączyłem watchdog IWDG, ustawiłem: prescaler = 64, reload value = 1024  
6) Ctrl+S, wygenerowano większość kodu  
7) Napisałem kod dla IWDG i GPIO, oraz implementacje tego w main.c  
   7a) W gpio.c dioda mruga co 100ms, czyli jeden cykl mrugania trwa 200ms, więc częstotliwość = 5Hz  
  
Kod sie skopmilował bez żadnego problemu więc uznałem, że dobrze  
