#include <bits/stdc++.h>
using namespace std;

template <typename T = int, size_t SIZE = 10>
struct PersistentArray
{
    PersistentArray(size_t n = 0) : PersistentArray(n, nullptr) {}
    PersistentArray(const vector<T> &src) : PersistentArray(src.size())
    {
        for (size_t i = 0; i < _n; i++)
        {
            _destructive_set(_root, i, src[i]);
        }
    }

    size_t size() { return _n; }

    PersistentArray resize(size_t n) { return PersistentArray(n, _root); }

    void destructive_set(size_t i, const T &v)
    {
        assert(i < _n);
        _destructive_set(_root, i, v);
    }

    PersistentArray set(size_t i, const T &v)
    {
        assert(i < _n);
        Node *nr = _set(_root, i, v);
        return PersistentArray(_n, nr);
    }

    T get(size_t i)
    {
        assert(i < _n);
        return _get(_root, i)->v;
    }

    PersistentArray push(const T &v)
    {
        Node *nr = _set(_root, _n, v);
        return PersistentArray(_n + 1, nr);
    }

    PersistentArray pop()
    {
        assert(_n > 0);
        return PersistentArray(_n - 1, _root);
    }

private:
    struct Node
    {
        T v;
        Node *ch[SIZE] = {};
    };
    size_t _n;
    Node *_root = nullptr;
    PersistentArray(size_t n, Node *root) : _n(n), _root(root) {}

    void _destructive_set(Node *t, size_t i, const T &v)
    {
        if (!t)
            t = new Node();
        if (i == 0)
            t->v = v;
        else
            _destructive_set(t->ch[i % SIZE], i / SIZE, v);
    }

    Node *_set(const Node *t, size_t i, const T &v)
    {
        Node *res = new Node();
        if (t)
        {
            res->v = t->v;
            memcpy(res->ch, t->ch, sizeof(t->ch));
        }
        if (i == 0)
            res->v = v;
        else
            res->ch[i % SIZE] = _set(res->ch[i % SIZE], i / SIZE, v);
        return res;
    }
    Node *_get(Node *t, size_t i)
    {
        if (!t)
            return new Node();
        if (i == 0)
            return t;
        return _get(t->ch[i % SIZE], i / SIZE);
    }
};
