#include <iostream>
#include <cstring>
#include <string>

#include <climits>
#include <cstddef>
#include <memory>
#include <fstream>

//#include "b_plus_tree.hpp"


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

    template<class T>
    T *upper_bound(T *first, T *last, T key) {
        if (first == last)
            return first;
        last--;
        if (key >= *last)
            return last + 1;
        while (first < last) {
            T *mid = first + (last - first) / 2;
            if (key < *mid) {
                last = mid;
            } else {
                first = mid + 1;
            }
        }
        return first;
    }

    template<class T>
    T *lower_bound(T *first, T *last, T key) {
        if (first == last)return first;
        last--;
        if (key > *last)return last + 1;
        while (first < last) {
            T *mid = first + (last - first) / 2;
            if (*mid < key) {
                first = mid + 1;
            } else {
                last = mid;
            }
        }
        return first;
    }

    template<class T1, class T2>
    class pair {
    public:
        T1 first;
        T2 second;

        constexpr pair() : first(), second() {}

        pair(const pair &other) = default;

        pair(pair &&other) = default;

        pair(const T1 &x, const T2 &y) : first(x), second(y) {}

        template<class U1, class U2>
        pair(U1 &&x, U2 &&y) : first(x), second(y) {}

        template<class U1, class U2>
        pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}

        template<class U1, class U2>
        pair(pair<U1, U2> &&other) : first(other.first), second(other.second) {}
    };

    template<typename T>
    class vector {
    public:

        class const_iterator;

        class iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

        private:
            T *iter;
            T *head;
        public:
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */

            iterator(T *p, T *head) {
                this->head = head;
                iter = p;
            }

            explicit iterator(T *p) {
                this->head = p;
                iter = p;
            }

            const int position() const {
                int ret = iter - head;
                return ret;
            }

            iterator operator+(const int &n) const {
                iterator ret(iter + n, head);
                return ret;
                //TODO
            }

            iterator operator-(const int &n) const {
                iterator ret(iter - n, head);
                return ret;
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (head != rhs.head)
                    throw invalid_iterator();
                int ret = iter - rhs.iter;
                return ret;
                //TODO
            }

            iterator &operator+=(const int &n) {
                iter += n;
                return *this;
                //TODO
            }

            iterator &operator-=(const int &n) {
                iter -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator ret = *this;
                iter++;
                return ret;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                iter++;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator ret = *this;
                iter--;
                return ret;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                iter--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                return *iter;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else return false;

            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else return false;
            }
        };

        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

        private:
            /*TODO*/
            const T *iter;
            const T *head;
        public:
            const_iterator(T *p, T *head) {
                iter = p;
                this->head = head;
            }

            const_iterator(T *p) {
                iter = p;
                head = p;
            }

            const int position() const {
                int ret = iter - head;
                return ret;
            }

            const_iterator operator+(const int &n) const {
                const_iterator ret(iter + n, head);
                return ret;
            }

            const_iterator operator-(const int &n) const {
                const_iterator ret(iter - n, head);
                return ret;
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                if (head != rhs.head)
                    throw invalid_iterator();
                int ret = iter - rhs.iter;
                return ret;
            }

            const_iterator &operator+=(const int &n) {
                iter += n;
                return *this;
            }

            const_iterator &operator-=(const int &n) {
                iter -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                iterator ret = *this;
                iter++;
                return ret;
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                iter++;
                return *this;
            }

            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                iterator ret = *this;
                iter--;
                return ret;
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                iter--;
                return *this;
            }

            /**
             * TODO *it
             */
            T operator*() const {
                const T ret = *iter;
                return ret;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else return false;

            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else return false;
            }

        };

        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */

    private:
        long long curLength, maxSize;
        T *data;
        std::allocator<T> memAlloc;

    public:

        vector() {
            curLength = 0;
            maxSize = 2;
            data = memAlloc.allocate(2);
        }

        vector(const vector &other) {

            maxSize = other.maxSize;
            curLength = other.curLength;
            data = memAlloc.allocate(maxSize);
            for (int i = 0; i < curLength; i++) {
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + i, other.data[i]);
            }

        }

        /**
         * TODO Destructor
         */
        ~vector() {
            for (int i = 0; i < curLength; i++)
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + i);
            memAlloc.deallocate(data, maxSize);
        }


        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (this == &other)
                return *this;
            for (int i = 0; i < curLength; i++)
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + i);
            memAlloc.deallocate(data, maxSize);

            curLength = other.curLength;
            maxSize = other.maxSize;

            data = memAlloc.allocate(maxSize);

            for (int i = 0; i < curLength; i++)
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + i, other.data[i]);


            return *this;
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T &at(const size_t &pos) {
            if (pos < 0 || pos >= curLength)
                throw index_out_of_bound();
            else
                return data[pos];
        }

        const T &at(const size_t &pos) const {
            if (pos < 0 || pos >= curLength)
                throw index_out_of_bound();
            else
                return data[pos];
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T &operator[](const size_t &pos) {
            if (pos >= curLength || pos < 0)
                throw index_out_of_bound();
            else
                return data[pos];
        }

        const T &operator[](const size_t &pos) const {
            if (pos >= curLength || pos < 0)
                throw index_out_of_bound();
            else
                return data[pos];

        }

        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T &front() const {
            if (curLength == 0)
                throw container_is_empty();
            return data[0];
        }

        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T &back() const {
            if (curLength == 0)
                throw container_is_empty();
            return data[curLength - 1];

        }

        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator ret(data, data);
            return ret;
        }

        const_iterator cbegin() const {
            const_iterator ret(data, data);
            return ret;
        }

        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator ret(data + curLength, data);
            return ret;
        }

        const_iterator cend() const {
            const_iterator ret(data + curLength, data);
            return ret;

        }

        /**
         * checks whether the container is empty
         */
        bool empty() const {
            if (curLength == 0)
                return true;
            else return false;
        }

        /**
         * returns the number of elements
         */
        size_t size() const {
            return curLength;
        }

        /**
         * clears the contents
         */
        void clear() {
            for (int i = 0; i < curLength; i++)
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + i);
            curLength = 0;
            return;
        }

        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        void doubleSpace() {
            T *tempData;
            tempData = memAlloc.allocate(maxSize * 2);
            for (int i = 0; i < curLength; i++) {
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, tempData + i, data[i]);
            }
            for (int i = 0; i < curLength; i++) {
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + i);
            }

            memAlloc.deallocate(data, maxSize); // Deallocate previous memory
            maxSize *= 2;
            data = tempData;
        }

        iterator insert(iterator pos, const T &value) {
            if (curLength == maxSize)
                doubleSpace();

            int ind = pos.position();
            curLength++;
            if (ind == curLength - 1) {
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + curLength - 1, value);
                return pos;
            } else {
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + curLength - 1,
                                                                     data[curLength - 2]);
                for (int i = curLength - 1; i > ind; i--)   // multiple assignment?
                    data[i] = data[i - 1];
                data[ind] = value;
                return pos;
            }
        }

        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if (curLength == maxSize)
                doubleSpace();
            curLength++;
            if (ind == curLength - 1) {
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + curLength - 1, value);
                iterator ret(data + ind, data);
                return ret;
            } else {
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + curLength - 1,
                                                                     data[curLength - 2]);
                for (int i = curLength - 1; i > ind; i--)
                    data[i] = data[i - 1];
                iterator ret(data + ind, data);
                return ret;
            }
        }

        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            int ind = pos.position();
            curLength--;
            for (int i = ind; i <= curLength - 1; i++)
                data[i] = data[i + 1];
            std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + curLength);
            return pos;

        }

        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if (ind >= curLength)
                throw index_out_of_bound();
            curLength--;
            for (int i = ind; i <= curLength - 1; i++)
                data[i] = data[i + 1];

            std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + curLength);
            iterator ret(data + ind, data);
            return ret;

        }

        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (curLength == maxSize) {
                doubleSpace();
            }
            curLength++;
            std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + curLength - 1, value);
        }

        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if (curLength == 0)
                throw container_is_empty();
            curLength--;
            std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + curLength);
        }
    };


}

#


template<class T>
class Database {
//    static const int blockSize = 120, keySize = 65;
#define blockSize 120
#define keySize 65

    friend class Memory;

public:
    class Data {
    public:
        char key[keySize];
        T value;

        Data() {};

        Data(char *src, const T val) {
            strcpy(key, src);
            value = val;

        }

        bool operator<(const Data &obj) {
            if (strcmp(key, obj.key) < 0)
                return true;
            if (strcmp(key, obj.key) == 0 && value < obj.value)
                return true;
            return false;
        }

        bool operator>(const Data &obj) {
            if (strcmp(key, obj.key) > 0)
                return true;
            if (strcmp(key, obj.key) == 0 && value > obj.value)
                return true;
            return false;
        }

        bool operator<=(const Data &obj) {
            if (strcmp(key, obj.key) < 0)
                return true;
            if (strcmp(key, obj.key) == 0 && value <= obj.value)
                return true;
            return false;
        }

        bool operator>=(const Data &obj) {
            if (strcmp(key, obj.key) > 0 || (strcmp(key, obj.key) == 0 && value >= obj.value))
                return true;

            return false;
        }

        friend bool operator==(const Data &lhs, const Data &rhs) {

            if (strcmp(lhs.key, rhs.key) == 0 && lhs.value == rhs.value)
                return true;
            return false;
        }

        friend bool operator!=(const Data &lhs, const Data &rhs) {
            return !(lhs == rhs);
        }

        Data &operator=(const Data &obj) {
            if (&obj == this)
                return *this;

            strcpy(key, obj.key);
            value = obj.value;

            return *this;
        }
    };

    class Index {
    public:
        int rootAddr, totBlocks;


        Index(int pos = 1, int num = 1) {
            rootAddr = pos;
            totBlocks = num;
        }
    };

    enum nodeType {
        internal, leaf
    };

    class Node {
    public:
        nodeType type;
        int parentAddr;
        int size;
        int edge[blockSize + 1];
        Data value[blockSize];
        int nextLeaf, prevLeaf;
        // nextLeaf -> front_pos
        // prevLeaf -> back_pos;

        Node() {
            type = leaf;
            size = 0;
            parentAddr = 0;
            prevLeaf = 0;
            nextLeaf = 0;
        }
    };


    Index head;

    friend class Memory;


    struct Memory {
        friend class Database;

        friend class tes;

    public:
        void refresh(int addr, const Data &obj) {  // freshleft  //fill the empty place in the internal node
            if (addr == 0)
                return;
            Node cur;
            readNode(cur, addr);
            int idx = sjtu::upper_bound(cur.value, cur.value + cur.size, obj) - cur.value;
            if (idx != 0) {
                cur.value[idx - 1] = obj;
                writeNode(cur, addr);
            } else {
                refresh(cur.parentAddr, obj);
            }
        }

        int findKey(char *key, int addr) {
            Node obj;
            readNode(obj, addr);
            if (obj.type == leaf) {
                return addr;
            } else {
                int nxt = sjtu::upper_bound(obj.value, obj.value + obj.size, Data(key, T())) - obj.value;
                return findKey(key, obj.edge[nxt]);
            }
        }

        void moveCursor(Node &cur, int &idx, char *key) {
            while (true) {
                if (idx == -1) {
                    if (cur.prevLeaf == 0) {   // move the cursor to the first value with Key
                        idx++;
                        break;
                    }
                    readNode(cur, cur.prevLeaf);
                    idx = cur.size - 1;
                    if (strcmp(cur.value[idx].key, key) != 0) {
                        readNode(cur, cur.nextLeaf);
                        idx = 0;
                        break;
                    }
                }
                if (strcmp(cur.value[idx].key, key) != 0) {
                    idx++;
                    break;
                }
                idx--;
            }
        }


        sjtu::pair<sjtu::vector<T>, char *> Scan(Node &cur, char *key, int idx) {
            sjtu::vector<int> ans;
            while (true) {
                if (idx == cur.size) {
                    if (cur.nextLeaf != 0) {
                        readNode(cur, cur.nextLeaf);
                        idx = 0;
                    } else break;
                }
                if (strcmp(cur.value[idx].key, key) != 0)
                    break;
                else
                    ans.push_back(cur.value[idx].value);
                idx++;
            }

            sjtu::pair<sjtu::vector<T>, char *> ret(ans, key);
            return ret;
        }

        std::fstream op;

        void updateParent(const int addr, const int f_addr) {
            Node obj;
            readNode(obj, addr);
            obj.parentAddr = f_addr;
            writeNode(obj, addr);
        }

        void readIndex(Index &st) {
            op.seekg(0);
            op.read(reinterpret_cast<char *>(&st), sizeof(st));
        }

        void writeIndex(Index &st) {
            op.seekp(0);
            op.write(reinterpret_cast<char *>(&st), sizeof(st));
        }

        void readNode(Node &obj, int addr) {
            int pos = sizeof(Index) + (addr - 1) * (sizeof(Node));
            int sizeT = sizeof(obj);
            op.seekg(pos);
            op.read(reinterpret_cast<char *>(&obj), sizeT);
        }

        void writeNode(Node &obj, int addr) {
            int pos = sizeof(Index) + (addr - 1) * (sizeof(Node));
            int sizeT = sizeof(obj);
            op.seekp(pos);
            op.write(reinterpret_cast<char *>(&obj), sizeT);
        }

        void openFile(std::string name) {
            op.open(name);
        }

        void closeFile() {
            op.close();
        }

        void createFile(std::string name) {
            std::ofstream output(name);
            output.seekp(0);
            Index st;
            output.write(reinterpret_cast<char *>(&st), sizeof(Index));
            output.seekp(sizeof(Index));
            Node first;
            output.write(reinterpret_cast<char *>(&first), sizeof(Node));
        }
    };

    Memory memo;

    Database() {};


    explicit Database(std::string name) {
        std::ifstream input;
        input.open(name);

        if (!input) {
            memo.createFile(name);
        }
        memo.openFile(name);
        memo.readIndex(head);
    }

    ~Database() {
        memo.writeIndex(head);
        memo.closeFile();
    }

    void updatePrev(int addr, int prev) {   // update the node on the left side
        if (addr == 0)
            return;
        Node cur;
        memo.readNode(cur, addr);
        cur.prevLeaf = prev;
        memo.writeNode(cur, addr);
    }


    int findObj(const Data &obj, int addr) {
        Node cur;
        memo.readNode(cur, addr);
        if (cur.type == leaf) {
            return addr;
        } else {
            int next = sjtu::upper_bound(cur.value, cur.value + cur.size, obj) - cur.value;
            int ptr = cur.edge[next];
            return findObj(obj, ptr);
        }
    }


    bool judge(int pos, int f_pos, Node &obj) {  // check if this node belongs to the given father
        int addr = pos;
        int f_addr = f_pos;
        if (addr == 0)
            return true;
        memo.readNode(obj, addr);
        if (obj.parentAddr == f_addr)  // modified
            return false;
        else
            return true;
    }


    void mergeNode(int addr, Node &obj1, Node &obj2, Node &fa, int ind) {
        obj1.value[obj1.size] = fa.value[ind];
        obj1.size++;
        for (int i = 0; i < obj2.size; i++) {
            obj1.value[obj1.size + i] = obj2.value[i];
            obj1.edge[obj1.size + i] = obj2.edge[i];
            Node temp;
            memo.updateParent(obj2.edge[i], addr);
        }
        obj1.size += obj2.size;
        obj1.edge[obj1.size] = obj2.edge[obj2.size];
        memo.updateParent(obj2.edge[obj2.size], addr);
    }


    sjtu::pair<sjtu::vector<T>, char *> find(char *key) {
        int addr = memo.findKey(key, head.rootAddr);
        // find the leafNode corresponding to the given key;
        Node cur;
        memo.readNode(cur, addr);
        int idx = sjtu::lower_bound(cur.value, cur.value + cur.size, Data(key, T())) - cur.value;
        if (idx == cur.size)
            --idx;
        memo.moveCursor(cur, idx, key);
        return memo.Scan(cur, key, idx);
    }

    bool outputFind(char *key){
        sjtu::vector<int> ans = find(key).first;
        if(ans.empty())
            return false;

        for(int i=0;i<ans.size();i++)
            std::cout<<ans[i]<<" ";
        std::cout<<std::endl;

        return true;
    }

    bool insertObj(Node &curNode, const int pos, const int idx, const int Caddr, const Data &obj) {
        int addr = pos;
        int child_addr = Caddr;


        for (int i = curNode.size; i > idx; i--) {
            int te = curNode.edge[i];
            curNode.edge[i + 1] = te;

            Data tmp = curNode.value[i - 1];
            curNode.value[i] = tmp;

        }

        curNode.value[idx] = obj;
        curNode.edge[idx + 1] = child_addr;
        curNode.size++;
        memo.writeNode(curNode, addr);

        return false;
    }

    bool generateNewRightNode(Node &curNode, Node &New) {
        int mid = blockSize / 2;
        int newSize = mid - 1;
        int tmp = mid + 1;
        for (int i = tmp; i < blockSize; i++) {
            New.value[i - tmp] = curNode.value[i];
            New.edge[i - tmp] = curNode.edge[i];
            memo.updateParent(curNode.edge[i], head.totBlocks + 1);
        }
        New.edge[newSize] = curNode.edge[blockSize];

        int f_addr = head.totBlocks + 1;
        memo.updateParent(curNode.edge[blockSize], f_addr);
        curNode.size = mid;
        New.type = internal;

        return false;
    }

    bool generateNewParent(Node &curNode, Node &New, const int addr) {
        int mid = blockSize / 2;

        New.parentAddr = curNode.parentAddr;
        int x = head.totBlocks + 1;

        memo.writeNode(curNode, addr);
        memo.writeNode(New, x);

        head.totBlocks = x;

        Data o = curNode.value[mid];
        splitInternal(curNode.parentAddr, head.totBlocks, o);

        return false;
    }

    bool generateNewRoot(Node &curNode, Node &New, const int addr) {

        const int mid = blockSize / 2;
        int newRootAddr = head.totBlocks + 2;
        curNode.parentAddr = newRootAddr;
        New.parentAddr = newRootAddr;
        memo.writeNode(curNode, addr);

        int NewAddr = head.totBlocks + 1;
        head.totBlocks++;
        memo.writeNode(New, NewAddr);


        Node newRoot;

        assignRoot(newRoot, curNode.value[mid], addr, head.totBlocks);
        int x = head.totBlocks + 1;
        head.totBlocks++;
        memo.writeNode(newRoot, x);

        head.rootAddr = x;

        return false;
    }

    void splitInternal(int addr, int child_addr, const Data &obj) {
        Node curNode;
        memo.readNode(curNode, addr);
        int idx = sjtu::upper_bound(curNode.value, curNode.value + curNode.size, obj) - curNode.value;

        bool res = insertObj(curNode, addr, idx, child_addr, obj);


        if (curNode.size == blockSize) {
            Node New; //new Node generated by splitting
            int mid = blockSize / 2;
            New.size = mid - 1;

            generateNewRightNode(curNode, New);

            if (curNode.parentAddr != 0) {
                if (generateNewParent(curNode, New, addr))
                    return;
            } else {
                if (generateNewRoot(curNode, New, addr))
                    return;
            }
        }
    }

    bool assignRoot(Node &cur, const Data obj, const int edge0, const int edge1) {
        cur.type = internal;
        cur.size = 1;
        cur.edge[0] = edge0;
        cur.edge[1] = edge1;
        cur.value[0] = obj;

        return true;
    }


    void generateNew(Node &New, Node &Old, int addr) {
        int newRootPos = head.totBlocks + 2;
        Old.parentAddr = newRootPos;
        New.parentAddr = newRootPos;

        int NewPos = head.totBlocks + 1;
        head.totBlocks++;
        memo.writeNode(Old, addr);
        memo.writeNode(New, NewPos);

        Node newRoot;

        assignRoot(newRoot, New.value[0], addr, head.totBlocks);

        head.totBlocks++;
        memo.writeNode(newRoot, head.totBlocks);
        head.rootAddr = head.totBlocks;
    }

    void splitLeaf(int addr) {
        Node Old;
        memo.readNode(Old, addr);

        Node New;
        New.prevLeaf = addr;
        New.nextLeaf = Old.nextLeaf;

        int tmpNewAddr = head.totBlocks + 1;
        updatePrev(Old.nextLeaf, tmpNewAddr);
        Old.nextLeaf = tmpNewAddr;

        int newSize = blockSize / 2;
        for (int i = 0; i < newSize; i++)
            New.value[i] = Old.value[newSize + i];

        New.size = newSize;
        Old.size = newSize;

        if (Old.parentAddr != 0) {
            int tmp = Old.parentAddr;
            New.parentAddr = tmp;
            memo.writeNode(Old, addr);
            head.totBlocks = tmpNewAddr;

            int pos = head.totBlocks;
            memo.writeNode(New, pos);
            Data pivot = New.value[0];

            splitInternal(Old.parentAddr, head.totBlocks, pivot);
        } else {
            generateNew(New, Old, addr);
        }
    }

    bool insert(const int addr, const Data obj) {
        Node cur;
        memo.readNode(cur, addr);

        int idx = sjtu::upper_bound(cur.value, cur.value + cur.size, obj) - cur.value;

        for (int i = cur.size; i > idx; i--)
            cur.value[i] = cur.value[i - 1];
        cur.value[idx] = obj;
        cur.size++;

        memo.writeNode(cur, addr);

        if (cur.size >= blockSize)
            splitLeaf(addr);

        return true;
    }


    bool insert(char *index, T val) {
        Data obj(index, val);
        int addr = findObj(obj, head.rootAddr);
        insert(addr, obj);

        return true;
    }


    void insertValue(Node &cur, int idx, const Data obj, const int edg) {
        for (int i = cur.size; i > idx; i--)
            cur.value[i] = cur.value[i - 1];
        for (int i = cur.size + 1; i > idx; i--)
            cur.edge[i] = cur.edge[i - 1];
        cur.edge[idx] = edg;
        cur.value[idx] = obj;
        cur.size++;
    }

    void borrowFromLeft(const int idx, const int pos) {
        int ind = idx;
        int addr = pos;
        Node cur;
        memo.readNode(cur, addr);
        Node fa;
        memo.readNode(fa, cur.parentAddr);

        Node leftSib;
        memo.readNode(leftSib, fa.edge[ind - 1]);

        int thres = blockSize / 2;
        if (leftSib.size >= thres) {

            insertValue(cur, 0, fa.value[fa.size - 1], leftSib.edge[leftSib.size]);
            memo.updateParent(cur.edge[0], addr);

            leftSib.size--;

            Data tmp = leftSib.value[leftSib.size];
            fa.value[ind - 1] = tmp;

            memo.writeNode(cur, addr);
            memo.writeNode(leftSib, fa.edge[ind - 1]);
            memo.writeNode(fa, cur.parentAddr);

        } else {
            mergeNode(fa.edge[ind - 1], leftSib, cur, fa, ind - 1);
            memo.writeNode(leftSib, fa.edge[ind - 1]);
            adjustInternal(cur.parentAddr, fa.value[ind - 1]);
        }
    }

    void borrowFromRight(const int idx, const int pos) {
        int ind = idx;
        int addr = pos;
        Node cur;
        memo.readNode(cur, addr);
        Node fa;
        memo.readNode(fa, cur.parentAddr);

        Node rightSib;
        memo.readNode(rightSib, fa.edge[ind + 1]);
        int thres = blockSize / 2;
        if (rightSib.size >= thres) {
            int tmp = thres - 1;
            cur.edge[tmp] = rightSib.edge[0];

            int pivot = rightSib.edge[0];
            memo.updateParent(pivot, addr);

            cur.value[tmp - 1] = fa.value[ind];
            fa.value[ind] = rightSib.value[0];

            removeValue(rightSib, 0, 0);
            cur.size++;

            memo.writeNode(cur, addr);
            memo.writeNode(rightSib, fa.edge[ind + 1]);
            memo.writeNode(fa, cur.parentAddr);
        } else {
            mergeNode(addr, cur, rightSib, fa, ind);
            memo.writeNode(cur, addr);
            adjustInternal(cur.parentAddr, fa.value[ind]);
        }
    }

    void removeValue(Node &cur, const int idx1, const int idx2) {

        for (int i = idx1; i < cur.size - 1; i++)
            cur.value[i] = cur.value[i + 1];
        for (int i = idx2; i < cur.size; i++)
            cur.edge[i] = cur.edge[i + 1];
        cur.size--;

    }

    void adjustInternal(int addr, Data abandon) {
        Node cur;
        memo.readNode(cur, addr);

        if (addr == head.rootAddr && cur.size == 1) {
            Node child;
            memo.readNode(child, cur.edge[0]);
            child.parentAddr = 0;
            head.rootAddr = cur.edge[0];
            memo.writeNode(child, cur.edge[0]);
            return;
        }

        int idx = sjtu::upper_bound(cur.value, cur.value + cur.size, abandon) - cur.value;
        removeValue(cur, idx - 1, idx);

        if (addr == head.rootAddr) {
            memo.writeNode(cur, addr);
            return;
        }


        //borrow from siblings
        memo.writeNode(cur, addr);
        if (cur.size < blockSize / 2 - 1) {
            Node fa;
            memo.readNode(fa, cur.parentAddr);
            int ind = sjtu::upper_bound(fa.value, fa.value + fa.size, cur.value[0]) - fa.value;

            if (ind == fa.size) {
                borrowFromLeft(ind, addr);
            } else {
                borrowFromRight(ind, addr);
            }
        } else memo.writeNode(cur, addr);
    }

    void saveData(Node &cur, Node &sib, Node &fa, const int addr, const int sibAddr, const int f_addr) {
        memo.writeNode(cur, addr);
        memo.writeNode(sib, sibAddr);
        memo.writeNode(fa, f_addr);
    }

    bool mergeFromRight(Node &cur, Node &nextLeaf, const int addr) {
        int thres = blockSize / 2 - 1;
        cur.value[thres - 1] = nextLeaf.value[0];

        int t = nextLeaf.size - 1;
        for (int i = 0; i < t; i++) {
            nextLeaf.value[i] = nextLeaf.value[i + 1];
        }
        nextLeaf.size = t;
        cur.size++;
        Node fa;

        memo.readNode(fa, cur.parentAddr);
        int idx = sjtu::upper_bound(fa.value, fa.value + fa.size, cur.value[thres - 1]) - fa.value;

        Data tmp = nextLeaf.value[0];
        fa.value[idx - 1] = nextLeaf.value[0];
        saveData(cur, nextLeaf, fa, addr, cur.nextLeaf, cur.parentAddr);

        return true;
    }

    bool mergeRight(Node &cur, Node &nextLeaf, const int addr) {
        int tmp = blockSize / 2 - 2;
        int thres = blockSize - 3;
        for (int i = tmp; i < thres; i++)
            cur.value[i] = nextLeaf.value[i - tmp];
        cur.nextLeaf = nextLeaf.nextLeaf;

        updatePrev(cur.nextLeaf, addr);
        cur.size = thres;
        memo.writeNode(cur, addr);

        Data abandon = nextLeaf.value[0];
        adjustInternal(cur.parentAddr, abandon);

        return true;
    }

    bool mergeFromLeft(Node &cur, Node &prevLeaf, const int addr) {
        for (int i = cur.size; i > 0; i--)  //leave a empty space for the new value to settle in
            cur.value[i] = cur.value[i - 1];

        Data newVal = prevLeaf.value[prevLeaf.size - 1];
        cur.value[0] = newVal;
        prevLeaf.size--;
        cur.size++;

        Node fa;
        memo.readNode(fa, cur.parentAddr);
        int idx = sjtu::upper_bound(fa.value, fa.value + fa.size, newVal) - fa.value;

        Data tmp = newVal;
        fa.value[idx] = tmp;


        saveData(cur, prevLeaf, fa, addr, cur.prevLeaf, cur.parentAddr);
        return true;
    }

    bool mergeLeft(Node &cur, Node &prevLeaf, const int addr) {
        const int thres = blockSize - 3;
        const int low = blockSize / 2 - 1;
        for (int i = low; i < thres; i++)
            prevLeaf.value[i] = cur.value[i - low];
        prevLeaf.nextLeaf = cur.nextLeaf;

        updatePrev(prevLeaf.nextLeaf, cur.prevLeaf);
        prevLeaf.size = thres;
        memo.writeNode(prevLeaf, cur.prevLeaf);

        Data tmp = cur.value[0];
        adjustInternal(prevLeaf.parentAddr, tmp);

        return true;
    }

    bool grabFromPrev(Node &cur, Node &prevLeaf, const int addr) {
        for (int i = cur.size; i > 0; i--)
            cur.value[i] = cur.value[i - 1];

        int t = prevLeaf.size;
        cur.value[0] = prevLeaf.value[t - 1];
        prevLeaf.size--;
        cur.size++;

        Node fa;
        memo.readNode(fa, cur.parentAddr);
        int idx = sjtu::upper_bound(fa.value, fa.value + fa.size, cur.value[0]) - fa.value;
        fa.value[idx] = cur.value[0];
        memo.writeNode(cur, addr);
        memo.writeNode(prevLeaf, cur.prevLeaf);
        memo.writeNode(fa, cur.parentAddr);

        return true;
    }

    bool grabFromNext(Node &cur, Node &nextLeaf, const int addr) {
        int thres = blockSize / 2 - 1;
        cur.value[thres - 1] = nextLeaf.value[0];
        for (int i = 0; i < nextLeaf.size - 1; i++)
            nextLeaf.value[i] = nextLeaf.value[i + 1];
        nextLeaf.size--;
        cur.size++;

        Node fa;
        memo.readNode(fa, cur.parentAddr);
        Data tmp = cur.value[thres - 1];
        int idx = sjtu::upper_bound(fa.value, fa.value + fa.size, tmp) - fa.value;

        fa.value[idx - 1] = nextLeaf.value[0];
        memo.writeNode(cur, addr);
        memo.writeNode(nextLeaf, cur.nextLeaf);
        memo.writeNode(fa, cur.parentAddr);

        return true;
    }

    bool mergeNext(Node &cur, Node &nextLeaf, const int addr) {
        int low = blockSize / 2 - 2;
        int high = blockSize - 3;
        for (int i = low; i < high; i++)
            cur.value[i] = nextLeaf.value[i - low];

        cur.nextLeaf = nextLeaf.nextLeaf;
        updatePrev(cur.nextLeaf, addr);
        cur.size = high;
        memo.writeNode(cur, addr);

        Data abandon = nextLeaf.value[0];
        adjustInternal(cur.parentAddr, abandon);

        return true;
    }

    void adjustLeaf(int addr) {
        Node cur, prevLeaf, nextLeaf;
        memo.readNode(cur, addr);
        if (!cur.prevLeaf && !cur.nextLeaf)
            return;

        bool checkLeft = judge(cur.prevLeaf, cur.parentAddr, prevLeaf);
        bool checkRight = judge(cur.nextLeaf, cur.parentAddr, nextLeaf);
        if (checkLeft) {
            memo.readNode(nextLeaf, cur.nextLeaf);
            if (nextLeaf.size > blockSize / 2 - 1) {
                if (mergeFromRight(cur, nextLeaf, addr))
                    return;
            } else {
                if (mergeRight(cur, nextLeaf, addr))
                    return;
            }
        } else if (checkRight) {
            if (prevLeaf.size > blockSize / 2 - 1) {
                if (mergeFromLeft(cur, prevLeaf, addr)) {
                    return;
                }
            } else {
                if (mergeLeft(cur, prevLeaf, addr))
                    return;
            }
            return;
        }

        // both
        if (prevLeaf.size > blockSize / 2 - 1) {
            if (grabFromPrev(cur, prevLeaf, addr))
                return;
        } else if (nextLeaf.size > blockSize / 2 - 1) {
            if (grabFromNext(cur, nextLeaf, addr))
                return;
        } else {  //the last circumstance , merge the node with the next
            if (mergeNext(cur, nextLeaf, addr))
                return;
        }


    }

    void updateSib(const Node &sib, const int f_addr, const int pos, const int idx) {
        Node fa;
        memo.readNode(fa, f_addr);
        Data tmp = sib.value[idx];
        fa.value[pos - 1] = tmp;
        memo.writeNode(fa, f_addr);
    }

    void borrowValue(Node &cur, const int leftAddr, const int rightAddr, Data &pivot) {
        Node fa, left, right;  //the last value in leaf
        memo.readNode(fa, cur.parentAddr);
        memo.readNode(left, leftAddr);
        memo.readNode(right, rightAddr);

        bool leftCheck = !judge(cur.nextLeaf, cur.parentAddr, right);
        bool rightCheck = !judge(cur.nextLeaf, cur.parentAddr, right);

        if (!rightCheck) {
            int pos = sjtu::upper_bound(fa.value, fa.value + fa.size, pivot) - fa.value;
            if (pos == 0) {
                memo.refresh(cur.parentAddr, left.value[left.size - 1]);
            } else {
                updateSib(left, cur.parentAddr, pos, left.size - 1);
            }
        } else if (!leftCheck) {
            int pos = sjtu::upper_bound(fa.value, fa.value + fa.size, pivot) - cur.value;
            if (pos == 0)
                memo.refresh(cur.parentAddr, right.value[0]);
            else {
                updateSib(right, cur.parentAddr, pos, 0);
            }
        } else {  //both siblings are not belong to the same par
//                    readNode(right, cur.nextLeaf)
            int pos = sjtu::upper_bound(fa.value, fa.value + fa.size, pivot) - cur.value;
            if (pos == 0)
                memo.refresh(cur.parentAddr, right.value[0]);
            else {
                updateSib(right, cur.parentAddr, pos, 0);
            }
        }

    }

    bool erase(char *key, T val) {
        Data obj(key, val);
        int addr = findObj(obj, head.rootAddr);
        Node cur;
        memo.readNode(cur, addr);
        int idx = sjtu::upper_bound(cur.value, cur.value + cur.size, obj) - cur.value;
        idx--;
        if (cur.value[idx] != obj)
            return false;

        if (!idx && head.rootAddr != addr) {
            Data pivot = cur.value[0];
            if (cur.size == 1) {
                borrowValue(cur, cur.prevLeaf, cur.nextLeaf, pivot);
            } else {
                Node fa;
                memo.readNode(fa, cur.parentAddr);
                int pos = sjtu::upper_bound(fa.value, fa.value + fa.size, pivot) - fa.value;

                Data tmp = cur.value[1];
                if (!pos)
                    memo.refresh(fa.parentAddr, tmp);
                else {
                    fa.value[pos - 1] = tmp;
                    memo.writeNode(fa, cur.parentAddr);
                }
            }
        }

        int x = cur.size - 1;
        for (int i = idx; i < x; i++)
            cur.value[i] = cur.value[i + 1];
        cur.size = x;
        memo.writeNode(cur, addr);
        if (cur.size < blockSize / 2 - 1)
            adjustLeaf(addr);

        return true;
    }
};


int main() {

    int n;
    std::cin >> n;
    std::string s;
    char index[65];
    std::string name = "test";
    int value;
    Database<int> map(name);
    while (n--) {
        std::cin >> s >> index;
        if (s == "insert") {
            std::cin >> value;
            map.insert(index, value);
        } else if (s == "find") {
            bool flag = map.outputFind(index);
            if(!flag)
                std::cout << "null" << std::endl;
        } else if (s == "delete") {
            std::cin >> value;
            map.erase(index, value);
        }
    }


    return 0;
}