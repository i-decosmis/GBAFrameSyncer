# Responsabilità ⚠️
Questa guida è fornita a scopo informativo e redatta con la massima cura possibile. Tuttavia, l'autore non si assume alcuna responsabilità per eventuali danni, guasti o malfunzionamenti derivanti dall'uso delle informazioni qui contenute. L'utente è invitato a procedere con cautela e a utilizzare il proprio giudizio e competenza. L'uso di questa guida è interamente a proprio rischio.

Seguire questa guida modifica in modo irreversibile la shell.

# Guida all'utilizzo del sistema 📝
## Caricare il codice 🔄
* Aprire Arduino IDE.
* Caricare il codice scelto tra le versioni disponibili su Arduino (approfondimenti piú in basso).


## Inizio 🚀
* Alimentare il sistema tramite la porta USB-C.
* Collegare il connettore del sistema a quello installato sul GBA.
* Accendere il sistema.

## Se si utilizza la versione con display LCD 🖥️
* Regolare la luminosità cliccando il pulsante.
* Dopo aver scelto la luminosità preferita, tenere premuto il pulsante per più di 2 secondi e poi rilasciarlo.
* Usare il potenziometro per impostare il timer. Il potenziometro può variare il tempo aggiungendo o sottraendo al timer una, dieci, cento o mille unità, a seconda della rotazione verso destra o sinistra.
* Dopo aver impostato il timer, cliccare il pulsante.
* Dopo 5 secondi il GBA si riavvierà automaticamente.
* Al termine del tempo impostato, Arduino premerà il tasto A sul GBA.
* Resetta il sistema accendendo e spegnendo Arduino.

## Se si utilizza la versione senza display LCD 👀
Questa versione richiede l'uso del PC.
* Aprire il codice `NoDisplayMaxOptimized.ino` con Arduino IDE.
* Alla riga 2, modificare il valore di `value` con il tempo desiderato per il timer.
* Collegare Arduino al GBA tramite il connettore.
* Collegare Arduino al PC.
* Accendere Arduino tramite il pulsante, se spento.
* Caricare il codice su Arduino.
* Dopo 5 secondi Arduino riavvierà automaticamente il GBA.
* Al termine del tempo impostato tramite `value`, Arduino premerà il tasto A.
* Resetta il sistema accendendo e spegnendo Arduino.

## Considerazioni sul codice
Il sistema deve essere riavviato ogni volta dopo il timer perché ho utilizzato la funzione `micros` che va in overflow dopo circa 70 minuti. Per evitare problemi, ho scelto questo approccio.

## Differenze tra le tre versioni di codice 🆚
Sono disponibili tre versioni del codice:
* `CompleteCode.ino`: Include tutte le funzionalità, ovvero il pannello LCD e l'aggiornamento in tempo reale della percentuale di avanzamento del timer.
* `OptimizedCode.ino`: Include il pannello LCD, ma è ottimizzato per ridurre gli sfasamenti del timer, poiché non calcola la percentuale di avanzamento e dedica tutte le risorse al controllo del timer.
* `NoDisplay.ino`: Esclude il display LCD, il potenziometro e il pulsante, richiedendo un PC per l'uso.

`OptimizedCode.ino` e `NoDisplay.ino` offrono le stesse prestazioni.
Ecco una versione rivista:
Nel file `CompleteCode.ino` le prestazioni sono comunque considerate, poiché l'aggiornamento della percentuale rimanente viene calcolato solo una volta ogni 5 secondi, e solo se mancano almeno 10 secondi al termine, permettendo di essere più precisi possibile.

# Dettagli 🔎
In questo documento NON verranno illustrate le tecniche di manipolazione RNG su GBA, ma verrà presentato un sistema per automatizzare il processo di manipolazione RNG su GBA. 
L'obiettivo è ottenere un sistema utilizzabile senza PC. Si consiglia di consultare il video di accompagnamento per ulteriori dettagli sui passaggi.

# Requisiti ✅
* Saldatore
* Colla a caldo
* Un GBA
* Stampante 3D
* [Arduino Nano](https://www.amazon.it/dp/B0CWH4P152)
* 4 [fotoaccoppiatori](https://www.amazon.it/dp/B07X46SYQT)
* [Resistori da 220, 1k, 10k ohm](https://www.amazon.it/dp/B0B8CQ9FYC)
* [Breadboard](https://www.amazon.it/dp/B078HV79XX)
* [Condensatore da 100 microF](https://amzn.eu/d/5ATUCtE)
* [Piccoli fili elettrici](https://amzn.eu/d/4wbI2sM)
* [Potenziometro](https://www.amazon.it/dp/B09LLVJ4WK)
* [Pulsanti](https://www.amazon.it/dp/B082DBBPGC)
* [Interruttori](https://www.amazon.it/dp/B0BTM3WQXN)
* [Connettori USB-C](https://www.amazon.it/dp/B0DFPV1V35)
* [Plug USB-C](https://www.amazon.it/dp/B0D5PVDJLX)
* [LCD 16x02](https://www.amazon.it/dp/B082166FCL)
* [Connettore a 5 pin](https://www.amazon.it/dp/B0C9C2NSYC)
* [Guaina termorestringente](https://amzn.eu/d/3FiaBTP)

# Guida 🧭
## Modifica del GBA 🛠️
In questo esempio, viene utilizzato un Game Boy Advance SP.

### Primo Passo 1️⃣
Saldare dei fili sottili sui pin evidenziati nell'immagine. (Video per dettagli)
<img src="../../Images/gbaSpMotherboard.png" alt="gbamother" width="500">

### Secondo Passo 2️⃣
Forare la shell.
È possibile utilizzare una shell già modificata, con un foro sul lato destro.
<img src="../../Images/shell.png" alt="shell" width="500">
L'obiettivo è far uscire i fili appena saldati dalla shell. È possibile scegliere il punto migliore in base alle proprie esigenze. (Video per dettagli)

### Terzo Passo 3️⃣
Riassemblare il GBA SP. (Video per dettagli)
<img src="../../Images/reassembleGba1.png" alt="reassemble1" width="500">
<img src="../../Images/reassembleGba2.png" alt="reassemble2" width="500">

## Creazione del circuito ⚡
Seguire lo schema elettrico per creare il circuito. (Video per dettagli)
<img src="../../Images/circuit.png" alt="circuit" width="500">
È consigliato l'uso di un'estensione USB-C con un pulsante per interrompere l'alimentazione, permettendo di alimentare e riprogrammare Arduino anche dopo l'assemblaggio. (Video per dettagli)
Molte batterie portatili smettono di caricare se il carico è troppo basso; per questo motivo è inserita una resistenza in parallelo ad Arduino, consentendo l’alimentazione anche da batterie portatili. Esistono soluzioni più efficienti, ma questa è risultata la più immediata e pratica. (Video per dettagli)

### Circuito senza display LCD, potenziometro e pulsante ⚡👀
Utilizzare il codice `NoDisplay.ino` con questo schema.
<img src="../../Images/smallCircuit.png" alt="circuit" width="500">

## Stampa e assemblaggio della scocca 📐
Questa è stata la mia prima esperienza nella progettazione e stampa di una scocca per un circuito, e c'è sicuramente margine per una maggiore compattezza e ottimizzazione.
[Questa scocca](../../3dFiles/) è progettata per la versione completa del circuito.
Stampare il file 3D, scegliere i punti in cui praticare i fori per il pulsante, la presa USB-C di ingresso e il connettore per il GBA.
Assemblare il circuito nella scocca. (Video per dettagli)
<img src="../../Images/finalCircuit.png" alt="circuit" width="500">
Sotto il coperchio è presente una sezione in cui è possibile inserire una batteria portatile. Questa scelta consente di utilizzare il sistema senza PC o presa elettrica.
<img src="../../Images/batterySlide.gif" alt="circuit" width="500">

## Test del sistema 🔬
È disponibile un test del sistema qui.

## Valutazione dell'errore fisico 📊
Dopo diversi test, il numero massimo di tentativi per calcolare l'errore fisico nel delay è risultato essere 4. Nella maggior parte dei casi non è stato necessario più di 3 tentativi.
Questo errore deriva dal metodo con cui Arduino misura il tempo: il suo chip in ceramica è sensibile alle variazioni di temperatura, causando lievi oscillazioni di precisione.
Una possibile soluzione potrebbe essere l'uso di moduli dedicati al timer, meno influenzati dalla temperatura.
Occorre inoltre considerare l'eventuale delay dei fotoaccoppiatori e dei collegamenti.

# Problemi 🆘
Nessun problema riscontrato finora.

# Licenza 🛂
Questo progetto è concesso sotto licenza **GNU General Public License v3.0**. Sei libero di usare, modificare e distribuire questo codice alle seguenti condizioni:

1. **Attribuzione**: Se usi questo codice come base per il tuo progetto o crei opere derivate, ti preghiamo di dare credito includendo il mio nome (Ivan De Cosmis) nella documentazione del progetto, README o altri materiali pertinenti.

2. **Condivisione allo stesso modo**: Qualsiasi lavoro derivato basato su questo progetto deve essere concesso in licenza sotto GPLv3, per garantire che gli utenti futuri possano beneficiare delle tue modifiche.

3. **Uso commerciale**: Se intendi usare questo progetto o derivati per scopi commerciali, contattami per discutere la corretta attribuzione e eventuali accordi.

Per maggiori dettagli, consulta il testo completo della **GNU General Public License v3.0** [qui](https://www.gnu.org/licenses/gpl-3.0.html).