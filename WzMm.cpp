#include <iostream>
#include <fcntl.h>
struct vm_area_struct {
	unsigned long vm_start;
	unsigned long vm_end;

	vm_area_struct* prev;
	vm_area_struct* next;
};
struct rb_node
{
	vm_area_struct* vm_area;
	rb_node* left;
	rb_node* right;
};
struct rb_root {
	rb_node* rb_node;
};
struct mm_struct {
	vm_area_struct* mmap;
	vm_area_struct* mmap_cache;
	rb_root* mm_rb;
};
void __vma_link_list() {

}
//todo rb_link
int find_vma_links(mm_struct* mm, unsigned long start, unsigned long end, vm_area_struct** prev, rb_node** parent, vm_area_struct*** rb_link) {

	rb_node* __rb_link, * __parent, * __prev;

	__parent = __prev = NULL;//

	__rb_link = mm->mm_rb->rb_node;

	while (__rb_link) {
		__parent = __rb_link;
		if (__rb_link->vm_area->vm_end > start) {
			if (__rb_link->vm_area->vm_start < end)
				return -1;
			__rb_link = __parent->left;
		}
		else {
			__prev = __parent;
			__rb_link = __parent->right;
		}
	}

	*parent = __parent;
	if (__prev)
		*prev = __prev->vm_area;
	return 0;
}

vm_area_struct* find_vma(mm_struct* mm, unsigned long addr) {
	vm_area_struct* vma = NULL;
	rb_node* node = mm->mm_rb->rb_node;

	while (node) {
		if (node->vm_area->vm_end > addr) {
			vma = node->vm_area;
			if (node->vm_area->vm_start <= addr)
				break;
			node = node->right;
		}
		else {
			node = node->right;
		}
	}
	return vma;
}
struct list_head {
	struct list_head* prev;
	struct list_head* next;
};
struct wait_queue_entry
{
	unsigned int flags;
	struct list_head entry;
};
//#define offsetof(type,member)  (size_t)&(((type*)0)->member)

#define list_entry(ptr, type, member) (type *)((void*)(ptr) - offsetof(type,member))
#define list_entry_is_head(pos, head, member) (&pos->member == head)


