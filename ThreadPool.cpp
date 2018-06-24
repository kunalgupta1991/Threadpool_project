#include <iostream>
#include<mutex>
#include<vector>
#include<queue>
#include<set>
using namespace std;
class ThreadPool
{
	typedef function<void()> task;
	vector<thread> _threadpool_vec;
	queue<task> task_queue;
	condition_variable queue_condition;
	mutex queue_access_mutex;
public:
	ThreadPool(int n)
	{
		thread t1(&ThreadPool::Run,this);
		thread t2(&ThreadPool::Run,this);
		thread t3(&ThreadPool::Run,this);
		thread t4(&ThreadPool::Run,this);
		_threadpool_vec.push_back(move(t1));
		_threadpool_vec.push_back(move(t2));
		_threadpool_vec.push_back(move(t3));
		_threadpool_vec.push_back(move(t4));

	}
	void Run()
	{
		while (1)
		{
			unique_lock<mutex> ul(queue_access_mutex);
			if (!task_queue.empty())
			{
				task t = task_queue.front();
				task_queue.pop();
				ul.unlock();
				t();
			
			}
			else
			{

				ul.unlock();
			}
		
		}

	}
	bool trypost(task t)
	{
		unique_lock<mutex> ul(queue_access_mutex);
		task_queue.push(move(t));
		return true;

	}
	~ThreadPool()
	{
		for (auto &itr : _threadpool_vec)
		{
			itr.join();
	    }
	}

};
void fun1()
{
	while (1)
	{
		cout << this_thread::get_id() << " executing taks "<<endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}
int main()
{
		ThreadPool t(4);
		t.trypost(fun1);
		t.trypost(fun1);
		t.trypost(fun1);
		t.trypost(fun1);
	
}
