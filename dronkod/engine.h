#ifndef ENGINE_H
#define ENGINE_H

#include <Arduino.h>

void konfigurujSilniki(); 

void jedzDoPrzodu();
void stopPrzod();
void jedzDoTylu();
void stopTyl();
void skrecWLewo();
void stopLewo();
void skrecWPrawo();
void stopPrawo();
void stopWszystko(); 

#endif //ENGINE_H