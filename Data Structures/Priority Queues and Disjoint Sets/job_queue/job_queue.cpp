#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <limits>

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::swap;

struct Thread_ {
	Thread_():
		id(0), time_finish(0)
	{}

    Thread_(int id, long long time_finish):
        id(id),
        time_finish(time_finish)
    {}

    Thread_(const Thread_& th):
		id(th.id),
        time_finish(th.time_finish)
    {}

    int id; // thread id
    long long time_finish; // latest job finish time

	bool operator>(const Thread_& x) const
	{
		return (this->time_finish > x.time_finish) ||
			((this->time_finish == x.time_finish) && 
			(this->id > x.id));
	}

	bool operator<(const Thread_& x) const
	{
		return (this->time_finish < x.time_finish) ||
			((this->time_finish == x.time_finish) && 
			(this->id < x.id));
	}
};

class Priority_Queue_Zero { // zero-indexing queue

private:
	vector<Thread_> data_;
	int size_; // number of elements
	int maxSize_; // capacity;

	void SetSize(int n) { size_ = n; }

	void SetId(int index, int i) 
	{ 
		data_.at(index).id = i;
	}

	void SetFinishTime(int index, long long t) 
	{ 
		data_.at(index).time_finish = t;
	}

	int Parent(int i) const {return (i-1)/2;}
	
	int LeftChild(int i) const { return (2*i)+1;}
	
	int RightChild(int i) const { return (2*i)+2;}
	
	void SiftUp(int i) 
	{
		while((i>0) && (data_.at(Parent(i))>data_.at(i))) {
			swap(data_.at(Parent(i)), data_.at(i));
			i = Parent(i);
		}
	}

	void SiftDown(int i) 
	{
		int minIndex = i;
		int l = LeftChild(i);
		if((l<size_) && (data_.at(l) < data_.at(minIndex))) {
			minIndex = l;
		}
		int r = RightChild(i);
		if((r<size_) && (data_.at(r) < data_.at(minIndex))) {
			minIndex = r;
		}

		if(i!=minIndex) {
			swap(data_[i], data_[minIndex]);
			SiftDown(minIndex);
		}
	}

public:
	Priority_Queue_Zero(int maxSize_):
        size_(0), maxSize_(maxSize_)
    {
		data_.resize(maxSize_);
	}



	void operator=(const Thread_& x)
	{
		this->SetFinishTime(0, x.time_finish);
	}

	int GetNumberOfElements () const { return size_; }

	void Insert(int id, long long val) 
	{
		if(size_==maxSize_) {
			cerr << "priority_queue size limit exceeded" << endl;
			exit(EXIT_FAILURE);
		}

		++size_;
		SetId(size_-1, id); // zero - indexing
		SetFinishTime(size_-1, val); // zero - indexing
		SiftUp(size_-1);
	}

	Thread_ GetMin() const { return data_.at(0); }

	Thread_ ExtractMin() 
	{
		Thread_ result = data_.at(0);
		data_[0] = data_[size_-1];
		--size_;
		SiftDown(0);
		return result;
	}

	void Remove(int i) 
	{
		SetFinishTime(i, std::numeric_limits<long long>::max());
		SiftUp(i);
		ExtractMin();
	}

	void ChangePriority(long long val) 
	{
		long long val_old = GetMin().time_finish;
		data_[0].time_finish = val;
		if(val < val_old) { SiftUp(0); }
		else { SiftDown(0); }
	}
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

    void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
/*
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		vector<long long> next_free_time(num_workers_, 0);
		for (int i = 0; i < jobs_.size(); ++i) {
		  int duration = jobs_[i];
		  int next_worker = 0;
		  for (int j = 0; j < num_workers_; ++j) {
			if (next_free_time[j] < next_free_time[next_worker])
			  next_worker = j;
		  }
		  assigned_workers_[i] = next_worker;
		  start_times_[i] = next_free_time[next_worker];
		  next_free_time[next_worker] += duration;
		}
*/
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		Priority_Queue_Zero thread_pq(num_workers_);
		for(int j = 0; j<jobs_.size(); ++j) {
			if(thread_pq.GetNumberOfElements() < num_workers_) {
				int id = thread_pq.GetNumberOfElements(); // zero-indexing
				thread_pq.Insert(id, jobs_[j]); 
				assigned_workers_[j] = id;
				start_times_[j] = 0;
			}
			else {
				Thread_ thread_min(thread_pq.GetMin());
				assigned_workers_[j] = thread_min.id;
				start_times_[j] = thread_min.time_finish;
				thread_pq.ChangePriority(thread_min.time_finish + jobs_[j]);
			}
		}
	}	

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
