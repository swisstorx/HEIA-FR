/*
 * serpent.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 */

#include <stdio.h>
#include "serpent.h"
#include "seg7.h"

#define CHA 		1
#define GPIO2 		AM335X_GPIO2
#define CHB 		29
#define GPIO1 		AM335X_GPIO1

static int former_state = 0;



/*
ça je dois le faire dans le main? récupérer mon serpent states pour afficher
les différents steps?
*/

enum serpent_states {
	//L = left d=Digit X=position
	Ld_G, Ld_B,Ld_A,Ld_F,Ld_E,Ld_D,Ld_C,Rd_G,Rd_B,Rd_A,Rd_F,Rd_E,Rd_D,Rd_C;
};
/*
une meilleure idée pour faire ça? je sais pas comment affecter
un elt de mon enum pour allumer tel ou tel digit
*/

static inline int get_Serpent_state() {
	int state = 0;
/*
parcours du Enum, si on tourne a droite, on fait +1 dans l'Enum
parcours du Enum, si on tourne a gauche, on fait -1 dans l'Enum

*/
	if (am335x_gpio_get_state(GPIO2, CHA))
		state += 1;
	if (am335x_gpio_get_state(GPIO1, CHB))
		state += -1;

	return state;
}
enum wheel_direction get_Snake() {
	int state = get_encoder_state();

	printf("encode %d", get_encoder_state());
	//controle si la direction à changé depuis le dernier contrôle
	enum wheel_direction direction = transitions[former_state][state];

	former_state = state;

	return direction;
}