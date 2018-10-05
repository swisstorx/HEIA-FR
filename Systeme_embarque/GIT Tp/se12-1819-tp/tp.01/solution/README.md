# Quelques améliorations possibles

Il est possible d'apporter quelques améliorations au programme

1.  La configuration des portes d'entrée/sortie peut être généralisée. Pour cela il faut étendre la structure `struct gpio_init` avec 2 champs supplémentaires, soit `enum am335x_gpio_modules module` et `bool state`. Le premier champ indique le numéro du module gpio sur lequel la porte d'entrée/sortie est connectée. Le deuxième champ spécifie la valeur initiale de la porte (à 1 ou à 0).

1. Il est possible de se passer de la méthode `turn_leds_on()` en appelant directement la méthode `am335x_gpio_change_states()`dans la méthode `switch_leds_on_off()`.

1. Il est possible de remplacer la 2e boucle `while` à l'intérieur de la méthode `main()` par une boucle `for` et en utilisant la macro `ARRAY_SIZE()`pour obtenir le nombre d'éléments contenu dans le message `msg`.
