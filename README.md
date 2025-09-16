## Contenuto del folder "trial_generator" (file .py):

"trial_generator": contiene i codici per la creazione dell'inyero set di combianzioni comoplete di stimoli A, V, AV all'interno del range di ISI che viene impostato (p.e. le 7000 combinazioni con ISI fra 1000 e 1500 ms). Le immagini vengono pescate dal folder "visual cues led matrices", in cui si possono appunto cambiare se c'è necessità di altri colori, forme o dimensioni ma va rigenerato anche il set completo di 7000 trial. Il codice in output salva direttamente tutte le combianzioni divivse per A, V, Av e tutte quante mixate assieme in 3 cartelle all'interno del path che si trova nelle ultime righe di codice (DA MODIFICARE SUL TUO PC).

"estrai_random_subset": se eseguito preleva un subsed di X trial fra quelli gnerati col codice prima di diverso tipo (A, V e AV) e salva quersto subset in un folder dedicato (MODIFICARE IL PATH NEL CODICE) da cui poi, dall'interfacia dell'esperimento si possono iportare e caricare com e treno di trial gia pronto all'esecuzione

## PROBLEMATICHE AUDIO
### Rumore in sottofondo
con il sistema di gestione dei segnali audio PWM direttamente dalle porte GPIO del master, gli amplificatori raccolgono e amplificano un sacco di rumori indesiderati e costanti che infastidicono l'esecuzione e non permettono di avere un silenio puro durante tutto il test (si sente un rumore di fondo, suoni ad alta frequenza ripetitivi, picchi ecc)
### (RISOLTO) Problema interruzione anticipata primo trial del treno
modificato codice experiment.cpp nella gestione cronometro temporale sulla durata del trial e quindi sulla condizione di terminazione trial e passaggio da T_WAIT_FOR_END a T_END: ora il codice mentre il trial è in esecuzione verifica con due condizioni separate SE la durata del trial è stata raggiunta, poi SE un qualche evento da tastiera è stato registrato. Prima di questo: verficava l'OR fra queste due condizioni, quindi durante il primo trial, se durante lo stimolo venva premuto un tasto, l'esecuzione bypassava l'ISI e pasasava direttamente al secondo trial (quindi primo e secondo stimolo risultavano uno di seguito all'altro e attaccati temporalmente) RISOLTO!!
