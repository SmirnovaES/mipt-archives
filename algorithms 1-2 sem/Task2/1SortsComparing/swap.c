#include <stdio.h>
#include <stdlib.h>

void swap(void* a, void* b, size_t element_size) {
	void* t = malloc(element_size);
	memcpy(t, a, element_size);
	memcpy(a, b, element_size);
	memcpy(b, t, element_size);
	free(t);
}
