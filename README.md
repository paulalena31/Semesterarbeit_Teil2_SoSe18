# Dokumentation

### Paulas_Play

##### Installation
1. Projekt herunterladen und die zip. Datei entpacken
2. .pro-Datei in QT öffnen
3. Kompilieren (getestet mit Desktop Qt 4.4.1 MSVC2017 64bit)

##### Benutzung:

+ Klick auf **Start** startet das Spiel
+ Über **Save** und **Load** kann der Spielstand gespeichert und geladen werden.
+ Der Spieler lässt sich mit den Pfeiltasten ← → steuern
+ Ziel ist es, den herunterfallenden Objekten auszuweichen 
+ Für jedes Objekt dem ausgewichen wurde, sammelt der Spieler Punkte 
+ Neben der Punktzahl wird auch die Spielzeit in Sekunden abgegeben, sobald das Spiel gestartet wird.
+ Durch **Stop** kann das Spiel angehalten werden
+ Durch **Leave** kann das Spiel verlassen werden

##### Spielfunktion

1. die class _meinWidget_ enthält den grundlegenden Fensteraufbau mit den Start-, Stop-, Save-, Load- und Leave-Buttons.

2. die class _zeichenFeld_ 
+ In zeichenFeld::paintEvent(QPaintEvent *event) wird der Avatar, die herunterfallenden Objekte, die Lifes und der Punktecounter eingefügt
+ spielFeld::serialize(QFile &file) und spielFeld::deserialize(QFile &file) 
+ Für das Speichern und Laden eines Savegame: Bringen Daten zur Position aller Elemente, den Punktestand und die Anzahl der Leben in serielle (und human-readable) Form und extrahieren aus diesen seriellen Daten wieder alle Informationen für das Spiel
+ In zeichenFeld::updateObjects() werden die Objekte über einen QTimer durch das Spielfeld bewegt  
+ In zeichenFeld::HitRegistration() überprüft das Programm, ob die Objekte mit dem Avatar kollidieren
+ Durch die Funktion zeichenFeld::keyPressEvent(QKeyEvent *event) achtet das Programm auf den Druck der Pfeiltasten Links und Rechts, sodass der Avatar sich bewegen kann




