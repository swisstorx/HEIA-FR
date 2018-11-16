//MAIN.C

/**
 * Copyright 2017 University of Applied Sciences Western Switzerland / Fribourg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Project:	HEIA-FR / Embedded Systems 1 Laboratory
 *
 * Abstract:Digital visual metronome
 *
 * Purpose:	This is a metronome program for the Beaglebone board equipped qith the extenstion board ML130
 *
 * Author: 	Valentin Pharisa
 * Date: 	04.12.2017
 */

#include <stdio.h>
#include <stdbool.h>

#include "dmtimer1.h"
#include "seg7.h"				// Permet d'utiliser facilement l'afficheur 7-segments
#include "wheel.h"				// Permet d'accéder aux fonctions de l'encodeur
#include "leds.h"				// Permet d'accéder aux fonctions des leds
#include "button.h"				// Permet d'accéder à l'état du bouton S1 du circuit d'extension

// public method implementation -----------------------------------------------

int main(){

	// initialization des différents composants
	seg7_init();
	wheel_init();
	button_init();
	dmtimer1_init();
	led_init();

	int tempo = 60;				// Valeur du tempo par défaut
	int ledUse = 1;				// Led s1 par defaut
	bool released = true;		// Bouton s5 est relâché par défaut
	int beat = 1;				// nbre de battement
	bool on = true;				// Allume = true , éteint = false
	bool mode = false;			// Mode ( false = tempo , true = nbre de leds)
	seg7_display_value(tempo);	// Affiche la valeur par défaut du tempo sur seg7

	uint32_t period = 60 * dmtimer1_get_frequency() / tempo; // toutes les secondes (tempo = 60 par defaut)
	uint32_t st = dmtimer1_get_counter();
	uint64_t total = 0;

	// main loop
	while(true) {
		seg7_refresh_display();
		if (wheel_button_is_pressed()){
			if(released){
				released = false; 					// met à jour release (s5 est pressé)
				if(button_s1_is_pressed()){
					if(mode){
						ledUse = 1;					// par defaut led s1
						seg7_display_value(ledUse);
					}
					else{
						tempo = 60;					// par defaut le tempos (s5 est relaché)
						seg7_display_value(tempo);
					}
				}
				else{
					if (mode) {
						mode = false;				// mode tempo
						seg7_display_value(tempo);
					}
					else {
						mode = true;				// mode nbre leds
						seg7_display_value(ledUse);
					}
				}
			}
		}
		else{
			released = true;
		}

		switch (wheel_get_direction()) {		// direction de la roulette
			case WHEEL_RIGHT:
				if (mode) { 					// configure nbre leds
					if(ledUse < 3) {
						ledUse++;
					}
				}
				else {
					if(tempo < 199){
						tempo++;
					}
				}
				if (mode) {						//affiche les valeurs selon le mode
					seg7_display_value(ledUse);
				}
				else {
					seg7_display_value(tempo);
				}
				break;

			case WHEEL_LEFT:
				if (mode) {						// mode nbre leds
					if(ledUse > 1) {			// (On ne peut pas avoir moins d'une led)
						ledUse--;
					}
				}
				else {
					if(tempo > 0){				// mode tempo
						tempo--;
					}
				}

				if (mode) {						//affiche les valeurs selon le mode
					seg7_display_value(ledUse);
				}
				else {
					seg7_display_value(tempo);
				}
				break;

			case WHEEL_STILL:
				if(button_s1_is_pressed()){
					if(mode){					// affichage du nombre de led selon s1
						if(ledUse < 3){
							ledUse++;
							break;
						}
						else{
							ledUse=1;
							break;
						}
					}
					if(!mode){					// affichage du tempo selon s1
						if(tempo < 189){
							tempo+=10;
							break;
						}
						else{
							tempo=1;
							break;
						}
					}
				break;

			default:
				break;
		}


		/*
		 * Implémentation de l'horloge
		 */

		uint32_t sp = dmtimer1_get_counter();
		uint32_t delta = sp-st;
		st = sp;
		total += delta;
		if (total >= period) {
			if(on) beat += 1;
			if (beat > ledUse) beat =1;
			total -= period;
			on = !on;
			led_set_state(on ? (1<<(beat-1)) : 0);
		}
	}
}
