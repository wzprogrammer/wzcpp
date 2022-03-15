#include <sys/eventfd.h>
#include <sys/epoll.h>
class Looper {
public:
	Looper()
	{
		wakeFd = eventfd(0, EFD_CLOEXEC|EFD_NOBLOCK);

		epollFd = epoll_create(10);
		struct epoll_event eventItem;
		eventItem.events = EPOLLIN;
		eventItem.data.id = wakeFd;
		epoll_ctl(epollFd, EPOLL_CTL_ADD, wakeFd, eventItem);
	}
	int pollInner() {
		while (true)
		{
			#define MAX 3
			struct epoll_event events[MAX];
			int count = epoll_wait(epollFd,events,_INTEGRAL_MAX_BITS,0);
			for (int i = 0; i < count; i++)
			{

			}
		}
	}
private:
	int wakeFd;
	int epollFd;
};
