#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
	Buffer(int size):
        size_(size),
		num_elements(0),
        finish_time_()
    {}

    Response Process(const Request &request) {
		bool dropped_tmp = true;
		int start_time_tmp, finish_time_tmp;

        // write your code here
		if(finish_time_.empty()) { // first packet
			finish_time_tmp = request.arrival_time + request.process_time;
			dropped_tmp = false;
			start_time_tmp = request.arrival_time;
			++num_elements;
		} 
		else if(num_elements < size_) { // buffer not full
			++num_elements;
			dropped_tmp = false; 
			if(finish_time_.back() >= request.arrival_time) {
				start_time_tmp = finish_time_.back();
			} 
			else {
				start_time_tmp = request.arrival_time;
			}			
			finish_time_tmp = start_time_tmp + request.process_time;
		} 
		else if(finish_time_.front() <= request.arrival_time) { // buffer full
			dropped_tmp = false;
			if(finish_time_.back() >= request.arrival_time) {
				start_time_tmp = finish_time_.back();
			} 
			else {
				start_time_tmp = request.arrival_time;
			}			
			finish_time_tmp = start_time_tmp + request.process_time;
			finish_time_.pop();
		} 

		if(dropped_tmp) {
			return Response(dropped_tmp, -1);
		}
		else {
			finish_time_.push(finish_time_tmp);
			return Response(dropped_tmp, start_time_tmp);
		}

    }
private:
    int size_;
	int num_elements; // new addition
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
