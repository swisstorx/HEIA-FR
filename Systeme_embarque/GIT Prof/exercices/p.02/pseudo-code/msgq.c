struct msgq {
	struct msgq* chain;
	
	semaid_t mutex;
	semaid_t items;
	semaid_t spaces;

	unsigned size;
	unsigned nb;
	unsigned in;
	unsigned out;
	void* msg[];
};

static struct msgq* msgq_list=0;

msgqid_t msgq_create(unsigned size) {
	// Allocate memory for the whole queue (for size messages)
	// Set the size attribute
	// Create "mutex" as a new semaphore with initial value of 1
	// Create "items" as a new semaphore with initial value of 0
	// Create "spaces" as a new semaphore with initial value of size
	// Add message queue to the "msgq_list" list
	// Return the created message queue
}

int msgq_destroy(msgqid_t msgq_id) {
	// Destroy all semaphores (returns error code on failure)
	// Remove the message queue from the "msgq_list" list
	// Free memory
	// return 0
}

int msgq_post (msgqid_t msgq_id, void* msg) {
	// Wait for the "spaces" semaphore (prevent overflow)
	// Wait for the "mutex" (critical region)
	// Add msg to the list (at "in")
	// Signal the "mutex" (end of critical region)
	// Signal "items"
}

void* msgq_fetch(msgqid_t msgq_id) {
	// Wait for the "items" semaphore (prevent underflow)
	// Wait for the "mutex" (critical region)
	// Get msg from the list (at "out")
	// Signal the "mutex" (end of critical region)
	// Signal "spaces"
}

void msgq_init() {
	// Nothing to do
}