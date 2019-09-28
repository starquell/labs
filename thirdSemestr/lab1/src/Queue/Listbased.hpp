#ifndef LAB1_LISTBASED_QUEUE_HPP
#define LAB1_LISTBASED_QUEUE_HPP


namespace Queue {
    template<typename T>
    class Listbased{

        struct Node {
            T data;
            Node* next;
        };

        using Ptr = Node*;

        Ptr head;
        std::size_t mSize;

    public:

        Listbased() : head(nullptr), mSize(0){
        }

        void push (const T &data) {
            if (!head)
                head = new Node {data};
            else {
                Ptr temp = head;
                while (temp->next)
                    temp = temp->next;

                temp->next = new Node {data};
            }

            ++mSize;
        }

        void pop() {

            if (!head)
                return;
            Ptr temp = head;
            head = temp->next;

            delete temp;

            --mSize;
        }

        T &front() const {
            if (head)
                return head->data;
            else
                throw std::out_of_range("");
        }

        [[nodiscard]] bool empty() const {
            return !head;
        };

        auto size() const {
            return mSize;
        }

        ~Listbased() {

            Ptr current = head;
            Ptr next;

            while (current) {
                next = current->next;
                delete current;
                current = next;
            }
        }
    };
}
#endif
