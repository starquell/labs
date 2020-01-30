template <typename T>
class Listbased{

    struct Node{
        T data;
        Node *next;
    };

    Node *head;

public:

    Listbased() {
        head = nullptr;
    }

    void push (T data) {
        if (!head)
            head = new Node{data};
        else {
            Node *temp = head;

            while (temp->next)
                temp = temp->next;

            temp->next = new Node{data};
        }
    }

    void pop() {

        if (!head)
            return;

        Node *temp = head;
        head = temp->next;
        delete temp;
    }

    T getFront() {
        return head->data;
    }

    bool isEmpty() {
        return !head;
    };
};