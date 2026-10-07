#pragma once

#include<stddef.h>
void* my_malloc(size_t size);
void* my_calloc(size_t num, size_t size);
void my_free(void* ptr);
