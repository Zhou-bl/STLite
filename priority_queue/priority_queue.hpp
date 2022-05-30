#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {
template<typename T, class Compare = std::less<T>>
class priority_queue {
public:
    class Heap{
    public:
        class Node{//斜堆的结点
        public:
            T val;
            Node *lc, *rc;
            Node():val(0), lc(nullptr), rc(nullptr){}
            Node(const Node &rhs):val(rhs.val), lc(rhs.lc), rc(rhs.rc){}
            Node(const T &v):val(v), lc(nullptr), rc(nullptr){}
        };

        Node *root;
        size_t Size;

        void Swap_Node(Node * &a, Node * &b){
            Node *tmp = a;
            a = b;
            b = tmp;
        }

        Heap():root(nullptr), Size(0){} //默认构造

        Heap(const Heap &rhs){ //拷贝构造
            if(this == &rhs) return;
            Size = rhs.Size;
            Heap_Clone(rhs.root, root);
        }
        Heap &operator = (const Heap &rhs){
            if(this == &rhs) return *this;
            Heap_Clear(root);
            Heap_Clone(rhs.root, root);
            Size = rhs.Size;
            return *this;
        }
        void Heap_Clone(const Node *rhs, Node * &cur){//用于递归实现拷贝构造函数.
            if(rhs == nullptr) return;
            cur = new Node(*rhs);
            Heap_Clone(rhs->lc, cur->lc);
            Heap_Clone(rhs->rc, cur->rc);
        }
        void Heap_Clear(Node * &p){//用于析构函数即Clear
            if(p == nullptr) return;
            Heap_Clear(p->rc);
            Heap_Clear(p->lc);
            delete p;
        }
        Node* Heap_Merge(Node *a, Node *b){
            if(a == nullptr) return b;
            if(b == nullptr) return a;
            //小堆与大堆的右子堆合并
            //确保 a > b
            if(Compare()(a->val, b->val)) Swap_Node(a, b);
            a->rc = Heap_Merge(a->rc, b);
            Swap_Node(a->lc, a->rc);
            return a;
        }
        void Heap_Insert(const T &p){
            Node *tmp = new Node(p); //构建单节点堆
            root =  Heap_Merge(root, tmp);
            Size++;
        }
        const T& Top() const {
          return root->val;
        }
        void Pop(){
            Node *tmp = root;
            root = Heap_Merge(root->lc, root->rc);
            delete tmp;
            Size--;
        }
        void Merge(Heap &b){
            Size += b.Size;
            b.Size = 0;
            root = Heap_Merge(root, b.root);
            b.root = nullptr;
        }
        ~Heap(){
            Heap_Clear(root);
        }
    };
public:
    Heap h;
	priority_queue() {}
	priority_queue(const priority_queue &other):h(other.h){}
	~priority_queue() {}
	priority_queue &operator=(const priority_queue &other) {//记得要有返回值
        h = other.h;
        return *this;
    }
	const T & top() const {
        if(empty()) throw container_is_empty();
        return h.Top();
	}
	void push(const T &e) { h.Heap_Insert(e);}
	void pop() {
        if(empty()) throw container_is_empty();
        h.Pop();
	}
	size_t size() const { return h.Size;}
	bool empty() const { return !h.Size;}
	void merge(priority_queue &other) { h.Merge(other.h);}
};

}

#endif
