/**
 * Programmation C: Structures complexes
 * solution de l'exercice 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

enum msg_dir {
	request,
	response
};


struct msg_header {
	int id;
	enum msg_dir dir;
	int sz;
	int status;
};

struct request1 {int a; int b;};
struct request2 {float a; int b; int c;};
struct request3 {};
struct request4 {int a[10]; int b;};
struct request5 {long a; char b;};

struct response1 {int a; int b;};
struct response2 {};
struct response3 {int a; int b; int c; int d;};
struct response4 {int a;};
struct response5 {long a;};


struct messages_01 {
    struct msg_header header;
    union
    {
	struct request1	 req1;
	struct request2	 req2;
	struct request3	 req3;
	struct request4	 req4;
	struct request5	 req5;

	struct response1 res1;
	struct response2 res2;
	struct response3 res3;
	struct response4 res4;
	struct response5 res5;
    } msg;
};

struct messages_02 {
    struct msg_header header;
    union {
	struct request1	 req1;
	struct request2	 req2;
	struct request3	 req3;
	struct request4	 req4;
	struct request5	 req5;
    } request;

    union {
	struct response1 res1;
	struct response2 res2;
	struct response3 res3;
	struct response4 res4;
	struct response5 res5;
    } response;
};


struct messages_11 {
    struct msg_header header;
    struct request1   request;
    struct response1  response;
};

struct messages_12 {
    struct msg_header header;
    struct request2   request;
    struct response2  response;
};

struct messages_13 {
    struct msg_header header;
    struct request3   request;
    struct response3  response;
};

struct messages_14 {
    struct msg_header header;
    struct request4   request;
    struct response4  response;
};

struct messages_15 {
    struct msg_header header;
    struct request5   request;
    struct response5  response;
};


int main()
{
   struct messages_01 msg;
   struct request1 request1 = {.a=0, };

   msg.header.id = 1;
   msg.header.dir = request;
   msg.header.sz = sizeof(msg.header) + sizeof (msg.msg.req1);
   msg.header.status = 0;

   msg.msg.req1 = request1;

   return 0;
}
