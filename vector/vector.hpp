#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector
    {
    private:
        size_t cap;
        size_t cur;
        T* array;
    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        class const_iterator;
        class iterator
        {
            // The following code is written for the C++ type_traits library.
            // Type traits is a C++ feature for describing certain properties of a type.
            // For instance, for an iterator, iterator::value_type is the type that the
            // iterator points to.
            // STL algorithms and containers may use these type_traits (e.g. the following
            // typedef) to work properly. In particular, without the following code,
            // @code{std::sort(iter, iter1);} would not compile.
            // See these websites for more information:
            // https://en.cppreference.com/w/cpp/header/type_traits
            // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
            // About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
            T* p;
            const vector* from;

        public:
            iterator() : p(nullptr), from(nullptr) {}
            iterator(T* tmp_p, const vector* tmp_from){
                p = tmp_p;
                from = tmp_from;
            }
            iterator(const iterator& rhs){
                p = rhs.p;
                from = rhs.from;
            }
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const
            {
                return iterator(p + n, from);
            }
            iterator operator-(const int &n) const
            {
                return iterator(p - n, from);
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {
                if(from != rhs.from) throw invalid_iterator();
                else return abs(p - rhs.p);
            }
            iterator& operator+=(const int &n)
            {
                p += n;
                return *this;
            }
            iterator& operator-=(const int &n)
            {
                p -= n;
                return *this;
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator tmp(*this);
                p++;
                return tmp;
            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
                p++;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator tmp(*this);
                p--;
                return tmp;
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
                p--;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const{
                return *p;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return p == rhs.p;
            }
            bool operator==(const const_iterator &rhs) const {
                return p == rhs.p;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator
        {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:
            /*TODO*/
            const T* p;
            const vector* from;
        public:
            const_iterator() : p(nullptr), from(nullptr){}
            const_iterator(T* tmp_p, const vector* tmp_from){
                p = tmp_p;
                from = tmp_from;
            }
            const_iterator(const const_iterator& rhs){
                p = rhs.p;
                from = rhs.from;
            }

            const_iterator operator+(const int &n) const
            {
                return const_iterator(p + n, from);
            }
            const_iterator operator-(const int &n) const
            {
                return const_iterator(p - n, from);
            }
            int operator-(const iterator &rhs) const
            {
                if(from != rhs.from) throw invalid_iterator();
                else return abs(p - rhs.p);
            }
            const_iterator& operator+=(const int &n)
            {
                p += n;
                return *this;
            }
            const_iterator& operator-=(const int &n)
            {
                p -= n;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator tmp(*this);
                p++;
                return tmp;
            }

            const_iterator& operator++() {
                p++;
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator tmp(*this);
                p--;
                return tmp;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                p--;
                return *this;
            }
            /**
             * TODO *it
             */
            const T operator*() const{
                return *p;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return p == rhs.p;
            }
            bool operator==(const const_iterator &rhs) const {
                return p == rhs.p;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };
        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        vector(size_t num = 10) {
            cur = 0;
            cap = num;
            array = (T*)malloc(cap * sizeof(T));
        }
        vector(const vector &other) {
            cur = other.cur;
            cap = other.cap;
            array = (T*)malloc(cap * sizeof(T));
            for(size_t i = 0; i < cur; ++i){
                new (array + i) T(other[i]);//不能直接赋值 要用拷贝构造函数
                //array[i] = other[i];
            }
        }
        /**
         * TODO Destructor
         */
        ~vector() {
            if(array != nullptr){
                for(int i = 0; i < cur; ++i) array[i].~T(); //显示调用析构函数
                free(array);
            }
        }
        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if(&other != this){
                for(int i = 0; i < cur; ++i) array[i].~T();
                free(array);
                cur = other.cur;
                cap = other.cap;
                array = (T*)malloc(cap * sizeof(T));
                for(size_t i = 0; i < cur; ++i){
                    new (array + i) T(other[i]);
                    //array[i] = other[i];
                }
            }
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, max_size)
         */
        T & at(const size_t &pos) {
            if(pos < 0 || pos >= cur) throw index_out_of_bound();
            return array[pos];
        }
        const T & at(const size_t &pos) const {
            if(pos < 0 || pos >= cur) throw index_out_of_bound();
            return array[pos];
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos) {
            if(pos < 0 || pos >= cur) throw index_out_of_bound();
            return array[pos];
        }
        const T & operator[](const size_t &pos) const {
            if(pos < 0 || pos >= cur) throw index_out_of_bound();
            return array[pos];
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T & front() const {
            if(!cur) throw container_is_empty();
            return array[0];
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T & back() const {
            if(!cur) throw container_is_empty();
            return array[cur - 1];
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(array, this);
        }
        const_iterator cbegin() const {
            return const_iterator(array, this);
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(array + cur, this);
        }
        const_iterator cend() const {
            return const_iterator(array + cur, this);
        }
        /**
         * checks whether the container is empty
         */
        bool empty() const { return !cur; }
        /**
         * returns the number of elements
         */
        size_t size() const { return cur; }
        /**
         * clears the contents
         */
        void clear() {
            for(int i = 0; i < cur; ++i) array[i].~T();
            cur = 0;
        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        void DoubleSpace(){
            size_t new_cap = cap * 2;
            T* NewSpace = (T*)malloc(new_cap * sizeof(T));
            for(int i = 0; i < cur; ++i) new (NewSpace + i) T(array[i]);
            for(int i = 0; i < cur; ++i) array[i].~T();
            free(array);
            array = NewSpace;
            cap = new_cap;
        }
        iterator insert(iterator pos, const T &value) {
            size_t arr_pos = pos - begin();
            if(cur + 1 == cap) DoubleSpace();//留一个尾元素
            cur++;
            for(size_t i = cur - 1; i > arr_pos; --i) array[i] = array[i - 1];
            array[arr_pos] = value;
            return iterator(array + arr_pos, this);
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(ind > cur) throw index_out_of_bound();
            if(cur + 1 == cap) DoubleSpace();
            cur++;
            for(size_t i = cur - 1; i > ind; --i) array[i] = array[i - 1];
            array[ind] = value;
            return iterator(array + ind, this);
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            size_t arr_pos = pos - begin();
            array[arr_pos].~T();
            cur--;
            for(size_t i = arr_pos; i < cur; ++i) array[i] = array[i + 1];
            return iterator(array + arr_pos, this);
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if(ind >= cur) throw index_out_of_bound();
            array[ind].~T();
            cur--;
            for(size_t i = ind; i < cur; ++i) array[i] = array[i + 1];
            return iterator(array + ind, this);
        }
        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if(cur + 1 == cap) DoubleSpace();
            new (array + cur) T(value);
            ++cur;
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if(empty()) throw container_is_empty();
            array[--cur].~T();
        }
    };

}

#endif
