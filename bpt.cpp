#ifndef SJTU_EXCEPTIONS_HPP
#define SJTU_EXCEPTIONS_HPP

#include <cstddef>
#include <cstring>
#include <string>

namespace sjtu {

    class exception {
    protected:
        const std::string variant = "";
        std::string detail = "";
    public:
        exception() {}
        exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
        virtual std::string what() {
            return variant + " " + detail;
        }
    };

    class index_out_of_bound : public exception {
        /* __________________________ */
    };

    class runtime_error : public exception {
        /* __________________________ */
    };

    class invalid_iterator : public exception {
        /* __________________________ */
    };

    class container_is_empty : public exception {
        /* __________________________ */
    };
}

#endif
#ifndef BPT_VECTOR_H
#define BPT_VECTOR_H

#include <climits>
#include <cstddef>

constexpr int Size = 100;

namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector
    {
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
            friend vector;
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
            T* pos;
            vector<T>* target;
        public:
            iterator(T* p = nullptr, vector* vp = nullptr) : target(vp), pos(p) {}
            iterator(const iterator &a) : target(a.target), pos(a.pos) {}
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const
            {
                //TODO
                return iterator(pos+n,this->target);
            }
            iterator operator-(const int &n) const
            {
                //TODO
                return iterator(pos-n,this->target);
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {
                //TODO
                if (target != rhs.target) {
                    throw invalid_iterator();
                } else {
                    return pos - rhs.pos;
                }
            }
            iterator& operator+=(const int &n)
            {
                //TODO
                pos += n;
                return *this;
            }
            iterator& operator-=(const int &n)
            {
                //TODO
                pos -= n;
                return *this;
            }
            /**
             * TODO iter++
             */
            iterator operator++(int)
            {
                iterator temp = *this;
                pos++;
                return temp;
            }
            /**
             * TODO ++iter
             */
            iterator& operator++()
            {
                pos++;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int)
            {
                iterator temp = *this;
                pos--;
                return temp;
            }
            /**
             * TODO --iter
             */
            iterator& operator--()
            {
                pos--;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const { return *pos; }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const { return pos == rhs.pos; }
            bool operator==(const const_iterator &rhs) const { return pos == rhs.pos; }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const { return pos != rhs.pos; }
            bool operator!=(const const_iterator &rhs) const { return pos != rhs.pos; }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator
        {
            friend vector;
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:
            /*TODO*/
            T* pos;
            const vector<T>* target;

        public:
            const_iterator(T* p = nullptr,const vector* vp = nullptr) : target(vp), pos(p) {}
            const_iterator(const const_iterator &a) : target(a.target), pos(a.pos) {}
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            const_iterator operator+(const int &n) const
            {
                //TODO
                return const_iterator(pos+n,this->target);
            }
            const_iterator operator-(const int &n) const
            {
                //TODO
                return const_iterator(pos-n,this->target);
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const
            {
                //TODO
                if (target != rhs.target) {
                    throw invalid_iterator();
                } else {
                    return pos - rhs.pos;
                }
            }
            const_iterator& operator+=(const int &n)
            {
                //TODO
                pos += n;
                return *this;
            }
            const_iterator& operator-=(const int &n)
            {
                //TODO
                pos -= n;
                return *this;
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int)
            {
                const_iterator temp = *this;
                pos++;
                return temp;
            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++()
            {
                pos++;
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int)
            {
                const_iterator temp = *this;
                pos--;
                return temp;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--()
            {
                pos--;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const { return *pos; }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const { return pos == rhs.pos; }
            bool operator==(const const_iterator &rhs) const { return pos == rhs.pos; }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const { return pos != rhs.pos; }
            bool operator!=(const const_iterator &rhs) const { return pos != rhs.pos; }
        };

        friend iterator;
        friend const_iterator;

    private:
        T* data;
        int _size;
        int top;
        void resize()
        {
            _size *= 2;
            T* temp = reinterpret_cast<T*>(new char[sizeof(T) * _size]);
            for (int i=0;i<=top;i++) {
                new (&temp[i]) T(data[i]);
                (data + i)->~T();
            }
            delete [] reinterpret_cast<char *>(data);
            data = temp;
        }
    public:
        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */
        vector() : _size(Size), top(-1)
        {
            data = reinterpret_cast<T*>(new char[sizeof(T) * _size]);
        }
        vector(const vector &other) : _size(other._size), top(other.top)
        {
            data = reinterpret_cast<T*>(new char[sizeof(T) * _size]);
            for (size_t i = 0; i < _size; i++) {
                new (&data[i]) T(other.data[i]);
            }
        }
        /**
         * TODO Destructor
         */
        ~vector()
        {
            for (int i = 0; i <= top; i++) (data + i)->~T();
            delete[] reinterpret_cast<char *>(data);
        }
        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other)
        {
            if (this == &other) {
                return *this;
            }
            for (size_t i = 0; i < _size; i++) (data + i)->~T();
            delete[] reinterpret_cast<char *>(data);
            _size = other._size;
            top = other.top;
            data = reinterpret_cast<T*>(new char[sizeof(T) * _size]);
            for (int i=0;i<=top;i++) {
                new (&data[i]) T(other.data[i]);
            }
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, _size)
         */
        T & at(const size_t &pos)
        {
            if (pos < 0 || pos > top) {
                throw index_out_of_bound();
            }
            return data[pos];
        }
        const T & at(const size_t &pos) const
        {
            if (pos < 0 || pos > top) {
                throw index_out_of_bound();
            }
            return data[pos];
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, _size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos)
        {
            if (pos < 0 || pos > top) {
                throw index_out_of_bound();
            }
            return data[pos];
        }
        const T & operator[](const size_t &pos) const
        {
            if (pos < 0 || pos > top) {
                throw index_out_of_bound();
            }
            return data[pos];
        }
        /**
         * access the first element.
         * throw container_is_empty if _size == 0
         */
        const T & front() const
        {
            if (empty()) {
                throw container_is_empty();
            }
            return data[0];
        }
        /**
         * access the last element.
         * throw container_is_empty if _size == 0
         */
        const T & back() const
        {
            if (empty()) {
                throw container_is_empty();
            }
            return data[top];
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() { return iterator(data,this); }
        const_iterator cbegin() const { return const_iterator(data,this); }
        /**
         * returns an iterator to the end.
         */
        iterator end() { return iterator(data + top + 1,this); }
        const_iterator cend() const {  return const_iterator(data + top + 1,this); }
        /**
         * checks whether the container is empty
         */
        bool empty() const { return top == -1; }
        /**
         * returns the number of elements
         */
        size_t size() const { return top + 1; }
        /**
         * clears the contents
         */
        void clear() { top = -1; }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value)
        {
            if (top == _size - 1) {
                resize();
            }
            for (int i = top;i >= pos.pos - data;i--) {
                data[i + 1] = data[i];
            }
            *(pos) = value;
            top++;
            return pos;
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > _size (in this situation ind can be _size because after inserting the _size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value)
        {
            if (ind < 0 || ind > top + 1) {
                throw index_out_of_bound();
            }
            if (top == _size - 1) {
                resize();
            }
            for (int i = top;i >= ind;i--) {
                new (&data[i+1]) T(data[i]);
                //data[i + 1] = data[i];
            }
            new (&data[ind]) T(value);
            // data[ind] = value;
            top++;
            return iterator(data + ind,this);
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos)
        {
            if (empty()) {
                throw container_is_empty();
            }
            (data + top)->~T();
            for (int i = pos.pos - data;i < top;i++) {
                new (&data[i]) T(data[i+1]);
                //data[i] = data[i + 1];
            }

            top--;
            return pos;
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= _size
         */
        iterator erase(const size_t &ind)
        {
            if (empty()) {
                throw container_is_empty();
            }
            if (ind >= _size) {
                throw index_out_of_bound();
            }
            for (int i = ind;i < top;i++) {
                data[i] = data[i + 1];
            }
            (data + top)->~T();
            top--;
            return iterator(data + ind,this);
        }
        /**
         * adds an element to the end.
         */
        void push_back(const T &value)
        {
            if (top == _size - 1) {
                resize();
            }
            top++;
            new (&data[top]) T(value);
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if _size() == 0
         */
        void pop_back()
        {
            if (empty()) {
                throw container_is_empty();
            }
            (data + top)->~T();
            top--;
        }
    };


}

#endif //BPT_VECTOR_H
#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

//the first info is for the head of empty node chain
//the second info is for the number of empty node in the chain
template<class T, int info_len = 2>
class MemoryRiver {
private:
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out);
        int tmp = sizeof(int) * info_len;
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        tmp = 0;
        for (int i = 1; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.open(file_name);
        file.seekg(sizeof(int) * (n - 1));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name);
        file.seekp(sizeof(int) * (n - 1));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    int write(T &t) {
        file.open(file_name);
        int pos, num, r_index;
        file.seekg(0);
        file.read(reinterpret_cast<char *>(&pos), sizeof(int));
        r_index = pos;
        file.read(reinterpret_cast<char *>(&num), sizeof(int));
        //no empty node exists
        if (!num) {
            file.seekp(0);
            pos += sizeofT + sizeof(int);
            file.write(reinterpret_cast<char *>(&pos), sizeof(int));
            file.seekp(pos - sizeofT - sizeof(int));
            file.write(reinterpret_cast<char *>(&num), sizeof(int));
            file.write(reinterpret_cast<char *>(&t), sizeofT);
        }
        else {
            --num;
            file.seekp(pos);
            file.read(reinterpret_cast<char *>(&pos), sizeof(int));
            file.write(reinterpret_cast<char *>(&t), sizeofT);
            file.seekp(0);
            file.write(reinterpret_cast<char *>(&pos), sizeof(int));
            file.write(reinterpret_cast<char *>(&num), sizeof(int));
        }
        file.close();
        return r_index;
    }

    void update(T &t, const int &index) {
        file.open(file_name);
        file.seekp(index + sizeof(int));
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
    }

    void read(T &t, const int &index) {
        file.open(file_name);
        file.seekg(index + sizeof(int));
        file.read(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
    }

    void Delete(int index) {
        int a, num;
        file.open(file_name);
        file.read(reinterpret_cast<char *>(&a), sizeof(int));
        file.read(reinterpret_cast<char *>(&num), sizeof(int));
        ++num;
        file.seekg(index);
        file.write(reinterpret_cast<char *>(&a), sizeof(int));
        file.seekp(0);
        file.write(reinterpret_cast<char *>(&index), sizeof(int));
        file.write(reinterpret_cast<char *>(&num), sizeof(int));
        file.close();
    }
};

#endif //BPT_MEMORYRIVER_HPP




#ifndef BPT_BPT_HPP
#define BPT_BPT_HPP

#include <string>
#include <search.h>

constexpr int data_size = 400;
template <class Key, class T, int M = 100, int L = 100>
class BPTree {
private:
    class node;
    class data_vector {
        friend node;
        friend BPTree;
        int size, next;
        T data[data_size] = {0};

    public:
        data_vector() : size(0), next(0) {}
        ~data_vector() = default;

        bool insert(const T& val) { // return false if repeated
            if (val > data[size-1]) {
                data[size] = val;
                ++size;
                return true;
            }
            int l = 0, r = size - 1, mid;
            while (l < r) { // data[i] >= val
                mid = (l + r) >> 1;
                if (data[mid] < val) l = mid + 1;
                else r = mid;
            }
            if (data[l] == val) return false;
            for (int i=size;i>l;i--) data[i] = data[i-1];
            data[l] = val;
            ++size;
            return true;
        }

        // 1 : success 2 : > max 3 : not exist
        int erase(const T& val) {
            if (val > data[size-1]) return 2;
            int l = 0, r = size - 1, mid;
            while (l < r) {
                mid = (l + r) >> 1;
                if (data[mid] < val) l = mid + 1;
                else r = mid;
            }
            if (data[l] == val) {
                --size;
                for (int i=l;i<size;i++) data[i] = data[i+1];
                return 1;
            }
            else return 3;
        }
    };

    class node {
        friend data_vector;
        friend BPTree;
        bool is_leaf;
        int size, next;
        int son[std::max(M,L) + 2] = {0};
        Key key[std::max(M,L) + 2];
    public:
        node() : is_leaf(false), size(0), next(0) {}
        node(bool leaf, int len) : is_leaf(leaf), size(len), next(0) {}
        ~node() = default;

        // key[i] > val
        int upper_bound(const Key& val) {
            if (val >= key[size-1]) return size;
            int l = 0, r = size - 1, mid;
            while (l < r) {
                mid = (l + r) >> 1;
                if (key[mid] <= val) l = mid + 1;
                else r = mid;
            }
            return l;
        }
        // key[i] >= val
        std::pair<bool, int> lower_bound(const Key& val) {
            if (val > key[size-1]) return std::pair<bool, int>(false, size);
            int l = 0, r = size - 1, mid;
            while (l < r) {
                mid = (l + r) >> 1;
                if (key[mid] < val) l = mid + 1;
                else r = mid;
            }
            if (key[l] == val) return std::pair<bool, int>(true, l);
            else return std::pair<bool, int>(false, l);
        }
    };

    friend node;
    friend data_vector;

    int root, size;
//    MemoryRiver<node, 4> memory_node;
//    MemoryRiver<data_vector> memory_data;
    std::fstream datafile;
    std::fstream nodefile;
    std::string file_name;
    int write(data_vector &t) {
        int pos, num, r_index;
        datafile.seekp(0);
        datafile.seekg(0);
        datafile.read(reinterpret_cast<char *>(&pos), sizeof(int));
        r_index = pos;
        datafile.read(reinterpret_cast<char *>(&num), sizeof(int));
        //no empty node exists
        if (!num) {
            datafile.seekp(0);
            pos += sizeof(t) + sizeof(int);
            datafile.write(reinterpret_cast<char *>(&pos), sizeof(int));
            datafile.seekp(pos - sizeof(t) - sizeof(int));
            datafile.write(reinterpret_cast<char *>(&num), sizeof(int));
            datafile.write(reinterpret_cast<char *>(&t), sizeof(t));
        }
        else {
            --num;
            datafile.seekp(pos);
            datafile.read(reinterpret_cast<char *>(&pos), sizeof(int));
            datafile.write(reinterpret_cast<char *>(&t), sizeof(t));
            datafile.seekp(0);
            datafile.write(reinterpret_cast<char *>(&pos), sizeof(int));
            datafile.write(reinterpret_cast<char *>(&num), sizeof(int));
        }
        return r_index;
    }

    void update(data_vector &t, const int &index) {
        datafile.seekp(0);
        datafile.seekg(0);
        datafile.seekp(index + sizeof(int));
        datafile.write(reinterpret_cast<char *>(&t), sizeof(t));
    }

    void read(data_vector &t, const int &index) {
        datafile.seekp(0);
        datafile.seekg(0);
        datafile.seekg(index + sizeof(int));
        datafile.read(reinterpret_cast<char *>(&t), sizeof(t));
    }

    void Delete(int index) {
//        datafile.seekp(0);
//        datafile.seekg(0);
//        int a, num;
//        datafile.read(reinterpret_cast<char *>(&a), sizeof(int));
//        datafile.read(reinterpret_cast<char *>(&num), sizeof(int));
//        ++num;
//        datafile.seekg(index);
//        datafile.write(reinterpret_cast<char *>(&a), sizeof(int));
//        datafile.seekp(0);
//        datafile.write(reinterpret_cast<char *>(&index), sizeof(int));
//        datafile.write(reinterpret_cast<char *>(&num), sizeof(int));
    }
    int nwrite(node &t) {
        int pos, num, r_index;
        nodefile.seekg(0);
        nodefile.seekp(0);
        nodefile.read(reinterpret_cast<char *>(&pos), sizeof(int));
        r_index = pos;
        nodefile.read(reinterpret_cast<char *>(&num), sizeof(int));
        //no empty node exists
        if (!num) {
            nodefile.seekp(0);
            pos += sizeof(t) + sizeof(int);
            nodefile.write(reinterpret_cast<char *>(&pos), sizeof(int));
            nodefile.seekp(pos - sizeof(t) - sizeof(int));
            nodefile.write(reinterpret_cast<char *>(&num), sizeof(int));
            nodefile.write(reinterpret_cast<char *>(&t), sizeof(t));
        }
        else {
            --num;
            nodefile.seekp(pos);
            nodefile.read(reinterpret_cast<char *>(&pos), sizeof(int));
            nodefile.write(reinterpret_cast<char *>(&t), sizeof(t));
            nodefile.seekp(0);
            nodefile.write(reinterpret_cast<char *>(&pos), sizeof(int));
            nodefile.write(reinterpret_cast<char *>(&num), sizeof(int));
        }
        return r_index;
    }

    void nupdate(node &t, const int &index) {
        nodefile.seekg(0);
        nodefile.seekp(0);
        nodefile.seekp(index + sizeof(int));
        nodefile.write(reinterpret_cast<char *>(&t), sizeof(t));
    }

    void nread(node &t, const int &index) {
        nodefile.seekg(0);
        nodefile.seekp(0);
        nodefile.seekg(index + sizeof(int));
        nodefile.read(reinterpret_cast<char *>(&t), sizeof(t));
    }

    void nDelete(int index) {
//        nodefile.seekg(0);
//        nodefile.seekp(0);
//        int a, num;
//        nodefile.read(reinterpret_cast<char *>(&a), sizeof(int));
//        nodefile.read(reinterpret_cast<char *>(&num), sizeof(int));
//        ++num;
//        nodefile.seekg(index);
//        nodefile.write(reinterpret_cast<char *>(&a), sizeof(int));
//        nodefile.seekp(0);
//        nodefile.write(reinterpret_cast<char *>(&index), sizeof(int));
//        nodefile.write(reinterpret_cast<char *>(&num), sizeof(int));
    }

    void get_info_node(int &tmp, int n) {
        if (n > 4) return;
        nodefile.seekp(0);
        nodefile.seekg(0);
        nodefile.seekg(sizeof(int) * (n - 1));
        nodefile.read(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    void write_info_node(int tmp, int n) {
        if (n > 4) return;
        nodefile.seekp(0);
        nodefile.seekg(0);
        nodefile.seekp(sizeof(int) * (n - 1));
        nodefile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

public:
    explicit BPTree(const std::string& name) : file_name(name) {
        size = 0;
        nodefile.open(name + "node", std::ios::in);
        if (!nodefile) {
//            memory_node.initialise();
//            memory_data.initialise();
            datafile.open(name + "data", std::ios::out);
            datafile.seekp(0);
            datafile.seekg(0);
            int tmp = sizeof(int) * 2;
            datafile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
            tmp = 0;
            for (int i = 1; i < 2; ++i)
                datafile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
            datafile.close();

            nodefile.open(name + "node", std::ios::out);
            nodefile.seekp(0);
            nodefile.seekg(0);
            int ntmp = sizeof(int) * 4;
            nodefile.write(reinterpret_cast<char *>(&ntmp), sizeof(int));
            ntmp = 0;
            for (int i = 1; i < 4; ++i)
                nodefile.write(reinterpret_cast<char *>(&ntmp), sizeof(int));
            nodefile.close();
        }
        else {
//            memory_node.get_info(root,3);
//            memory_node.get_info(size,4);
//            file.close();
            nodefile.close();
            nodefile.open(name + "node");
            nodefile.seekp(0);
            nodefile.seekg(0);
            get_info_node(root,3);
            get_info_node(size,4);
            nodefile.close();
        }
        datafile.open(name + "data");
        nodefile.open(name + "node");
        nodefile.seekp(0);
        nodefile.seekg(0);
        datafile.seekp(0);
        datafile.seekg(0);
    }
    ~BPTree() {
        nodefile.close();
        nodefile.open(file_name + "node");
        nodefile.seekp(0);
        nodefile.seekg(0);
        write_info_node(root,3);
        write_info_node(size,4);
        datafile.close();
        nodefile.close();
    }

    sjtu::vector<T> find(const Key& val) {
        sjtu::vector<T> ret;
        if (size == 0) return ret;
        int pos = root;
        node temp;
        data_vector ans;
        nread(temp,pos);
        while (!temp.is_leaf) { // search down toward the leaf
            int son = temp.upper_bound(val);
            nread(temp,temp.son[son]);
        }
        // reach the leaf
        auto tar = temp.lower_bound(val);
        if (tar.first) {
            int leaf = temp.son[tar.second];
            while (leaf != 0) {
                read(ans, leaf);
                for (int i = 0; i < ans.size; i++) ret.push_back(ans.data[i]);
                leaf = ans.next;
            }
        }
        return ret;
    }
    // insert into an empty tree
    void insert_empty(const Key& key, const T& val) {
        node new_node(true, 1);
        data_vector new_data;
        new_data.data[new_data.size++] = val;
        new_node.key[0] = key;
        new_node.son[0] = write(new_data);
        root = nwrite(new_node);
        ++size;
    }
    // insert a value to existing key
    void insert_to_data(node& now, const T& val, int pos) {
        // pos is memory_index
        data_vector data;
        read(data, pos);
        while (data.data[data.size-1] < val) { // < instead of <= to deal with repeated value
            if (data.size < data_size && data.next == 0) { // the vector is not full and val > all value
                data.data[data.size++] = val;
                update(data, pos);
                return;
            }
            if (data.next) pos = data.next; // in case last vector is full
            else { // last vector is full and T > all
                data_vector new_data;
                new_data.data[new_data.size++] = val;
                data.next = write(new_data);
                update(data, pos);
                return;
            }
            read(data, pos);
        }
        // now data max >= val
        if (data.size < data_size) { // is not full
            if(data.insert(val)) update(data, pos); // not repeated
        }
        else { // full -> split
            data_vector split;
            for (int i=data_size/2;i<data_size;i++)
                split.data[split.size++] = data.data[i];
            data.size /= 2;
            if (val > data.data[data.size-1]) split.insert(val);
            else data.insert(val);
            split.next = data.next;
            data.next = write(split);
            update(data, pos); // key is updated on the outer recursion
        }
        // some situation omitted?
    }
    int insert_new_data(node& now, const Key& key, const T& val, int pos) {
        // pos is the lower_index
        for (int i=now.size-1;i>=pos;i--) {
            now.key[i+1] = now.key[i];
            now.son[i+1] = now.son[i];
        }
        data_vector new_data, last_vec;
        new_data.data[new_data.size++] = val;
        now.key[pos] = key;
        now.son[pos] = write(new_data);
        now.size++;
        size++;
        // need split
        if (now.size > M) {
            node split;
            split.is_leaf = true;
            for (int i=now.size/2;i<now.size;i++) {
                split.key[split.size++] = now.key[i];
                split.son[split.size-1] = now.son[i];
            }
            now.size /= 2;
            split.next = now.next;
            split.is_leaf = true;
            now.next = nwrite(split);
            return now.next;
        }
        return 0;
    }
    // recursively search-insert and split
    std::pair<int, Key> insert(const Key& key, const T& val, int pos) {
        // pos is the memory_index of node
        node now;
        nread(now,pos);
        std::pair<int, Key> ret(0, key);
        if (now.is_leaf) { // recurve to the leaf
            auto ser = now.lower_bound(key);
            // key has existed
            if (ser.first) insert_to_data(now, val, now.son[ser.second]);
                // need update node??
                // need to create a new data vector
            else {
                ret.first = insert_new_data(now, key, val, ser.second);
                nupdate(now, pos);
                nread(now, ret.first);
                ret.second = now.key[0]; // key and memory_index of split node
            }
            return ret;
        }
        // node is not leaf
        int upper = now.upper_bound(key);
        std::pair<int, Key> new_pair = insert(key, val, now.son[upper]);
        if (new_pair.first == 0) return new_pair; // exit of recursion
        // update upper layer of node
        for (int i=now.size;i>upper;i--)
            now.key[i] = now.key[i-1];
        for (int i=now.size+1;i>upper+1;i--)
            now.son[i] = now.son[i-1];
        now.key[upper] = new_pair.second;
        now.son[upper+1] = new_pair.first;
        now.size++;
        if (now.size <= M) {
            nupdate(now, pos);
            return ret;
        }
            // node is oversize after updated
        else if (now.size > M) {
            node split;
            for (int i=(now.size+1)/2;i<now.size;i++) {
                split.key[split.size++] = now.key[i];
                split.son[split.size-1] = now.son[i];
            } // skip middle node
            split.son[split.size] = now.son[now.size];
            now.size = (now.size + 1) / 2 - 1;
            split.next = now.next; // ??
            now.next = nwrite(split);
            int new_key = split.son[0];
            nread(split, new_key);
            ret.first = now.next;
            ret.second = now.key[now.size];
            nupdate(now, pos);
            return ret;
        }
    }
    void insert(const Key& key, const T& val) {
        if (size == 0) { // tree is empty
            insert_empty(key, val);
            return;
        }
        // tree is not empty
        std::pair<int, Key> new_pair = insert(key,val,root);
        if (new_pair.first) {
            // root need split
            node new_root;
            new_root.is_leaf = false;
            new_root.key[0] = new_pair.second;
            new_root.son[0] = root;
            new_root.son[1] = new_pair.first;
            new_root.size++;
            new_root.next = 0;
            root = nwrite(new_root);
        }
    }

    void remove(const Key& key, const T& val) {
        if (size == 0) return;

        node now;
        nread(now, root);
        if (now.is_leaf) {
            std::pair<bool, int>ser = now.lower_bound(key);
            if (!ser.first) return; // key don't exist
            data_vector data;
            int pos = now.son[ser.second],prev;
            read(data, pos);
            while (data.data[data.size-1] < val) {
                if (data.next == 0) return; // val > all -> no matching (key,val)
                prev = pos; // track previous vector to maintain "next"
                pos = data.next;
                read(data, pos);
            }
            // now data.data max >= val
            int flag = data.erase(val);
            if (flag == 1 && data.size == 0) {
                // erase val successfully
                Delete(pos);
                // vector is empty after removed
                if (pos == now.son[ser.second]) {
                    // the first vector of this key
                    if (data.next == 0) {
                        // this key has no value and need deleting
                        size--;
                        now.size--;
                        if (size == 0) { // tree is empty
                            // memory_node.initialise();
                            // memory_data.initialise();

                            //datafile.open(file_name + "data", std::ios::out);
                            nodefile.seekp(0);
                            nodefile.seekg(0);
                            datafile.seekp(0);
                            datafile.seekg(0);
                            int tmp = sizeof(int) * 2;
                            datafile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
                            tmp = 0;
                            for (int i = 1; i < 2; ++i)
                                datafile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
                            //datafile.close();

                            //nodefile.open(file_name + "node", std::ios::out);
                            int ntmp = sizeof(int) * 4;
                            nodefile.write(reinterpret_cast<char *>(&ntmp), sizeof(int));
                            ntmp = 0;
                            for (int i = 1; i < 4; ++i)
                                nodefile.write(reinterpret_cast<char *>(&ntmp), sizeof(int));
                            //nodefile.close();
                            return;
                        }
                        for (int i=ser.second;i<now.size;i++) {
                            now.son[i] = now.son[i+1];
                            now.key[i] = now.key[i+1];
                        }
                        nupdate(now,root);
                        return;
                    }
                    else { // son[i] -> next vector
                        now.son[ser.second] = data.next;
                        nupdate(now,root);
                        return;
                    }
                }
                else {
                    // middle vector is deleted
                    data_vector pre_data;
                    read(pre_data,prev);
                    pre_data.next = data.next;
                    update(pre_data,prev);
                    return;
                }
            }
            else update(data,pos);
            return;
        }

        remove(now, key, val, root, now, -1);
        // search down to leaf
        nread(now,root);
        if (now.size == 0) {
            nDelete(root);
            root = now.son[0];
        }
    }
    // remove when root is the only leaf
    void remove_from_leaf(node &fa, const Key& key, const T& val, int idx, node &fa_fa, int idx_fa_fa) {
        // ind is the memory_index of fa
        node now;
        int ind_fa = fa.upper_bound(key); // now is son[ind_fa] of fa
        nread(now,fa.son[ind_fa]);
        std::pair<bool, int>ser = now.lower_bound(key);
        if (!ser.first) return; // key don't exist
        data_vector data;
        int pos = now.son[ser.second],prev;
        read(data, pos);
        while (data.data[data.size-1] < val) {
            if (data.next == 0) return; // val > all -> no matching (key,val)
            prev = pos; // track previous vector to maintain "next"
            pos = data.next;
            read(data, pos);
        }
        // now data.data max >= val
        int flag = data.erase(val);
        if (flag == 1 && data.size == 0) {
            // erase val successfully
            Delete(pos);
            // vector is empty after removed
            if (pos == now.son[ser.second]) {
                // the first vector of this key
                if (data.next == 0) {
                    // this key has no value and need deleting
                    if (ser.second == 0 && ind_fa == 0 && idx_fa_fa != -1 && idx_fa_fa != 0) {
                        fa_fa.key[idx_fa_fa-1] = now.key[1];
                        //nupdate(fa_fa,fa_fa);
                    }
                    --size;
                    --now.size;
                    if (size == 0) { // tree is empty
//                        memory_node.initialise();
//                        memory_data.initialise();

                        //datafile.open(file_name + "data", std::ios::out);
                        nodefile.seekp(0);
                        nodefile.seekg(0);
                        datafile.seekp(0);
                        datafile.seekg(0);
                        int tmp = sizeof(int) * 2;
                        datafile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
                        tmp = 0;
                        for (int i = 1; i < 2; ++i)
                            datafile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
                        //datafile.close();

                        //nodefile.open(file_name + "node", std::ios::out);
                        int ntmp = sizeof(int) * 4;
                        nodefile.write(reinterpret_cast<char *>(&ntmp), sizeof(int));
                        ntmp = 0;
                        for (int i = 1; i < 4; ++i)
                            nodefile.write(reinterpret_cast<char *>(&ntmp), sizeof(int));
                        //nodefile.close();
                        return;
                    }
                    if (now.size < (L + 1) >> 1) {
                        // key of node is not enough
                        node next_node, prev_node;
                        if (ind_fa < fa.size) nread(next_node, fa.son[ind_fa+1]);
                        if (ind_fa > 0) nread(prev_node, fa.son[ind_fa-1]);
                        if (ind_fa < fa.size && next_node.size > (L + 1) >> 1) {
                            // borrow from right neighbour
                            for (int i=ser.second;i<now.size;i++) { // size has decreased
                                now.key[i] = now.key[i+1];
                                now.son[i] = now.son[i+1];
                            }
                            now.key[now.size] = next_node.key[0];
                            now.son[now.size++] = next_node.son[0];
                            next_node.size--;
                            for (int i=0;i<next_node.size;i++) {
                                next_node.key[i] = next_node.key[i+1];
                                next_node.son[i] = next_node.son[i+1];
                            }
                            fa.key[ind_fa] = next_node.key[0];
                            nupdate(now,fa.son[ind_fa]);
                            nupdate(next_node,fa.son[ind_fa+1]);
                        }
                        else if (ind_fa > 0 && prev_node.size > (L + 1) / 2) {
                            // borrow from left neighbour
                            for (int i=ser.second;i>0;i--) {
                                now.key[i] = now.key[i-1];
                                now.son[i] = now.son[i-1];
                            }
                            now.key[0] = prev_node.key[--prev_node.size];
                            now.son[0] = prev_node.son[prev_node.size];
                            now.size++;
                            fa.key[ind_fa-1] = now.key[0];
                            nupdate(now,fa.son[ind_fa]);
                            nupdate(prev_node,fa.son[ind_fa-1]);
                        }
                        else if (ind_fa < fa.size) {
                            // merge with right neighbour
                            for (int i=ser.second;i<now.size;i++) {
                                now.key[i] = now.key[i+1];
                                now.son[i] = now.son[i+1];
                            }
                            for (int i=0;i<next_node.size;i++) {
                                now.key[now.size] = next_node.key[i];
                                now.son[now.size++] = next_node.son[i];
                            }
                            nDelete(fa.son[ind_fa+1]);
                            fa.size--;
                            fa.key[ind_fa] = fa.key[ind_fa+1];
                            // key and son differ in index for non-leaf node
                            for (int i=ind_fa+1;i<fa.size;i++) {
                                fa.key[i] = fa.key[i+1];
                                fa.son[i] = fa.son[i+1];
                            }
                            if (fa.size != 0 && fa.size >= ind_fa) fa.son[fa.size] = fa.son[fa.size + 1];
                            nupdate(now,fa.son[ind_fa]);
                        }
                        else {
                            // merge with left neighbour
                            for (int i=0;i<ser.second;i++) {
                                prev_node.key[i + prev_node.size] = now.key[i];
                                prev_node.son[i + prev_node.size] = now.son[i];
                            } // skip deleted key
                            for (int i=ser.second;i<now.size;i++) {
                                prev_node.key[prev_node.size + i] = now.key[i+1];
                                prev_node.son[prev_node.size + i] = now.son[i+1];
                            }
                            prev_node.size += now.size;
                            nDelete(fa.son[ind_fa]);
                            fa.size--;
                            fa.key[ind_fa-1] = fa.key[ind_fa];
                            // key and son differ in index for non-leaf node
                            for (int i=ind_fa;i<fa.size;i++) {
                                fa.key[i] = fa.key[i+1];
                                fa.son[i] = fa.son[i+1];
                            }
                            if (fa.size != 0 && fa.size >= ind_fa) fa.son[fa.size] = fa.son[fa.size + 1]; // ???
                            nupdate(prev_node,fa.son[ind_fa-1]);
                        }
                        nupdate(fa,idx); // ???
                        return;
                    }
                    for (int i=ser.second;i<now.size;i++) {
                        now.son[i] = now.son[i+1];
                        now.key[i] = now.key[i+1];
                    }
                    if (ind_fa > 0) fa.key[ind_fa-1] = now.key[0];
                    nupdate(now,fa.son[ind_fa]);
                    nupdate(fa, idx);
                    return;
                }
                else { // son[i] -> next vector
                    now.son[ser.second] = data.next;
                    nupdate(now,fa.son[ind_fa]);
                    return;
                }
            }
            else {
                // middle vector is deleted
                data_vector pre_data;
                read(pre_data,prev);
                pre_data.next = data.next;
                update(pre_data,prev);
                return;
            }
        }
        else update(data,pos);
    }

    // recursively delete and push up
    void remove(node &fa, const Key& key, const T& val, int idx, node &fa_fa, int idx_fa_fa) {
        node now;
        int idx_fa = fa.upper_bound(key);
        nread(now, fa.son[idx_fa]);
        if (now.is_leaf) {
            remove_from_leaf(fa,key,val,idx,fa_fa,idx_fa_fa);
            return;
        }
        else remove(now,key,val,fa.son[idx_fa],fa,idx_fa);
        node prev_node, next_node;
        // push up to root
        if (now.size < (M + 1) / 2 - 1) {
            if (idx_fa < fa.size) nread(next_node, fa.son[idx_fa+1]);
            if (idx_fa > 0) nread(prev_node, fa.son[idx_fa-1]);
            if (idx_fa < fa.size && next_node.size > (M + 1) / 2 - 1) {
                node temp;
                nread(temp, next_node.son[0]);
                while (!temp.is_leaf) {
                    nread(temp,temp.son[0]);
                }
                now.key[now.size] = temp.key[0];
                now.son[now.size+1] = next_node.son[0];
                now.size++;
                next_node.size--;
                fa.key[idx_fa] = next_node.key[0];
                for (int i=0; i<next_node.size;i++) {
                    next_node.key[i] = next_node.key[i + 1];
                    next_node.son[i] = next_node.son[i + 1];
                }
                next_node.son[next_node.size] = next_node.son[next_node.size + 1];
                nupdate(next_node, fa.son[idx_fa + 1]);
                nupdate(now, fa.son[idx_fa]);
            }
            else if (idx_fa > 0 && prev_node.size > (M + 1) / 2 - 1) {
                node temp;
                nread(temp, now.son[0]);
                while (!temp.is_leaf) {
                    nread(temp,temp.son[0]);
                }
                now.son[now.size + 1] = now.son[now.size];
                for (int i=now.size;i>0;i--) {
                    now.key[i] = now.key[i - 1];
                    now.son[i] = now.son[i - 1];
                }
                now.size++;
                now.key[0] = temp.key[0];
                now.son[0] = prev_node.son[prev_node.size];
                fa.key[idx_fa - 1] = prev_node.key[prev_node.size-1];
                prev_node.size--;
                nupdate(prev_node, fa.son[idx_fa - 1]);
                nupdate(now, fa.son[idx_fa]);
            } else if (idx_fa < fa.size) {
                node temp;
                nread(temp, next_node.son[0]);
                while (!temp.is_leaf) {
                    nread(temp,temp.son[0]);
                }
                now.key[now.size++] = temp.key[0];
                for (int i=0;i<next_node.size;i++) {
                    now.key[now.size + i] = next_node.key[i];
                    now.son[now.size + i] = next_node.son[i];
                }
                now.size += next_node.size;
                now.son[now.size] = next_node.son[next_node.size];
                nDelete(fa.son[idx_fa + 1]);
                fa.size--;
                fa.key[idx_fa] = fa.key[idx_fa + 1];
                for (int i=idx_fa+1;i<fa.size; i++) {
                    fa.key[i] = fa.key[i + 1];
                    fa.son[i] = fa.son[i + 1];
                }
                if (fa.size != 0 && fa.size >= idx_fa) fa.son[fa.size] = fa.son[fa.size + 1];
                nupdate(now,fa.son[idx_fa]);
            } else {
                node temp;
                nread(temp, now.son[0]);
                while (!temp.is_leaf) {
                    nread(temp,temp.son[0]);
                }
                prev_node.key[prev_node.size++] = temp.key[0];
                for (int i=0;i<now.size;i++) {
                    prev_node.key[prev_node.size + i] = now.key[i];
                    prev_node.son[prev_node.size + i] = now.son[i];
                }
                prev_node.size += now.size;
                prev_node.son[prev_node.size] = now.son[now.size];
                nDelete(fa.son[idx_fa]);
                fa.size--;
                fa.key[idx_fa - 1] = fa.key[idx_fa];
                for (int i=idx_fa;i<fa.size;i++) {
                    fa.key[i] = fa.key[i + 1];
                    fa.son[i] = fa.son[i + 1];
                }
                if (fa.size != 0 && fa.size >= idx_fa) fa.son[fa.size] = fa.son[fa.size + 1];
                nupdate(prev_node, fa.son[idx_fa - 1]);
            }
            nupdate(fa,idx);
            return;
        }
        nupdate(now,fa.son[idx_fa]);
    }
};

#endif //BPT_BPT_HPP




















#include <iostream>
#include <cstdio>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
struct String {
    char index[65];

    String(const String &other) {
        for (int i = 0; i < 65; i++)index[i] = other.index[i];
    }

    String() = default;

    friend bool operator>(const String &lhs, const String &rhs) {
        return std::string(lhs.index) > std::string(rhs.index);
    }

    friend bool operator>=(const String &lhs, const String &rhs) {
        return std::string(lhs.index) >= std::string(rhs.index);
    }

    friend bool operator<(const String &lhs, const String &rhs) {
        return std::string(lhs.index) < std::string(rhs.index);
    }

    friend bool operator<=(const String &lhs, const String &rhs) {
        return std::string(lhs.index) <= std::string(rhs.index);
    }

    friend bool operator==(const String &lhs, const String &rhs) {
        return std::string(lhs.index) == std::string(rhs.index);
    }

    friend bool operator!=(const String &lhs, const String &rhs) {
        return std::string(lhs.index) != std::string(rhs.index);
    }

    friend std::ostream &operator<<(std::ostream &os, const String &obj) {
        os << obj.index;
        return os;
    }
};
int main() {
    // freopen("5.in","r",stdin);
    // freopen("me.out","w",stdout);
//    if (remove("testdata") != 0){
//        cout<<"failed"<<endl;
//    }
//    else cout<<"success"<<endl;
//    if (remove("testnode") != 0){
//        cout<<"failed"<<endl;
//    }
//    else cout<<"success"<<endl;
//    if (remove("test_val") != 0){
//        cout<<"failed"<<endl;
//    }
//    else cout<<"success"<<endl;
//    if (remove("test_node") != 0){
//        cout<<"failed"<<endl;
//    }
//    else cout<<"success"<<endl;
    BPTree<String, int> bpTree("test");
    String key;
    int val;
    int cnt;
    char cmd[10];
    scanf("%d", &cnt);
    for (int i = 1; i <= cnt; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'i') {
            scanf("%s%d", key.index, &val);
            bpTree.insert(key,val);
        } else if (cmd[0] == 'f') {
            scanf("%s", key.index);
            sjtu::vector<int> ans = bpTree.find(key);
            if (!ans.empty()) {
                int size = ans.size();
                for (int j = 0; j < size - 1; j++)printf("%d ", ans[j]);
                printf("%d\n",ans[size - 1]);
            } else puts("null");
        } else if (cmd[0] == 'd') {
            scanf("%s%d", key.index, &val);
            bpTree.remove(key,val);
        }

    }
    return 0;
}