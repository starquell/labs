#ifndef LAB1_STACK_LISTBASED_HPP
#define LAB1_STACK_LISTBASED_HPP

namespace Stack {

    template <class T>
    class Listbased {

        struct Node {
            T data;
            Node *next;
        };

        using Ptr = Node*;
        Ptr head;
        std::size_t mSize;

    public:

        Listbased() : head(nullptr), mSize(0) {
        }

        void push(const T &data) {

            if (!head)
                head = new Node{data};
            else {
                Ptr temp = head;
                while (temp->next)
                    temp = temp->next;
                temp->next = new Node{data};
            }
            ++mSize;
        }

        void pop() {

            if (!head)
                return;

            if (!head->next) {
                delete head;
                head = nullptr;
            }
            Ptr temp = head;
            while (temp->next->next)
                temp = temp->next;

            delete temp->next;
            temp->next = nullptr;

            --mSize;
        }

        T& top() const {

            if (!head)
                throw std::out_of_range("");

            Ptr temp = head;
            while (temp->next)
                temp = temp->next;
            return temp->data;
        }

        [[nodiscard]] bool empty() const {
            return !head;
        };

        auto size() const {
            return mSize;
        }


        ~Listbased()
        {
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

