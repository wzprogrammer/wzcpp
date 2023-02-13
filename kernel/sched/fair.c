/*
1 cfs_rq->avg->load_sum有什么用 为什么和se->avg->load_sum计算方式不同
 


*/

#include "sched.h"
#include <cstddef>

#define cpu_rq(cpu) (&rq)
#define task_cpu(p) 0

#define min(a,b) 0
typedef unsigned long long u64;
struct rq rq;

unsigned long cpu_util_next(int cpu, struct task_struct* p, int dst_cpu) {

	struct cfs_rq* cfs_rq = &cpu_rq(cpu)->cfs_rq;
	unsigned long util = cfs_rq->avg.util_avg;

	if (task_cpu(p) == cpu && dst_cpu != cpu)
		util -= p->se.avg.util_avg;
	else if (task_cpu(p) != cpu && dst_cpu == cpu)
		util += p->se.avg.util_avg;

	return min(util, cpu_rq(cpu)->cpu_capacity_orig);
}

void update_curr(struct cfs_rq* cfs_rq) {
	struct sched_entity* curr = cfs_rq->curr;
	if (!curr)
		return;
	u64 now = 0;
	curr->sum_exec_time = now - curr->start_exec_time;
	curr->start_exec_time = now;
	//curr->vruntime=calc_delta_fair();
}

void put_prev_entity(struct cfs_rq* cfs_rq,struct task_struct* prev) {
	
	update_curr(cfs_rq);
	struct cfs_rq* cfs_rq = prev->cfs_rq;
	//enqueue(cfs_rq, prev);
	cfs_rq->curr = NULL;
}
