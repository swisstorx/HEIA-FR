/**
 * Programmation C: Structures complexes
 * solution de l'exercice 6
 */

#include <stdint.h>
#include <stdio.h>

/* define command bitfield */
#define CMD_RST (1<<0)
#define CMD_STP (1<<1)
#define CMD_GO  (1<<2)

/* define status bitfield */
#define STATUS_IRQ (1<<0)
#define STATUS_ERR (1<<1)
#define STATUS_OK  (1<<5)

#define NUMBER_OF_COUNTERS 2

struct hw_device
{
	uint8_t  cmd;
	uint8_t  status;
	uint8_t  io;
	uint8_t  unused;
	uint16_t counter[NUMBER_OF_COUNTERS];
};

void init_hw_device (struct hw_device* regs)
{
	regs->cmd = CMD_RST;
	regs->status = 0;
	regs->io = 0;
	for (int i=NUMBER_OF_COUNTERS-1; i >= 0; i--) regs->counter[i] = 0;
}

struct hw_device hw_reg1 = {0, 0x20, 0, 0, {0, 0}};

struct hw_device hw_reg2 = {
	.cmd=0, .status=0, .io=0,
	.counter = {0, 0},};


int main()
{
	return 0;
}
