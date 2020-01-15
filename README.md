# Greedykub-Rummi
A Rummikub game with computer opponents based on a greedy algorithm written in C++



## Rummikub Spielanleitung

Vor der ersten Spielrunde: 
+	Auswahl Anzahl PC Gegner / menschliche Gegner (an einem PC)
+	Eingabe der Namen der Spieler

Spielstart:
+	Jedem Spieler werden zufällig 14 Spielsteine zugewiesen
+	Spieler, der das Spiel startet, wird zufällig ausgewählt

Spielverlauf:
+	Anzeigen des Befehlssatzes möglich
+	Kombinations-Regel - Auf dem Spielfeld dürfen zu jeder Zeit nur folgende Kombinationen liegen:
+	Gruppe: 3-4 Spielsteine: selbe Zahl, verschiedene Farben
+	Reihe: 3-13 Spielsteine: aufeinanderfolgende Zahlen, gleiche Farbe
Der Joker kann dabei den Wert eines beliebigen Spielsteins annehmen

Spielzug: 
+	Ablegen unter Einhaltung der Kombinations-Regel (kein Limit bzgl. Anzahl der max. ablegbaren Karten):
+	Bilden einer eigenen Gruppe/Reihe
+	Anlegen an einer auf dem Spielfeld befindlichen Gruppe/Reihe
+	Umstrukturierung der Karten auf dem Spielfeld (Aufnehmen bereits abgelegter Karten ist nicht gestattet (in den letzten Runden))
+	Einschränkung – Erstes Auslegen: Spielsteinwert mind. 30 Punkte, Joker wird dabei nicht berücksichtigt
Oder:
+	Spielstein von Vorratsstapel ziehen

Spielende + Auswertung:
+	Ein Spieler hat alle Karten abgelegt
	Für jeden Verlierer werden die Werte seiner Spielsteine addiert und als Minuspunkte notiert (Joker = 30 Minuspunkte)
	Der Gewinner erhält die Minuspunkte aller Verlierer als Pluspunkte
+	Keine Spielsteine mehr auf Vorratsstapel
+	Der Spieler mit dem höchsten Punktewert hat das gesamte Spiel gewonnen
+	Ausgabe Rangliste mit Punkten
