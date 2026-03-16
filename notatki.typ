#set text(lang: "pl")
#set document(author: "Just Edizi", title: "Notatki z Analizy Matematycznej")

= Analiza Matematyczna - Notatki

#outline()

== Ciągi Liczbowe

=== Podstawowe Definicje

==== Definicja Ciągu i Podciągu
*Ciągiem liczbowym* nazywamy funkcję $f: NN -> RR$. Wartość $f(n)$ oznaczamy jako $a_n$ i nazywamy $n$-tym wyrazem ciągu. Ciąg oznaczamy jako $(a_n)_(n in NN)$ lub krótko $(a_n)$. 

Niech $(a_n)$ będzie ciągiem, a $h: NN -> NN$ funkcją ściśle rosnącą (tj. $k_1 < k_2 => h(k_1) < h(k_2)$).
Ciąg $(a_(h(k)))_(k in NN)$, oznaczany zazwyczaj jako $(a_(n_k))$, gdzie $n_k = h(k)$, nazywamy *podciągiem* ciągu $(a_n)$.

==== Ograniczoność Ciągu
Ciąg $(a_n)$ nazywamy:
- *Ograniczonym z góry*, jeżeli $exists M in RR, forall n in NN: a_n <= M$.
- *Ograniczonym z dołu*, jeżeli $exists m in RR, forall n in NN: a_n >= m$.
- *Ograniczonym*, jeżeli jest ograniczony z góry i z dołu, co jest równoważne warunkowi: $exists M > 0, forall n in NN: |a_n| <= M$.

==== Monotoniczność Ciągu
Ciąg $(a_n)$ nazywamy:
- *Rosnącym*, jeżeli $forall n in NN: a_n < a_(n+1)$.
- *Niemalejącym*, jeżeli $forall n in NN: a_n <= a_(n+1)$.
- *Malejącym*, jeżeli $forall n in NN: a_n > a_(n+1)$.
- *Nierosnącym*, jeżeli $forall n in NN: a_n >= a_(n+1)$.
Monotoniczność badamy najczęściej analizując znak różnicy $a_(n+1) - a_n$ lub, dla ciągów o wyrazach dodatnich, porównując iloraz $a_(n+1) / a_n$ z $1$.

=== Granica Ciągu

==== Granica Właściwa
Liczbę $g in RR$ nazywamy *granicą właściwą* ciągu $(a_n)$, co zapisujemy $lim_(n->oo) a_n = g$ (lub $a_n -> g$), jeżeli:
$ forall epsilon > 0, exists N in NN, forall n >= N: |a_n - g| < epsilon $
Ciąg posiadający granicę właściwą nazywamy *ciągiem zbieżnym*.

==== Granica Niewłaściwa
Mówimy, że ciąg $(a_n)$ ma *granicę niewłaściwą* $+oo$ (odpowiednio $-oo$), co zapisujemy $lim_(n->oo) a_n = +oo$ (odp. $lim_(n->oo) a_n = -oo$), jeżeli:
$ forall M in RR, exists N in NN, forall n >= N: a_n >= M quad text("(odp. " ) a_n <= M text(")") $
Ciąg mający granicę niewłaściwą nazywamy *rozbieżnym do $+oo$* (odp. $-oo$). Ciągi nieposiadające żadnej granicy (właściwej ani niewłaściwej) nazywamy *rozbieżnymi*.

=== Własności i Twierdzenia o Granicach

==== Podstawowe Własności
1. *Jednoznaczność:* Każdy ciąg ma co najwyżej jedną granicę (właściwą lub niewłaściwą).
2. *Związek z podciągami:* Jeżeli $lim_(n->oo) a_n = g$ (właściwa lub niewłaściwa), to każdy podciąg $(a_(n_k))$ tego ciągu jest zbieżny do tej samej granicy: $lim_(k->oo) a_(n_k) = g$.
3. *Ograniczoność:* Każdy ciąg zbieżny (do granicy właściwej) jest ograniczony. (Uwaga: implikacja odwrotna nie zachodzi, np. $a_n = (-1)^n$).

==== Arytmetyka Granic
Niech $(a_n), (b_n)$ będą ciągami zbieżnymi, gdzie $lim_(n->oo) a_n = a$ oraz $lim_(n->oo) b_n = b$. Wówczas:
- $lim_(n->oo) |a_n| = |a|$
- $lim_(n->oo) (a_n plus.minus b_n) = a plus.minus b$
- $lim_(n->oo) (a_n dot b_n) = a dot b$
- $lim_(n->oo) a_n / b_n = a / b$, o ile $b != 0$ oraz $forall n in NN: b_n != 0$.
*(Uwaga: Powyższe wzory można uogólnić na granice niewłaściwe, pamiętając o symbolach nieoznaczonych typu: $oo - oo, 0 dot oo, oo/oo, 0/0, 1^oo, 0^0, oo^0$).*

==== Ważne Twierdzenia
- *O granicy iloczynu ciągu ograniczonego i zbieżnego do 0:* Jeżeli ciąg $(a_n)$ jest zbieżny do 0, a ciąg $(b_n)$ jest ograniczony, to ciąg $(a_n dot b_n)$ jest zbieżny do 0. \ 
  _Przykład:_ $lim_(n->oo) (sin n) / n = 0$, bo $1/n -> 0$, a $sin n$ jest ograniczone.
- *O trzech ciągach:* Jeżeli $exists n_0 in NN, forall n >= n_0: a_n <= b_n <= c_n$ oraz $lim_(n->oo) a_n = lim_(n->oo) c_n = g$, to $lim_(n->oo) b_n = g$.
- *O dwóch ciągach (dla granic niewłaściwych):* Jeżeli $exists n_0 in NN, forall n >= n_0: a_n <= b_n$ oraz $lim_(n->oo) a_n = +oo$, to $lim_(n->oo) b_n = +oo$. (Analogicznie dla $-oo$).
- *Zachowanie nierówności:* Jeżeli $lim_(n->oo) a_n = a$ oraz $lim_(n->oo) b_n = b$, a dla dostatecznie dużych $n$ zachodzi $a_n <= b_n$, to $a <= b$. (Ostra nierówność $a_n < b_n$ może w granicy dać równość).
- *Zbieżność ciągów monotonicznych:* Każdy ciąg monotoniczny i ograniczony jest zbieżny.
  - Ciąg niemalejący i ograniczony z góry jest zbieżny do swojego kresu górnego ($sup_(n) a_n$).
  - Ciąg nierosnący i ograniczony z dołu jest zbieżny do swojego kresu dolnego ($inf_(n) a_n$).

=== Granice Specjalne i Liczba $e$
Ważne granice, przydatne do rozwiązywania problemów (skala wzrostu funkcji):
1. $lim_(n->oo) 1/n^alpha = 0$ dla $alpha > 0$
2. $lim_(n->oo) q^n = 0$ dla $|q| < 1$; $+oo$ dla $q > 1$; nie istnieje dla $q <= -1$.
3. $lim_(n->oo) root(n, a) = 1$ dla $a > 0$
4. $lim_(n->oo) root(n, n) = 1$
5. $lim_(n->oo) n^alpha / a^n = 0$ dla $a > 1, alpha in RR$ (funkcja wykładnicza asymtotycznie rośnie szybciej niż potęgowa)
6. $lim_(n->oo) a^n / n! = 0$ dla $a in RR$ (silnia rośnie szybciej niż funkcja wykładnicza)

*Definicja liczby $e$:*
Ciąg $e_n = (1 + 1/n)^n$ jest rosnący i ograniczony z góry, zatem na mocy twierdzenia o zbieżności ciągów monotonicznych jest zbieżny. Jego granicę oznaczamy literą $e$.
$ lim_(n->oo) (1 + 1/n)^n = e approx 2.71828... $
Własność uogólniona: Jeżeli $lim_(n->oo) |a_n| = +oo$, to $lim_(n->oo) (1 + 1/a_n)^(a_n) = e$.

=== Głębsze Własności Ciągów

==== Twierdzenie Bolzano-Weierstrassa
Każdy ciąg ograniczony (w $RR$) zawiera podciąg zbieżny.
*(Lemat: Każdy ciąg liczbowy zawiera podciąg monotoniczny).*

==== Ciągi Cauchy'ego
Ciąg $(a_n)$ nazywamy *ciągiem Cauchy'ego*, jeżeli odległość między dowolnymi dwoma jego wyrazami o dostatecznie wysokich indeksach staje się dowolnie mała:
$ forall epsilon > 0, exists N in NN, forall n, m >= N: |a_n - a_m| < epsilon $
*Twierdzenie o zupełności $RR$:* Przestrzeń liczb rzeczywistych jest zupełna, co oznacza, że ciąg liczbowy jest zbieżny w $RR$ wtedy i tylko wtedy, gdy jest ciągiem Cauchy'ego.

=== Punkty Skupienia, Granica Górna i Dolna

==== Punkt Skupienia
Punkt $a in RR$ nazywamy *punktem skupienia* ciągu $(a_n)$, jeżeli istnieje podciąg $(a_(n_k))$ zbieżny do $a$. Dopuszczamy również niewłaściwe punkty skupienia ($+oo, -oo$). Niech $S$ oznacza zbiór wszystkich punktów skupienia ciągu $(a_n)$.

==== Granica Górna i Dolna
- *Granicą dolną* ciągu $(a_n)$ nazywamy kres dolny zbioru jego punktów skupienia $S$: 
  $ liminf_(n->oo) a_n = inf S $
- *Granicą górną* ciągu $(a_n)$ nazywamy kres górny zbioru $S$: 
  $ limsup_(n->oo) a_n = sup S $

*Przykład:* Dla ciągu naprzemiennego $a_n = (-1)^n$, zbiór punktów skupienia to $S = {-1, 1}$. Wtedy $liminf_(n->oo) (-1)^n = -1$, a $limsup_(n->oo) (-1)^n = 1$.

*Związek ze zbieżnością:* Ciąg $(a_n)$ ma granicę (właściwą lub niewłaściwą) $g$ wtedy i tylko wtedy, gdy jego granica dolna jest równa granicy górnej i wynosi $g$:
$ liminf_(n->oo) a_n = limsup_(n->oo) a_n = g $

== Funkcje

=== Definicje

=== Twierdzenia

=== Przykłady