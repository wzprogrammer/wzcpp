#include <cstddef>

#define MAX_ORDER 11

#define ALLOC_HARDER 0x10
#define ALLOC_HIGH 0x20
#define ALLOC_OOM 0x08
#define ALLOC_WMARK_MIN WMARK_MIN
#define ALLOC_WMARK_LOW WMARK_LOW
#define ALLOC_WMARK_HIGH WMARK_HIGH
#define ALLOC_NO_WATERMARKS 0x04
#define ALLOC_WMARK_MASK (ALLOC_NO_WATERMARKS-1)


struct list_head {
	struct list_head* prev;
	struct list_head* next;
};
struct free_area {	
	struct list_head free_list[MIGRATE_TYPES];
	unsigned long nr_free;
};
struct page {
	struct list_head lru;
};

struct zone {
	struct free_area free_area[MAX_ORDER];
	long vm_stat[NR_VM_ZONE_STAT_ITEMS];
	unsigned long wmark[NR_WMARK];
	unsigned long nr_reserved_highatomic;
	unsigned long lowmem_reserved[MAX_NR_ZONES];
};

enum zone_stat_item {
	NR_FREE_PAGES,
	NR_VM_ZONE_STAT_ITEMS
};

enum zone_type {
	DMA,
	NORMAL,
	HIGHMEM,
	MAX_NR_ZONES
};

enum zone_watermarks {
	WMARK_MIN,
	WMARK_LOW,
	WMARK_HIGH,
	NR_WMARK
};

enum migratetype {
	MIGRATE_UNMOVABLE,
	MIGRATE_MOVABLE,
	MIGRATE_RECLAIMABLE,
	MIGRATE_PCPTYPES,	/* the number of types on the pcp lists */
	MIGRATE_HIGHATOMIC = MIGRATE_PCPTYPES,
	MIGRATE_TYPES
};

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



#define offsetof(type,member)  (size_t)&(((type*)0)->member)

struct page* __rm_queue(struct zone* zone, unsigned int order) {
	free_area* area;
	list_head* lh;
	page* page = NULL;
	unsigned int i;
	for (i = order; i < MAX_ORDER; i++)
	{
		area = &zone->free_area[i];
		//todo
		lh = &area->free_list[0];
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


bool zone_watermark_ok(struct zone * zone,unsigned int order, unsigned int alloc_flags,unsigned int highest_zoneidx) {

	unsigned long mark = zone->wmark[alloc_flags & ALLOC_WMARK_MASK];
	unsigned long free_pages = zone->vm_stat[NR_FREE_PAGES];
	int o;

	free_pages -= 1 << order;
	if (!alloc_flags & (ALLOC_HARDER | ALLOC_OOM))
		free_pages -= zone->nr_reserved_highatomic;
	free_pages -= zone->lowmem_reserved[highest_zoneidx];

	if (alloc_flags & ALLOC_HIGH)
		mark -= mark / 2;
	if(alloc_flags & ALLOC_OOM)
		mark -= mark / 2;
	else if(alloc_flags & ALLOC_HARDER)
		mark -= mark / 4;

	if (free_pages < mark)
		return false;

	for (o = order; o < MAX_ORDER; o++) {
		free_area free_area = zone->free_area[o];

		int mt;
		for ( mt = 0; mt < MIGRATE_PCPTYPES; mt++)
		{
			if (free_area.free_list[mt].next != &free_area.free_list[mt])
				return true;
		}
	}

	//todo alloc_harder & MIGRATE_HIGHATOMIC

	return false;
}
