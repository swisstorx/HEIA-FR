/*
 * shell.h
 *
 *  Created on: Nov 6, 2018
 *      Author: lmi
 */
#pragma once
#ifndef _SHELL_H
#define _SHELL_H

/*
 * on initialise le shell avant de laisser l'utilisateur commencer
 * à taper ses commandes
 */
extern void shell_init();
/*
 * l'utilisateur va taper sa commande (on parse sa commande)
 */
extern void shell_prompt();

/*
 * validation de la commande tapée dans le shell prompt et vérification
 * de la commande à interpréter
 */
extern void shell_probe();


#endif
