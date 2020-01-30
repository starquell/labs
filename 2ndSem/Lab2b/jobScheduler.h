#include <mutex>

class JobScheduler{

    const unsigned limit = 1000;

    struct Task {
        std::string task;
        unsigned time;
        Task *next;
    };

    Task *head;
    std::mutex mtx;

public:

    JobScheduler() : head(nullptr)
    {
        std::thread work {&JobScheduler::Working, this};
        work.detach();
    }

    void push (const std::string &task, unsigned time) {
        mtx.lock();

        if (!head)
            head = new Task{task, time};

        else {
            Task *temp = head;

            while (temp->next)
                temp = temp->next;

            temp->next = new Task{task, time};
        }
        mtx.unlock();
    }

    void pop() {

        mtx.lock();

        if (!head)
            return;

        Task *temp = head;
        head = temp->next;
        delete temp;

        mtx.unlock();
    }

    void Working() {

        while (true) {
            while (!isEmpty()) {

                if (getFront()->time <= limit)
                    pop();

                else {
                    push(getFront()->task, getFront()->time - limit);
                    pop();
                }
                std::this_thread::sleep_for(1000ms);
            }
        }
    }

    Task* getFront() {
        mtx.lock();

        if (head) {
            mtx.unlock();
            return head;
        }
        else {
            mtx.unlock();
            return new Task{"null", 0};
        }

    }

    bool isEmpty(){
        return !head;
    }

    ~JobScheduler(){
        delete head;
    }
};