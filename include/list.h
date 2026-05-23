#pragma once
#include<random>

template<typename T>
struct  Node {
    T val;
    size_t lvl;
    Node** next;
    Node() : val(T()), lvl(0), next(nullptr) {}
    Node(T v, size_t l) : val(v), lvl(l) {
        next = new Node * [lvl]();
        for (size_t i = 0; i < lvl; i++) {
            next[i] = nullptr;
        }
    }
    Node(size_t l) : val(T()), lvl(l) {
        next = new Node * [lvl]();
        for (size_t i = 0; i < lvl; i++) {
            next[i] = nullptr;
        }
    }
    Node(const Node& other) {
        val = other.val;
        lvl = other.lvl;
        next = new Node * [lvl]();
        for (size_t i = 0; i < lvl; i++) {
            next[i] = other.next[i];
        }
    }
    ~Node() {
        delete[]next;
    }
    Node<T>& operator=(const Node<T>& other) {
        if (this == &other)return *this;
        val = other.val;
        if (lvl != other.lvl) {
            delete[] next;
            lvl = other.lvl;
            next = new Node * [lvl]();
        }
        for (size_t i = 0; i < lvl; i++) {
            next[i] = other.next[i];
        }
        return *this;
    }
};

template<typename T>
class SkipListIterator {
    Node<T>* tmp;
    Node<T>* end;
public:
    SkipListIterator(Node<T>* _tmp, Node<T>* _end) : tmp(_tmp), end(_end) {}
    bool hasNext() {
        return tmp != end;
    }
    T Next() {
        if (!hasNext())
            throw - 1;
        T val = tmp->val;
        tmp = tmp->next[0];
        return val;
    }
};

template<typename T>
class SkipList {
    Node<T>* head;
    Node<T>* end;
    Node<T>** lasts;
    size_t maxLvl;
    double prob;
    size_t randLvl() {
        size_t l = 1;
        while ((l < maxLvl) && (((double)rand() / RAND_MAX) < prob)) {
            l++;
        }
        return l;
    }
    Node<T>* update(T v, Node<T>* update[]) {
        Node<T>* cur = head;
        for (int i = (int)maxLvl - 1; i >= 0; i--) {
            while ((cur->next[i] != end) && (cur->next[i]->val < v)) {
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        cur = cur->next[0];
        return cur;
    }
public:
    SkipList(size_t ml = 16, double pr = 0.5) : maxLvl(ml), prob(pr) {
        head = new Node<T>(maxLvl);
        end = new Node<T>(maxLvl);
        lasts = new Node<T>*[maxLvl];
        for (size_t i = 0; i < maxLvl; i++) {
            head->next[i] = end;
            end->next[i] = nullptr;
            lasts[i] = head;
        }
    }
    SkipList(const SkipList& other) {
        maxLvl = other.maxLvl;
        prob = other.prob;
        head = new Node<T>(maxLvl);
        end = new Node<T>(maxLvl);
        lasts = new Node<T>*[maxLvl];
        for (size_t i = 0; i < maxLvl; i++) {
            head->next[i] = end;
            end->next[i] = nullptr;
            lasts[i] = head;
        }
        Node<T>* cur = other.head->next[0];
        while (cur != other.end) {
            add(cur->val);
            cur = cur->next[0];
        }
    }
    SkipList<T>& operator=(const SkipList<T>& other) {
        if (this == &other)return *this;
        if (maxLvl != other.maxLvl) {
            delete head;
            delete end;
            delete[]lasts;
            maxLvl = other.maxLvl;
            head = new Node<T>(maxLvl);
            end = new Node<T>(maxLvl);
            lasts = new Node<T>*[maxLvl];
            for (size_t i = 0; i < maxLvl; i++) {
                head->next[i] = end;
                end->next[i] = nullptr;
                lasts[i] = head;
            }
        }
        else {
            clear();
        }
        prob = other.prob;
        Node<T>* cur = other.head->next[0];
        while (cur != other.end) {
            add(cur->val);
            cur = cur->next[0];
        }
        return *this;
    }
    void clear() {
        Node<T>* cur = head->next[0];
        while (cur != end) {
            Node<T>* tmp = cur;
            cur = cur->next[0];
            delete tmp;
        }
        for (size_t i = 0; i < maxLvl; i++) {
            head->next[i] = end;
            lasts[i] = head;
        }
    }
    ~SkipList() {
        clear();
        delete head;
        delete end;
        delete[]lasts;
    }
    bool isEmpty() const {
        return head->next[0] == end;
    }
    Node<T>* find(T v) const {
        if (isEmpty())return nullptr;
        Node<T>* cur = head;
        for (int i = (int)maxLvl - 1; i >= 0; i--) {
            while ((cur->next[i] != end) && (cur->next[i]->val < v)) {
                cur = cur->next[i];
            }
        }
        cur = cur->next[0];
        if ((cur != end) && (cur->val == v))return cur;
        return nullptr;
    }
    void addLast(T v) {
        size_t rl = randLvl();
        Node<T>* n = new Node<T>(v, rl);
        for (size_t i = 0; i < rl; i++) {
            n->next[i] = lasts[i]->next[i];
            lasts[i]->next[i] = n;
            lasts[i] = n;
        }
    }
    void add(T v) {
        if (isEmpty()) {
            addLast(v);
            return;
        }
        if (v > lasts[0]->val) {
            addLast(v);
            return;
        }
        Node<T>** upd = new Node<T>*[maxLvl];
        Node<T>* cur = update(v, upd);
        if ((cur != end) && (cur->val == v)) {
            return;
        }
        size_t rl = randLvl();
        Node<T>* n = new Node<T>(v, rl);
        for (size_t i = 0; i < rl; i++) {
            n->next[i] = upd[i]->next[i];
            upd[i]->next[i] = n;
        }
        delete[]upd;
    }
    void remove(T v) {
        if (isEmpty())throw - 1;
        Node<T>** upd = new Node<T>*[maxLvl];
        Node<T>* tmp = update(v, upd);
        if ((tmp == end) || (tmp->val != v)) {
            throw - 1;
        }
        size_t l = tmp->lvl;
        for (size_t i = 0; i < l; i++) {
            upd[i]->next[i] = tmp->next[i];
        }
        if (v == lasts[0]->val) {
            for (size_t i = 0; i < maxLvl; i++) {
                Node<T>* cur = head;
                while (cur->next[i] != end) {
                    cur = cur->next[i];
                }
                lasts[i] = cur;
            }
        }
        else {
            for (size_t i = 0; i < l && i < maxLvl; i++) {
                if (tmp == lasts[i]) {
                    lasts[i] = upd[i];
                }
            }
        }
        delete tmp;
        delete[]upd;
    }
    SkipListIterator<T> itr() { return SkipListIterator<T>(head->next[0], end); };
    SkipListIterator<T> itr(Node<T>* a) { return SkipListIterator<T>(a, end); };
    SkipListIterator<T> itr() const { return SkipListIterator<T>(head->next[0], end); };
    SkipListIterator<T> itr(Node<T>* a) const { return SkipListIterator<T>(a, end); };

    T returnVal(int ind) {
        if (isEmpty())return T();
        Node<T>* cur = head;
        for (int i = 0; i < ind; i++) {
            if (cur == end)throw - 1;
            cur = cur->next[0];
        }
        cur = cur->next[0];
        return cur->val;
    }
};