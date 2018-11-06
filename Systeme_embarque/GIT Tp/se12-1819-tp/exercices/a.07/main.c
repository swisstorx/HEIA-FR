/**
 * Copyright 2018 University of Applied Sciences Western Switzerland / Fribourg
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
 * Project:		HEIA-FR / Embedded Systems TODO Laboratory
 *
 * Abstract:	TODO
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		Oct 28, 2018
 */

#include <stdio.h>

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

struct element {
	int key;
	int value;
	struct element* next;
};

struct list {
	struct element first;
};

void t_add(struct list* l, struct element node) {


	l->first = node;



}

void t_show(struct list* l) {



	while(l->next != NULL){

		printf("key: %d / value: %d\n", l->key, l->value);

	}

}

void t_delete(struct element circ[], int key, int len) {
	for (int i = 0; i < len; ++i) {
		if (circ[i].value == key)
			circ[i].value = 0;

	}
}

int t_find(struct element circ[], int key, int len) {

	return circ[key].value;
}
int main() {

	struct element node = {1,3,NULL};
	struct list l;


	t_add(&l,node);

	return 0;
}
