#ifndef LAB1_QUEUE_HPP
#define LAB1_QUEUE_HPP

namespace Queue {

    template<typename T>
    class Listbased{

        struct Node {
            T data;
            Node *next;
        };

        Node *head;

    public:
        using value_type = T;

        Listbased() : head(nullptr) {
        }

        void push(const value_type &data) {
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

        value_type &front() const {
            return head->data;
        }

        [[nodiscard]] bool empty() const {
            return !head;
        };

        ~Listbased() {

            auto *current = head;
            Node *next;

            while (current) {
                next = current->next;
                delete current;
                current = next;
            }
        }
    };
}
#endif //LAB1_QUEUE_HPP
