#include<unistd.h>
#include<stdio.h>

typedef struct block{
	size_t size;
	int free;
	struct block* next;
}block_t;
#define BLOCK_SIZE sizeof(block_t)

block_t *head = NULL;

void *my_malloc(size_t size){
	block_t *curr = head;

	while(curr){
		if(curr->free && curr->size>=size){
			if(curr->size>=size + BLOCK_SIZE + 8){
				block_t *split = (block_t*)((char*)(curr+1)+size);
				
				split->size = curr->size -size - BLOCK_SIZE;
				split->free = 1;
				split->next = curr->next;

				curr->size = size;
				curr->next = split;
			}
			curr->free = 0;
			return (void*)(curr +1);
		}
		curr = curr->next;
	}

	block_t *new_block = sbrk(sizeof(block_t)+ size);
	if(new_block==(void*)-1)
		return NULL;
	new_block->size = size;
	new_block->free = 0;
	new_block->next = NULL;

	if(!head){
		head = NULL;
	}else{
		curr = head;
		while(curr->next)
			curr = curr->next;
		curr->next = new_block;
	}
	return (void*)(new_block+1);
}
void my_free(void *ptr){
	if(!ptr) return;

	block_t *block = (block_t*)ptr-1;
	block->free = 1;

	block_t *curr = head;

	while(curr && curr->next){
		if(curr->free && curr->next->free){
			curr->size += sizeof(block_t) + curr->next->size;
			curr->next = curr->next->next;
		}else{
			curr = curr->next;
		}
	}
}
int main()
{
	int *a = my_malloc(100);
	int *b = my_malloc(100);
	printf("a = %p\n",a);
	printf("b= %p\n",b);
	my_free(a);
	my_free(b);
	
	int *c = my_malloc(150);
	printf("c=%p\n",c);
	return 0;
}
