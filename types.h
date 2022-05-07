#pragma once

struct list_head {
	struct list_head* prev;
	struct list_head* next;
};

enum gfp_type
{
	
};

#define gfp_type gfp_t
#define freelist_idx_t short
struct slab {
	struct list_head slab_list;
	void* s_mem;
	void* free_list;

	unsigned int active;
};
