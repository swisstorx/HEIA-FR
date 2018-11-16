// 1. Adressage normal

// ex1.

struct S {int a; int b; int c; int d;} s = {1,2,3,4};
//          0      4      8      12
int c = 0;

c = s.c;

	.data
s:	.long 1, 2, 3, 4
c:	.long 0

	.text
	ldr	r0, =s
	ldr	r1, =c
	ldr	r2, [r0, #8]
	str	r2, [r1, #0]




// ex.2

char s[4] = {1,2,3,4};
int c = 0;

int i=3;
c = s[i];

	.data
s:	.byte 1, 2, 3, 4
c:	.long 0

	.text
	ldr	r0, =s
	ldr	r1, =c
	ldr	r2, =i
	ldr	r2, [r2]

	ldrb	r3, [r0, r2]
	str	r3, [r1]



// ex.3

int s[4] = {1,2,3,4};
int c = 0;

int i=3;
c = s[i];

	.align 2
s:	.long 1, 2, 3, 4
c:	.long 0

	.text
	ldr	r0, =s
	ldr	r1, =c
	ldr	r2, =i
	ldr	r2, [r2]

	ldr	r3, [r0, r2, lsl #2]
	str	r3, [r1]



// 2. Adressage post-indexé

char src[] = "0123456789"
char dst[30];
char* s = &src[0];
char* d = &dst[0];

while (*d++ = *s++);

	.data
src:	.asciz "0123456789"
dst:	.space 30, 0

	.text
	ldr	r0, =src
	ldr	r1, =dst

1:	ldrb	r2, [r0], #1    --> r2 = memb[r0]; r0+=1
	strb	r2, [r1], #1	--> memb[r1] = r2; r1+=1
	cmp	r2, #0
	bne	1b




// 3. Adressage pre-indexé

char src[10+1] = "0123456789"
char dst[10+1];
char* s = &src[30];
char* d = &dst[30];

for(int i=30; i>0; i--) *--d = *--s;


	.data
src:	.asciz "0123456789"
dst:	.space 30, 0

	.text
	ldr	r0, =src+30
	ldr	r1, =dst+30
	mov	r2, #30

1:	ldrb	r2, [r0, #-1]!
	strb	r2, [r1, #-1]!
	subs r2, #1
	bne	1b

