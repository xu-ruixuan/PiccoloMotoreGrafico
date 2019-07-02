#ifndef SETTINGS
#define SETTINGS

#define RES_W 800
#define RES_H 600

#define SHOW_TEAPOT false
#define SHOW_SPHERE true
#define SHOW_PYRAMID false

//I gradi del campo di vista
#define CAMERA_FOV 60

//Disegna il wireframe degli oggetti
#define WIREFRAME true

//Back face culling: Cancella dalla pipeline i triangoli coperti
#define BACK_FACE_CULLING false

//proiezione prospettiva, se false allora usa la proiezione ortogonale
#define PERSPECTIVE true

//Corregge l'aspect ratio
#define AUTO_ASPECT_RATIO true

//Se l'aspect ratio non è automatico allora vengono definiti questi valori
#define ASPECT_RATIO 1
//Valori per la traslazione della finestra
#define X0 0
#define Y0 0


#endif
