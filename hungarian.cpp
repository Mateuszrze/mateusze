#include<bits/stdc++.h>

using namespace std;

// znajduje NAJDROZSZE sposrod PELNYCH skojarzen w grafie dwudzielnym n x n
// przed uzyciem ustawic n oraz w[0..n-1][0..n-1]
typedef int T; // typ wag
#define N 128
T w[N][N]; int n;   // input
T lx[N], ly[N], sl[N];
int skojx[N], skojy[N], par[N], q[N];
bool markx[N], marky[N];

vector <int> hungarian () {
   for(int i=0; i<n; i++) {
      skojx[i] = skojy[i] = -1;
      ly[i] = 0;
      lx[i] = *max_element(w[i],w[i]+n);
   }
   for(int syf=0; syf<n; syf++) {
      int v = -1, qb = 0, qe = 0;
      for(int i=0; i<n; i++) {
         marky[i] = markx[i] = 0;
         sl[i] = -1;
         if (skojx[i] == -1) q[qe++] = i;
      }
      while (v == -1) {
         while (qb < qe) {
            int i = q[qb++];
            markx[i] = 1;
            for(int j=0; j<n; j++) if (!marky[j] and (sl[j] == -1 or sl[j] > lx[i]+ly[j]-w[i][j])){
               if ((sl[j] = lx[par[j] = i] + ly[j] - w[i][j]) == 0) {
                  marky[j] = 1;
                  if (skojy[j] != -1) q[qe++] = skojy[j];
                  else { v = j; goto end; }
               }
            }
         }
         T x = -1;
         for(int i=0; i<n; i++) if (!marky[i] && (x == -1 || sl[i] < x)) x = sl[i];
         for(int i=0; i<n; i++) {
            if (markx[i]) lx[i] -= x;
            if (marky[i]) ly[i] += x;
            else if ((sl[i] -= x) == 0) {
               marky[i] = 1;
               if (skojy[i] != -1) q[qe++] = skojy[i];
               else v = i;
            }
         }
      }
      end:
      while (v != -1) {
         int y = skojx[par[v]];
         skojx[par[v]] = v;
         skojy[v] = par[v];
         v = y;
      }
   }
   return vector <int> (skojx,skojx+n);
}
