#include "include/linux/sched.h"
#include "kernel/sched/sched.h"
#include <stdio.h>

//temp
static struct task_struct* current;
#define u64 long
#define u32 long
#define NICE_0_WEIGHT 1024
u64 min(u64 u1, u64 u2) {
	return -1;
}
u64 max(u64 u1, u64 u2) {
	return -1;
}

#define WMUTI_SHIFT 32

int fls(int num) {
	int result = 32;

	if (num == 0)
		return 0;

	if (num & 0xffff0000) {
		num <<= 16;
		result -= 16;
	}
	if (num & 0xff000000) {
		num <<= 8;
		result -= 8;
	}
	if (num & 0xf0000000) {
		num <<= 4;
		result -= 4;
	}
	if (num & 0xc0000000) {
		num <<= 2;
		result -= 2;
	}
	if (num & 0x80000000) {
		num <<= 1;
		result -= 1;
	}
	return result;
}

u64 cal_delta(u32 delta, int weight, int weight2) {
	//no how to translate divide to multi
	int shift = WMUTI_SHIFT;
	u64 result = delta * weight;
	//abandon

}

void update_min_runtime() {
	struct cfs_rq* cfs;//todo percpu

	u64 min_runtime = cfs->min_runtime;

	if (current) {
		min_runtime = min(current->se.vruntime, min_runtime);
	}
	//struct task_struct *leftmost
	//if(leftmost) min_runtime = min(leftmost->se.vruntime, min_runtime);

	cfs->min_runtime = max(min_runtime, cfs->min_runtime);
}

void update_cur() {
	long now;
	long delta = now - current->se.start_exec_time;
	current->se.start_exec_time += delta;
	current->se.vruntime += cal_delta(delta, NICE_0_WEIGHT, current->se.weight);

	update_min_runtime();
}



void task_fork_fair(struct task_struct* task) {
	//1 update task->se->vruntime

	//1
	struct cfs_rq* cfs;
	task->se.vruntime = 0;//error 
	//? cfs_rq->curr & current
	//? se->on_rq
	//? how to update cfs_rq->min_runtime
}

struct task_struct* pick_next_task_fair(struct rq* rq, struct task_struct* prev) {
	//1 update date structure
	//2 update statis

	//1
	struct sched_entity* se = &prev->se;
	struct cfs_rq* cfs;
	if (prev) {
		put_prev_entity(cfs, se);
	}
	struct task_struct* leftmost;
	if (leftmost) {
		//dequeue
		cfs->curr = leftmost;
		return leftmost;
	}
	return NULL;
}

static void put_prev_entity(struct cfs_rq* cfs_rq, struct sched_entity* se) {
	//?
	if (se->on_rq)
		update_cur();
	if (se->on_rq) {
		//__enqueue_task();
	}
	cfs_rq->curr = NULL;
}
int main() {

}


/*
1 src dsc imbalance数量
2 migrate tasks
添加的优化点
    can_migrate
      cache
    need_break
    LBF_DST_PINNED
    	
    






*/


load_balance


find_busiest_group
	//是否load_balance的比较算法
	update_sd_lb_stats
		更新sd下面所有sg的stats，选出busiest
		更新自己的cpu_capacity
		//busiest的比较算法
		if (local_group)
			update_group_capacity(env->sd, env->dst_cpu);
		for_each_group
			update_sg_lb_stats
				for_cpu_span
					sgs+=load
					sgs+=runable
					sgs+=util

					sgs+=nr_running
					sgs+=h_nr_running

					SG_OVERLOAD
					SG_OVERUTILIZED
				sgs->group_type = group_classify
					group_overloaded
					group_imbalanced
					group_fully_busy
					group_has_spare
			update_sd_pick_busiest
		
		update rd->overload
		update rd->overutilized

find_busiest_queue
	//busiest的比较算法


load_banlance触发
scheduler_tick
	trigger_load_balance 触发irq
run_rebalance_domains irq处理


