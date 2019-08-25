/* void kernel_transfer(...);
 * r0 = context address of the former task
 * r1 = context address of the new task
 */
kernel_transfer:
	// Store all registers to the context at r0
	// Store the CPSR to the context at r0
	// Load the CPSR from the context at r1
	// Load all registers from the context at r1

kernel_interrupt_enable:
	// Set the I and the F bits to 0 according the the
	// parameter passed in r0

kernel_interrupt_disable:
	// Disable the interrupts and returns the previous state of
	// the I and F flags
