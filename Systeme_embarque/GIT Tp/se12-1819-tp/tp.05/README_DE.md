# TP.05 : Einführung in die Assembler Programmiersprache und dem Interfacing mit C

## Ziele

Am Ende des Labors sind die Studenten/Studentinnen fähig,

* Ein Programm in Assemblersprache zu entwerfen und zu realisieren
* Assemblerfunktionen mit C-Funktionen zu verbinden
* Ein aus Assembler und C gemischtes Programm zu debuggen
* entwickelte Komponenten aus früheren Arbeiten zu integrieren

Dauer der praktischen Arbeit

* 2 Laboreinheiten (8 Stunden) + persönliche Arbeit

Abzugeben:

* Laborbericht und den Sourcecode auf das zentralisierte Depot

## Aufgaben

Das Ziel dieses TP ist die Konzeption und Entwicklung des Spiels "Die Türme
von Hanoi" auf dem LCD OLED Display des Beaglebone in Assemblersprache.

![game](img/game.png)

Der Turm besteht aus 10 verschieden farbigen Scheiben. Das Verschieben des Turmes
wird durch das Drücken des entsprechenden Tasters gewählt.


## Nützliche Hinweise

Hier finden Sie einige Hinweise, welche die Umsetzung dieser praktischen
Arbeit erleichtert.

### Einige nützliche Funktionen, welche für die Realisation des Spieles entwickelt 
werden sollen

Hier finden sie einige Funktionen welche realisiert werden sollen, um die 
Entwicklung der Applikation zu erleichtern.

```c
/**
 * method to clear the disk located at position "height" out of the given "peg"
 */
static void clear_disk(int peg, int height);

/**
 * method to draw a "disk" on given "peg" at the specified position "height"
 */
static void draw_disk(int peg, int height, int disk);

/**
 * method to push a "disk" onto the given "peg"
 */
static void push_disk(int peg, int disk);

/**
 * method to move a "disk" out of specified peg "from" to another one "to"
 */
static void move_disk(int from, int to, int disk);

/**
 * method to draw a peg
 */
static void draw_peg(int peg);
```

Hier die Kernfunktion des Hanoi-Turmes:

```c
void tower_of_hanoi_move(int from, int to, int by, int height)
{
	if (height > 0) {
		height--;
		tower_of_hanoi_move(from, by, to, height);
		move_disk(from, to, height);
		tower_of_hanoi_move(by, to, from, height);
	}
}
```

Um die oben gezeigte Bildeinstellung auf dem LCD-Display zu erhalten, reicht es die folgende Methode zu implementieren:

```c
void tower_of_hanoi_init(int peg)
{
	display_init();

	for (int i = NUMBER_OF_PEGS-1; i>=0; i--) {
		draw_peg(i);
	}

	for (int i = TOWER_HEIGHT-1; i >= 0; i--) {
		push_disk(peg, i);
	}

	display_text(0, 0, " Welcome to ", DISPLAY_WHITE);
	display_text(0, 2, "   HANOI    ", DISPLAY_WHITE);

	display_text(0, 9, "Merry X-Mas!", DISPLAY_YELLOW);
	display_text(0,11, ":) new(Year)", DISPLAY_RED);
}
```

## Fragen

* Für die zwei Strukturen _`struct S1`_ , _`struct S2`_ und dem folgenden Code,

	```c
	struct S1 {int a;};
	struct S2 {int a; int b[100];};

	struct S1 f1();
	struct S2 f2();

	void f3 (int a, int b, int c, int d, struct S2 s);
	void f4 (int a, int b, int c, int d, const struct S2* s);
	void f5 (struct S2 s, int a, int b, int c, int d);
	void f6 (const struct S2* s, int a, int b, int c, int d);
	void f7 (struct S1 s);
	```

  geben sie die verwendete Konvention an für 

  * die Rückgabe dieser Strukturen durch die Funktionen _`f1`_ und _`f2`_
  * die Übergabe durch Wert dieser Strukturen durch die Funktionen _`f3`_ bis _`f7`_


## Aktualisierungen

* Um die spezialisierte Bibliothek des Beaglebone zu aktualisieren

    ```
    $ cd ~/workspace/se12/tp
    $ git pull upstream master
    $ make -C ~/workspace/se12/tp/bbb/source
    ```
* Um die Paths der includes in Eclipse zu aktualisieren
  * öffnen sie _`Properties`_ ihres Projektes
  * gehen sie in   _`C/C++ General`_  --> _`Paths and Symbols`_
  * öffnen sie _`Includes`_ --> _`GNU C`_
  * fügen sie _`/home/lmi/workspace/se12/bbb/source`_ hinzu

## Bedingungen

* Abgabe
    * Der Code und der Bericht werden auf das zentralisierte Git-Depot geladen
        * sources: _.../tp/tp.05_
        * Bericht: _.../tp/tp.05/doc/report.pdf_

* Frist
  * Der Code und der Bericht müssen bis spätestens 7 Tage nach dem TP 
    bis 23h59 abgegeben werden.
