
template <typename T>
class Queue{

    struct Node{
        T data;
        int priority;
        Node *next;
    };

    Node *head;

public:

    Queue() {
        head = nullptr;
    }

    void push(T data, int priority) {
        if (!head)
            head = new Node{data, priority};

        else {
            Node *temp = head;

            if (priority > head->priority) {
                head = new Node{data, priority, head};
                return;
            }

            while (temp->next) {
                if (priority < temp->next->priority)
                    temp = temp->next;
                else
                    temp->next = new Node{data, priority, temp->next};
            }
            temp->next = new Node{data, priority};
        }
    }

    void popByHighest() {

        if (!head)
            return;

        Node *temp = head;
        head = temp->next;
        delete temp;
    }


    T getFront() {
        if (head)
        return head->data;
        else
            return "nothing";
    }

    int length() {

        int counter{};
        Node *temp = head;

        while (temp){
            ++counter;
            temp = temp->next;
        }

        return counter;
    };
};