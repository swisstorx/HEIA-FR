# TP.03 : Implementierung von Peripheriegeräten mit C

## Ziele

Am Ende des Labors sind die Studenten/Studentinnen fähig,

* Modulare Programme (mehrere Dateien) in C zu konzipieren und zu realisieren
* Ein C Programm zu debuggen
* Den Gebrauch einer seriellen Schnittstelle (UART) zu beschreiben
  (vorbereitendes Studium der Signale und des Protokolls)
* Die Prinzipien eines seriellen Busses (I2C) zu beschreiben
  (vorbereitendes Studium der Signale und des Protokolls)
* Die Prinzipien eines seriellen Busses (SPI) zu beschreiben
  (vorbereitendes Studium der Signale und des Protokolls)
* Eine Kommandozeile durch die serielle Schnittstelle (UART) zu konzipieren
* Implementierung eines Thermometers mit einem I2C-Bus
* Implementierung eines LCD-Displays mit einem SPI-Bus
* Das datasheet eines einfachen elektronischen Bauteils zu verstehen

Dauer der praktischen Arbeit

* 2 Laboreinheiten (8 Stunden) + persönliche Arbeit

Abzugeben:

* Laborbericht und den Sourcecode auf das zentralisierte Depot

## Aufgaben

In diesem TP soll eine modulare Applikation in C konzipiert und realisiert werden,
welche es erlaubt, Peripheriegeräte mit I2C- und SPI-Bus auf der Erweitungskarte
zu implementieren. Es soll auch eine Kommandozeile, welche die serielle Schnittstelle
des Beaglebone benutzt, realisiert werden.

Die zwei ausgewählten Peripheriegeräte sind: 
* das LCD-Display OLED-C, welcher mit dem SPI-Bus verbunden ist.
  dieses wird auf den slot 1 (CAPE1) der Erweitungskarte gesteckt.
* das Thermo3 Thermometer, welches mit dem I2C-Bus verbunden ist.
  dieses wird auf den slot 2 (CAPE2) der Erweitungskarte gesteckt.

Das Programm besteht daraus, einen Digitalthermometer zu implementieren,
welcher die aktuell gemessene Temperatur sowie die Minimal- und Maximalwerte anzeigt.
(siehe folgende Abbildung)
Die Kommandozeile erlaubt es, mit dem Programm zu interagieren.

![application](img/bbb.jpg)

Die Spezifikationen des Programmes:

* Thermometer
  * Die gemessene Temperatur des I2C-Thermometers wird konvertiert und in
	Grad Celcius angezeigt.
  * Die Minimal- und Maximalwerte werden in Echtzeit berechnet und in
	Grad Celcius angezeigt.
	
* LCD-Display
  * Das LCD-Display wird in zwei Teile unterteilt:
    * auf der linken Seite wird die aktuelle Temperatur, sowie die
	  Minimal- und Maximalwerte im Stil eines analogen Thermometers
	  von -20 bis +40°C angezeigt.
	* auf der rechten Seite werden die Temperaturen in Textform angezeigt (ascii).

  * Diese 3 Temperaturen werden in verschiedenen Farben angezeigt.
  
  * Die Orientierung der Anzeige soll so gewählt sein, dass wenn man das LCD-Display
    anschaut, es auch möglich sein soll den Text auf dem PCB der Karte zu lesen.
	d.h. Taster, 7-Segmentanzeige und Drehencoder befinden sich oberhalb des click boards.

* Kommandozeile (CLI)
  * Mindestens 2 Befehle müssen implementiert werden:
    * einen Befehl, um die Farbe des Thermometers und die Farben der
	  verschiedenen Temperaturen zu wählen. Eine Option soll erlauben,
	  die Standardfarben auszuwählen.
	* einen Befehl, um die Minimal- und Maximalwerte auf die aktuelle
	  Temperatur zu initialisieren.

## Nützliche Hinweise

Hier finden Sie einige Hinweise, welche die Umsetzung dieser praktischen
Arbeit erleichtert.

### Kommandozeile (ligne de commande)

Der µP TI AM3358 des Beaglebone ist mit 6 seriellen Schnittstellen ausgestattet.
Diese werden mit dem Modul _`am335x_uart`_ der Bibliothek _`bbb`_ gesteuert.
UART_0 dient als Konsolenschnittstelle. Diese ist eine serielle Schnittstelle,
welche von Betriebssystemen als Kommandozeile verwendet wird.

Um die Kommandozeile zu implementieren werden 3 Bibliotheken zu Verfügung
gestellt, um die Zeichen welche getippt werden zu erfassen:

* _`am335x_console`_ der Bibliothek _`bbb`_ bietet eine Low-Level-Schnittstelle,
  welche speziell für das Beaglebone entwickelt wurde.
  
* _`stdio`_ der Standartbibliothek von C _`glibc`_ bietet eine sehr
  leistungsstarke Schnittstelle mit Methoden wie _`printf`_, _`scanf`_,
  _`getchar`_, _`putchar`_ oder _`puts`_.
  
* Die Bibliothek _`fileio`_ von _`Unix`_ bietet nicht-blockierende Dienste wie
  _`read`_ und _`write`_ an, welche die Implementierung der Kommandozeile
  vereinfacht. Um auf die Konsole zuzugreifen, muss man nur die virtuelle
  Datei _`/dev/console`_ öffnen.
  
Die Bibliothek _`getopt`_ erlaubt es, Argumente in der Kommandozeile auf
sehr elegante Weise zu bearbeiten.

### I2C-Thermometer

Der Prozessor besitzt 3 I2C-Kontroller. Der 2. Kontroller (Bus I2C2) dient
als Schnittstelle zwischen dem µP und den Peripheriegeräten _microBUS_,
welche sich auf den slots "CAPE1" und "CAPE2" der Erweitungskarte befinden.
Das Modul _`am335x_i2c`_ der Bibliothek _`bbb`_ bietet die nötigen Dienste
zur Steuerung der Peripheriegeräte an.

Das click board "Thermo3" (I2C Gerät) ermöglicht es, die Umgebungstemperatur
zu erfassen. Die technischen Details zu diesem Gerät sind in den Kursunterlagen
oder direkt auf Gitlab ([se12/docs/01_datasheets/03_i2c/04_tmp102](https://gitlab.forge.hefr.ch/se12-1819/se12/blob/master/docs/01_datasheets/03_i2c/04_tmp102.pdf)) zu finden.

### LCD-Display OLED

Der Prozessor besitzt auch 2 SPI-Kontroller. Der SPI-Bus N°1 ist auch auf
den slots "CAPE1" und "CAPE2" der Erweitungskarte vorhanden.
Das Modul _`am335x_spi`_ der Bibliothek _`bbb`_ bietet die nötigen Dienste
zur Steuerung der Peripheriegeräte an.

Das click board "OLED-C" (SPI-Gerät) bietet einen LCD-Display von
96x96 Pixel in RGB565 an. Die technischen Details zu diesem Display sind
in den Kursunterlagen oder direkt auf Gitlab ([se12/docs/01_datasheets/04_oled](https://gitlab.forge.hefr.ch/se12-1819/se12/tree/master/docs/01_datasheets/04_oled)).
Das Modul _`oled`_ bietet die Dienste zur Steuerung dieser Karte an.
Jedoch muss diese zwingend auf "CAPE1" verbunden sein.

Die Schriftart _`font_8x8`_ bietet eine "bitmap" für jeden der 256 Charakter
des ascii-Codes an. Diese kann natürlich auf die Bedürfnisse des Projektes
angepasst werden.

## Fragen

* Was sind die Haupteigenschaften (Signale und Protokoll) der
  Kommunikationsschnittstellen UART, I2C und SPI ?

* Wie kann man ein Bild drehen bevor es auf dem LCD-Display
  angezeigt wird ?

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
        * sources: _.../tp/tp.03_
        * Bericht: _.../tp/tp.03/doc/report.pdf_

* Frist
  * Der Code und der Bericht müssen bis spätestens 20 Tage nach dem TP 
    bis 23h59 abgegeben werden.