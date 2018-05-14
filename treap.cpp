#include<bits/stdc++.h>

using namespace std;

// numerujemy od 1 

struct treap
{
      treap * left = 0, *right = 0;
      treap * parent = 0;
      int k; // wartosc w wierzchołku
      int rank;
      int r = 1;
      bool rev = false; // czy jest obrocony

      treap (int K = 0)
      {
            k=K;
            rank=rand();
            r=1;
            rev=false;
            left=0;
            right=0;
            parent=0;
      }

      void propagate()
      {
            if(rev)
            {
                  swap(left,right);
                  if(left)
                        left->rev=!left->rev;
                  if(right)
                        right->rev=!right->rev;
                  rev=false;
            }

      }

};

inline int r(treap *t)
{
      return t == 0 ? 0 : t->r;
}

inline void update(treap *t)
{
      if(t)
            t->r=r(t->left)+r(t->right)+1;
      if(t->left)
            t->left->parent=t;
      if(t->right)
            t->right->parent=t;
}

treap * merge (treap *a, treap *b) // dokleja treapa do treapa
{
      if(a==0)
            return b;
      if(b==0)
            return a;
      a->propagate();
      b->propagate();
      if(a->rank > b->rank)
      {
            a->right=merge(a->right,b);
            update(a);
            return a;
      }
      else
      {
            b->left=merge(a,b->left);
            update(b);
            return b;
      }

}

pair<treap * ,treap *> split(treap *t ,int k) // [1, k] , [k + 1, ...]
{
      if(t==0)
            return pair<treap * ,treap *> (0,0);
      t->propagate();
      if(r(t->left)>=k)
      {
            auto p=split(t->left,k);
            t->left=p.second;
            update(t);
            if(p.first)
                  p.first->parent=0;
            return {p.first,t};
      }
      else
      {
            auto p=split(t->right,k-r(t->left)-1);
            t->right=p.first;
            update(t);
            if(p.second)
                  p.second->parent=0;
            return {t,p.second};
      }

}

treap * reverse(treap *t,int a,int b) // [1, a - 1] , [a, b] (odwrocone) , [b + 1, ...]
{
      t->propagate();
      // b->propagate();
      auto p=split(t,b);
      auto p2=split(p.first,a);
      if(p2.second)
            p2.second->rev=!p2.second->rev;
      return merge(merge(p2.first,p2.second),p.second);
}

int nr(treap *t) // ktory od lewej jest ten wierzcholek
{
      t->propagate();
      treap * par =t->parent;
      if(par == 0)
            return r(t->left);
      if(par->left == t)
            return nr(par)-r(t->right)-1;
      return nr(par) +r(t->left)+1;
}

treap * kty(treap * t, int k) // zwraca kty treap w drzewie ktorego korzeniem jest t
{
      t->propagate();
      if(r(t->left) >= k)
            return kty(t->left, k);
      if(r(t->left) == k - 1)
            return t;
      return kty(t->right, k - r(t->left) - 1);
}

void propagate_up(treap *t)
{
      if(t == 0)
            return ;
      propagate_up(t->parent);
      t->propagate();
}


