#include "include/linux/rbtree_types.h"
struct cfs_rq {
	long min_runtime;
	struct rb_root rb_root;

	struct task_struct* curr;
};
struct rq {
	struct cfs_rq cfs;
};
void task_cpu(struct task_struct* task) {

}
//todo percpu
#define cfs_rq_of(cpu) 
