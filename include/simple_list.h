#pragma once

template<typename T>
struct  Link {
    T val;
    Link* next;
    Link(T _val = nullptr, Link* _next = nullptr) : val(_val), next(_next) {}
};

template<typename T>
class Iterator {
    Link<T>* tmp;
public:
    Iterator(Link<T>* _tmp) : tmp(_tmp) {}
    bool hasNext() {
        return tmp != nullptr;
    }
    T Next() {
        if (!hasNext())
            throw - 1;
        T val = tmp->val;
        tmp = tmp->next;
        return val;
    }
    Link<T>* return_tmp() { return tmp; }
};

template<typename T>
class List {
    Link<T>* st;
    Link<T>* end;
public:
    List() : st(nullptr), end(nullptr) {}
    List(const List& ls) {
        st = nullptr;
        end = nullptr;
        Link<T>* tmp = ls.st;
        while (tmp != nullptr) {
            addLast(tmp->val);
            tmp = tmp->next;
        }
    }
    ~List() {
        Clean();
    }
    void delFirst() {
        if (st == nullptr)
            return;
        Link<T>* tmp;
        tmp = st;
        st = st->next;
        if (st == nullptr) {
            end = nullptr;
        }
        delete(tmp);
    }
    void delLast() {
        if (st == nullptr)
            throw - 1;
        if (st == end) {
            delete st;
            st = nullptr;
            end = nullptr;
            return;
        }
        Link<T>* cur = st;
        while (cur->next != end) {
            cur = cur->next;
        }
        delete end;
        cur->next = nullptr;
        end = cur;
    }
    void Clean() {
        while (st != nullptr)
            delFirst();
    }
    void addFirst(T value) {
        Link<T>* tmp = new Link<T>(value, st);
        st = tmp;
        if (end == nullptr) {
            end = st;
        }
    }
    void addLast(T value) {
        Link<T>* n = new Link<T>(value, nullptr);
        if (st == nullptr) {
            st = n;
            end = n;
        }
        else {
            end->next = n;
            end = n;
        }
    }
    void add(T value) {
        Link<T>* v = new Link<T>(value);
        if (st == nullptr) {
            addFirst(value);
            return;
        }
        if (value <= st->val) {
            addFirst(value);
            return;
        }
        Link<T>* cur = st;
        while ((cur->next != nullptr) && (cur->next->val < value)) {
            cur = cur->next;
        }
        v->next = cur->next;
        cur->next = v;
        if (cur == end) {
            end = v;
        }
    }
    int Size() {
        Link<T>* tmp = st;
        if (tmp == nullptr)
            return 0;
        int n = 1;
        while (tmp->next != nullptr) {
            n++;
            tmp = tmp->next;
        }
        return n;
    }
    void delInd(int id) {
        Link<T>* tmp = st;
        if (tmp == nullptr)
            throw - 1;
        if (id == 0) {
            delFirst();
            return;
        }
        if (tmp->next == nullptr)
            throw - 1;
        while (id > 1) {
            if (tmp == nullptr)
                throw - 1;
            tmp = tmp->next;
            id--;
        }
        Link<T>* tmp2 = tmp->next;
        tmp->next = tmp2->next;
        if (tmp2 == end) {
            end = tmp;
        }
        delete tmp2;
    }
    List<T>& operator=(const List<T>& other) {
        if (this != &other) {
            Clean();
            Link<T>* tmp = other.st;
            while (tmp != nullptr) {
                addLast(tmp->val);
                tmp = tmp->next;
            }
        }
        return *this;
    }
    Iterator<T> itr() { return Iterator<T>(st); };
    Iterator<T> itr(Link<T>* a) { return Iterator<T>(a); };
};

int search(int* arr, int n, List<int> l, List<int>& res);
