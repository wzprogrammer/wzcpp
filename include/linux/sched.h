struct sched_avg {
	unsigned long load_avg;
	unsigned long runnable_avg;
	unsigned long util_avg;
};
struct sched_entity {
	long sum_exec_time;
	long prev_sum_exec_time;
	long start_exec_time;

	long vruntime;
	int weight;
	int on_rq;

	struct sched_avg avg;
};
struct cfs_rq {
	struct sched_avg avg;
	struct sched_entity* curr;
};
struct task_struct {
	struct sched_entity se;
	struct cfs_rq* cfs_rq;
};
struct rq {
	struct cfs_rq cfs_rq;
	unsigned long cpu_capacity_orig;
};
