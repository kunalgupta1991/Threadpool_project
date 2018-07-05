// ThreadPoolProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
enum class JobType : char
{
	addPathNE = 0,
	Dia =10 ,
};
template<class T>
class CJobType
{
public:
	explicit CJobType(T mJob, T sJob)
	{
		_jobTypeTuple = make_tuple(mJob, sJob);
	}
	~CJobType()
	{

	}
	std::tuple<T, T> getType()
	{
		return _jobTypeTuple;
	}
private:
	std::tuple<T, T> _jobTypeTuple;
};
class Itask
{
public:
	virtual void exectue() = 0;
	
};
template<class T>
class Ctask : public Itask
{
	unique_ptr<T> fn;
public:
	void execute()
	{
		*(fn.get())();
	}
	bool registerMainProc(unique_ptr<T> main_proc)
	{
		try
		{
			fn = move(main_proc);
		}
		catch (...)
		{
			return false;
		}
		catch (exception t)
		{
			
		}
	}
};
class Icallback
{
public:
	Icallback() {};
	virtual ~Icallback() {};
};
template<class notifyJobCompletion, class notifyException>
class callBack : public Icallback
{
	unique_ptr<notifyJobCompletion> _completion;
	unique_ptr<notifyException> _exception;

	explicit callBack(unique_ptr<notifyJobCompletion> completion, unique_ptr<notifyException> exception):_completion(move(completion)),_exception(move(exception))
	{

	}
};
class Cjob : public Itask
{
public:
	CJobType<JobType> _jobType;
	int _jobId;
	unique_ptr<Icallback> _callback;
	Cjob(CJobType<JobType> jobType, int jobId, unique_ptr<Icallback> callback) :_jobType(jobType),_jobId(jobId),_callback(move(callback))
	{

	}


};

