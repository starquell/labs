#ifndef LAB1_STACK_LISTBASED_HPP
#define LAB1_STACK_LISTBASED_HPP

namespace Stack {

    template<typename T>
    class Listbased {

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

            auto temp = head;
            while (temp->next)
                temp = temp->next;

            delete temp;
            temp = nullptr;
        }

        value_type &front() const {

            auto temp = head;
            while (temp->next)
                temp = temp->next;

            return temp->data;
        }

        [[nodiscard]] bool empty() const {
            return !head;
        };
    };
}
#endif


