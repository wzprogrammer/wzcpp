struct cfs_rq {

};
struct rq {
	struct cfs_rq cfs;
};
void task_cpu(struct task_struct* task) {

}
//todo percpu
#define cfs_rq_of(cpu) 