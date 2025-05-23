## Progetto SuperSerra64
Componenti:
- Creazzo Nicola
- Hu Caterina
- Lagnarini Iris

Questo progetto, sviluppato in C++, simula una serra intelligente capace di gestire automaticamente l’irrigazione di diverse piante, ognuna con esigenze diverse. Il sistema permette di accendere e spegnere gli impianti in modo manuale o automatico, seguendo orari o condizioni ambientali.

Ogni impianto è legato a un tipo di pianta (tropicale, desertica, mediterranea, ecc.) e funziona secondo regole diverse: alcuni si accendono da soli dopo un certo tempo, altri vanno gestiti a mano, e altri ancora si attivano in base alla temperatura.

Tutti gli impianti derivano da una classe base comune, e vengono gestiti da una classe chiamata **Serra**, che tiene traccia di tutti gli impianti presenti. L’utente può interagire con il sistema tramite comandi scritti da terminale: ad esempio può accendere un impianto, impostare l’orario, o vedere lo stato della serra.

Il progetto include anche una simulazione dell’orario, gestita dalla classe **Orario**, che permette di far avanzare il tempo e attivare gli impianti in automatico, come se passassero davvero le ore.

Suddivisione del lavoro:

- Nicola Creazzo si è occupato della gestione del tempo e delle logiche di irrigazione automatica, manuale e con sensore di temperatura. Ha anche modificato l’interfaccia utente.
- Caterina Hu ha sviluppato la classe Serra, che gestisce tutti gli impianti nella serra e ha fatto il main.
- Iris Lagnarini ha creato la classe base Impianto da cui derivano tutti i tipi di impianti, e ha scritto il README.

Il progetto è diviso in file, ben commentato e compilabile tramite CMake. Usa solo librerie standard del C++. Non ci sono eseguibili inclusi: il codice viene compilato al momento della correzione.
