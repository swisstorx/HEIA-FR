/* Interfacing C with assembleur
 * Exercice 2 : solution
 */

struct S1 { long a; };
struct S2 {int a; int b[100];};

struct S1 s1 = {1};
struct S2 s2 = {2, {10, 11}};

extern struct S1 f1();
extern struct S2 f2();
extern long long f8();

extern void f3 (int a, int b, int c, int d, struct S2 s);
extern void f4 (int a, int b, int c, int d, const struct S2* s);
extern void f5 (struct S2 s, int a, int b, int c, int d);
extern void f6 (const struct S2* s, int a, int b, int c, int d);
extern void f7 (struct S1 s);

int main ()
{
    struct S1 r1 = f1();
    struct S2 r2 = f2();
    f3 (1,2,3,4,s2);
    f4 (1,2,3,4,&s2);
    f5 (s2,1,2,3,4);
    f6 (&s2,1,2,3,4);
    f7 (s1);
    long long r3 = f8();
    return 0;
}

