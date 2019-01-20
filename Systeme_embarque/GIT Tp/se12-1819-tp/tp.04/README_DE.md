# TP.04 : Implementieren eines Hardware-Timers in C

## Ziele

Am Ende des Labors sind die Studenten/Studentinnen fähig,

* Modulare Programme (mehrere Dateien) in C zu konzipieren und zu realisieren
* Ein C Programm zu debuggen
* Einen Peripherie-Treiber in C zu konzipieren und realisieren
* Einen Treiber für den DMTimer des AM3358 µP zu konzipieren
* Komponenten von früheren Arbeiten zu integrieren
* Das Datasheet eines Komponenten des Mikroprozessors zu verstehen

Dauer der praktischen Arbeit

* 1 Laboreinheiten (4 Stunden) + persönliche Arbeit

Abzugeben:

* Laborbericht und den Sourcecode auf das zentralisierte Depot

## Aufgaben

Das Ziel dieses TP ist die Konzeption und Entwicklung eines Spieles, welches
die Reaktionszeit einer Person beim Aufleuchten eines Lichtsignales misst.

Für die Entwicklung dieser Applikation soll ein Taster, das OLED LED-Display
und der Timer des µP TI AM3358 verwendet werden.

Spezifikationen der Anwendung:

* Auslöser
  * Das Drücken eines Tasters aktiviert das Spiel
  * Eine Nachricht, dass das Spiel anfängt, wird auf dem Display gezeigt

* Reflex
  * Nach einer zufälligen Zeit zwischen 500 und 2500 ms wird eine neue
    Nachricht auf dem Display angezeigt
  * Ein erste Zähler nimmt den aktuellen Wert des µP-Timers an
  * Nachdem man den Taster losgelassen hat, nimmt ein zweiter Zähler den
    neuen Wert des Timers an
  * Die Differenz der zwei Zähler ergibt dann die Reaktionszeit

* Resultat
  * Die Reaktionszeit wird in ms auf dem Display angezeigt
  * Ein erneutes Drücken auf den Taster startet das Spiel neu


Taktgeber (Clock)

  * Der Timer DMTimer2 des AM3358 µP dient als Taktgeber für die Applikation

  * Der Peripherie-Treiber steuert alle 6 Timer des µP,
    DMTimer 2 bis 7 und bietet die folgenden Funktionen an:
	* Eine Methode für die Initialisierung eines Timers
	* Eine Methode, um den aktuellen Wert eines Timers zu lesen
	* Eine Methode, um die Taktfrequenz eines Timers zu lesen

  * Das korrekte Funktionieren des Treibers muss bestätigt werden

## Nützliche Hinweise

Hier finden Sie einige Hinweise, welche die Umsetzung dieser praktischen
Arbeit erleichtert.

### Die Timer des AM3358 µP

Der µP verfügt über 8 verschiedene Timer (DMTimer 0 bis 7). Die Timer
2 bis 7 sind identisch. Die folgende Abbildung "Integration" zeigt deren
Integration im TI AM3358 µP.

Wie auf der Abbildung "Integration" gezeigt, erhalten die Timer ihre Clock vom
Modul _PRCM_. Dieses Modul bietet 3 verschiedene Clocks an, _CLK_M_OSC_ zu 24MHz,
_CLK_32KHz_ und eine externe Clock.
Das Modul _`<am335x_clock.h>`_ stellt die notwendigen Dienste zum Benutzen der
verschiedenen Clocks des µP-Controllers zur Verfügung. Die Methode 
_`am335x_clock_enable_timer_module(enum am335x_clock_timer_modules module)`_ 
erlaubt es, die Clock _CLK_M_OSC_ auszuwählen und den Takt des ausgewählten
Timers anzugeben.

![integration](img/integration.png)

([ref: se12/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf, page 4328](https://gitlab.forge.hefr.ch/se12-1819/se12/blob/master/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf))

### Das Schema des DMTimer 2 bis 7

Die folgende Abbildung "dmtimer" zeigt das Schema des DMTimers 2 bis 7 des 
AM3358 µP. Lediglich die Funktion _counter_ mit auto-reload und den Blöcken
_Prescaler_ und _Timer Counter_, sowie die Register _tclr_, _ttgr_, _tldr_, _tcrr_ 
und _tiocp_cfg_ werden bei der Realisierung dieses Projektes nötig sein. Die Logik
für die Unterbrechung (Interruption) ist für das Projekt nicht nützlich.

![dmtimer](img/dmtimer.png)

([ref: se12/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf, page 4326](https://gitlab.forge.hefr.ch/se12-1819/se12/blob/master/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf))

### Der Zählermodus des DMTimers

Die folgende Abbildung "Zählermodus" zeigt den Modus _Zähler_ der DMTimer.
In diesem Modus inkrementiert der Timer den Inhalt des Registers _tccr_ zu der
Taktfrequenz der Clock (in unserem Fall 24MHz), bis der Overflow-Wert 0xffff'ffff
erreicht ist.

Wenn man das Register _tclr_ mit dem Bit _AR_ auf 1 konfiguriert, wird der
Controller das Register _tccr_ mit dem Wert des Registers _tldr_ überschreiben.
Dieser Betriebsmodus ermöglicht es, einen Timer zu erhalten, welcher während einer
Periode von ca. 3 Minuten unendlich lange zählt.  

![mode compteur](img/counter_mode.png)

([ref: se12/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf, chapitre 20.1.3.1, page 4331](https://gitlab.forge.hefr.ch/se12-1819/se12/blob/master/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf))

### Die Register der DMTimer 2 bis 7

Die folgende Abbildung "registers" zeigt die Register der DMTimer 2 bis 7.

Diese Register befinden sich im adressierbaren Bereich des µP an den folgenden Adressen (siehe Seiten 181-182)

* DMTimer2 : `0x4804_0000 - 0x4804_0FFF`
* DMTimer3 : `0x4804_2000 - 0x4804_2FFF`
* DMTimer4 : `0x4804_4000 - 0x4804_4FFF`
* DMTimer5 : `0x4804_6000 - 0x4804_6FFF`
* DMTimer6 : `0x4804_6000 - 0x4804_6FFF`
* DMTimer7 : `0x4804_A000 - 0x4804_AFFF`

![registers](img/regs.png)

([ref: se12/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf, page 4340](https://gitlab.forge.hefr.ch/se12-1819/se12/blob/master/docs/01_datasheets/01_am335x/06_am335x_technical_reference_manual.pdf))

## Fragen

* Was ist die Bedeutung der Qualifiers _`volatile`_ und dessen Nutzen, wenn
  dieser an einen Pointer gebunden ist ?
* Wie werden die Felder (Elemente) einer Struktur im Speicher abgelegt ?
* Wie kann man die im Speicherbereich des µP abgelegten Register 
  eines Peripherie-Controllers und deren Werte auf effiziente Weise definieren ? 
* Wie kann man auf diese Register zugreifen ?
* Bei einer maximalen Frequenz von 24MHz, erlaubt es der Zähler des Timers nur in
  Intervallen von ca. 3 Minuten zu zählen. Beschreiben Sie den Algorithmus, welcher
  implementiert werden muss, wenn man während mehrerer Jahre mit der gleichen
  Genauigkeit zählen will.

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

        * sources: _.../tp/tp.04_
        * Bericht: _.../tp/tp.04/doc/report.pdf_

* Frist

  * Der Code und der Bericht müssen bis spätestens 7 Tage nach dem TP 
    bis 23h59 abgegeben werden.
