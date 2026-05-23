#include"list.h"
#include<iostream>

/*void arr_to_list(int* arr, int n, List<int*, IteratorPair<int*>>& l) {
    for (int i = n - 1; i > 0; i--) {
        if (arr[i] - arr[i - 1] < 0) {
            l.addFirst(&arr[i - 1]);
        }
    }
}*/

int search(int* arr, int n, List<int> l, List<int>& res) {
    for (int i = 0; i < n; i++) {
        l.addFirst(arr[i]);
    }
    Iterator<int> i1 = l.itr();
    int max = 0;
    while (i1.hasNext()) {
        Link<int>* u = i1.return_tmp();
        Iterator<int> i2 = l.itr(u->next);
        int st = i1.Next();
        int maxst = st;
        if (max < st) {
            max = st;
            res.Clean();
            res.addFirst(st);
        }
        int t2 = 1;
        while (i2.hasNext()) {
            t2++;
            int tmp = i2.Next();
            if (tmp < maxst)maxst = tmp;
            int sq = maxst * t2;
            if (sq > max) {
                max = sq;
                if (t2 == 2) {
                    res.Clean();
                    Iterator<int> q1 = l.itr(u);
                    for (int q = 0; q < t2; q++) {
                        res.addFirst(q1.Next());
                    }
                }
                else {
                    res.addFirst(tmp);
                }
            }
        }
    }
    return max;
}
