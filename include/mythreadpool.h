#ifndef THREAD_POOL_H
#define THREAD_POOL_H

/************************************************************************\
* 参考：https://github.com/progschj/ThreadPool
* 说明：有稍许调整
\************************************************************************/

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class threadpool {
public:
	threadpool(size_t);
	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>;
	~threadpool();

	/*edit by mingl*/
	// size of threads
	size_t get_workers_count();
	// size of undisposed tasks
	size_t get_tasksqueue_count();
	// size of idle threads (just reference)
	size_t working_count = 0;
	size_t get_idle_count_reference();
	/*end by mingl*/

private:
	// need to keep track of threads so we can join them
	std::vector< std::thread > workers;
	// the task queue
	std::queue< std::function<void()> > tasks;

	// synchronization
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;
};

// the constructor just launches some amount of workers
inline threadpool::threadpool(size_t threads)
	: stop(false)
{
	for (size_t i = 0; i < threads; ++i)
		workers.emplace_back(
			[this]
	{
		for (;;)
		{
			std::function<void()> task;

			{
				std::unique_lock<std::mutex> lock(this->queue_mutex);
				this->condition.wait(lock,
					[this] { return this->stop || !this->tasks.empty(); });
				if (this->stop && this->tasks.empty())
					return;
				task = std::move(this->tasks.front());
				this->tasks.pop();
			}

			++(this->working_count);
			task();
			--(this->working_count);
		}
	}
	);
}

// add new work item to the pool
template<class F, class... Args>
auto threadpool::enqueue(F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queue_mutex);

		// don't allow enqueueing after stopping the pool
		if (stop)
			throw std::runtime_error("enqueue on stopped threadpool");

		tasks.emplace([task]() { (*task)(); });
	}
	condition.notify_one();
	return res;
}

// the destructor joins all threads
inline threadpool::~threadpool()
{
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop = true;
	}
	condition.notify_all();
	for (std::thread &worker : workers)
		worker.join();
}

/*edit by mingl*/
inline size_t threadpool::get_workers_count()
{
	return working_count;
}

inline size_t threadpool::get_tasksqueue_count()
{
	return tasks.size();
}

inline size_t threadpool::get_idle_count_reference()
{
	return workers.size() - this->working_count;
}
/*end by mingl*/
#endif
