# PiccoloMotoreGrafico
Piccolo motore grafico per la tesi 2019/2020 sulla geometria proiettiva.

## Dipendenze

Per compilare il progetto è necessario avere le librerie:

1. Eigen3: libreria per l'algebra lineare.
2. SFML: libreria per il rendering 2D.

## Settaggi
I settaggi sono nel file Settings.h, modificando le macro all'interno è possibile cambiare il comportamento del software.
Ogni volta che si cambiano i settaggi è necessario ricompilare tutto il progetto tramite il makefile: nella cartella "src" scrivere su linea di comando "make".

## Input

Freccia su : sposta un oggetto in alto  
Freccia giu : sposta un oggetto in basso  
Freccia sinistra : sposta un oggetto a sinistra  
Freccia destra : sposta un oggetto a destra  
8 : sposta un oggetto in profondità  
2 : avvicina l'oggetto  

I : sposta la telecamera in avanti  
K : sposta la telecamera indietro  
J : sposta la telecamera a sinistra  
L : sposta la telecamera a destra  

W : zoom in  
S : zoom out  

Q : ruota un oggetto in senso anti orario per l'asse y  
 
R : Ingrandisci l'oggetto  
F : Rimpocciolisci l'oggetto  

D : allarga l'oggetto  

