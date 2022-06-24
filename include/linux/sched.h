struct sched_entity {
	long sum_exect_time;
	long prev_sum_exect_time;
	long start_exec_time;

	long vruntime;
	int weight;
	int on_rq;
};
struct task_struct {
	struct sched_entity se;
};
