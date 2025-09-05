# Github:
https://github.com/Endorum/SpaceInvaders

# Build:
<p>cmake -S . -B build -DCMAKE_POLICY_VERSION_MINIMUM=3.5
<p>cmake --build build

# Run:
./build/bin/SpaceInvaders

Das Spiel startet sofort, der Spieler befindet sich in der Mitte, unten.
Die Aliens starten oben und bewegen sich langsam hin und her und nach unten.
Jeder Alien hat pro Tick eine Chance von 1 zu 1000 einen Laser zu schießen, 
der den Spieler oder einen der Bunker treffen kann.

Der Spieler kann mit den Pfeiltasten gesteuert werden, (links und rechts)
Außerdem kann der Spieler schießen mit der Leertaste.
Der Laser kann auch die Bunker treffen und zuerstören, man soll also versuchen
zwischen den Lücken zu schießen.

Wenn einer der Aliens eine bestimmte Linie erreichen (kurz über den Bunkern) hat man verloren.
Wenn der Spieler keine Leben mehr hat, hat man auch verloren.
Wenn alle Aliens tod sind, gewinnt man die Runde, es wird 2 Sekunden gewartet, und das nächste 
Level beginnt, der einzige unterschied ist, dass die Aliens Level für Level immer 10% schneller werden.

Jeder Alien kill bringt 10 Punkte, so kann man später sehen wie gut man war.