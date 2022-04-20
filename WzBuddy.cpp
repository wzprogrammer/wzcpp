#include <cstddef>
struct list_head {
	struct list_head* prev;
	struct list_head* next;
};
struct free_area {
	struct list_head free_list;
	unsigned long nr_free;
};
struct page {
	struct list_head lru;
};

#define MAX_ORDER 11
struct zone {
	struct free_area free_area[MAX_ORDER];
};

enum zone_type {
	DMA,
	NORMAL,
	HIRHMEM,
	MAX_NR_ZONES
};


//2022-4-20
struct pglist_data
{
	struct zone zones[MAX_NR_ZONES];
};

struct pglist_data contig_page_data;

pglist_data* first_online_pgdat() {
	return &contig_page_data;
}

pglist_data* next_online_pgdat(struct pglist_data* pgdat) {
	//todo
	return &contig_page_data;
}

pglist_data* NODE_DATA(int nid) {

}

#define for_each_online_pgdat(pgdat) \
	for(pgdat = first_online_pgdat(); \
		pgdat; \
		pgdat = next_online_pgdat(pgdat))
//end 2022-4-20


#define offsetof(type,member)  (size_t)&(((type*)0)->member)

struct page* __rm_queue(struct zone* zone, unsigned int order) {
	free_area* area;
	list_head* lh;
	page* page = NULL;
	unsigned int i;
	for (i = order; i < MAX_ORDER; i++)
	{
		area = &zone->free_area[i];
		lh = &area->free_list;
		if (!lh->next || lh->next == lh)
			continue;
		page = (struct page*)(lh->next - offsetof(struct page, lru));
		break;
	}
	if (page) {
		list_head* prev = page->lru.prev;
		list_head* next = page->lru.next;

		prev->next = next;
		next->prev = prev;
		page->lru.prev = page->lru.next = nullptr;

	}
	return NULL;
}
