

namespace s21 {
    template <class T>
    struct Node
    {
        using value_type = T;
        
        bool isRed;
        struct Node *parent, *left, *right;
        value_type data;
    };

    template <class T>
    class RedBlackTree
    {
        using value_type = T;
        using size_type = size_t;
        using reference = T &;
        using const_reference = const T &;

        public:
            RedBlackTree() {
                root_ = new Node;
                this->root;
            };
        private:
            Node *root_;
    };  
} // namespace s21
