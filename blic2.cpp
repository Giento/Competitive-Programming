#include <iostream>
#include <bits/stdc++.h>
using namespace std;


void construct_segment_tree(vector<pair<int, string>>& segtree,
                            vector<pair<int, string>>& a, int n) {
   // assign values to leaves of the segment tree
   for (int i = 0; i < n; i++)
      segtree[n + i] = a[i];
 
   // assign values to internal nodes
   //to compute maximum in a given range 
   for (int i = n - 1; i >= 1; i--)
      segtree[i] = max(segtree[2 * i], segtree[2 * i + 1]);
}
 
void update(vector<pair<int, string>>& segtree, int pos, 
            pair<int, string> value, int n) {
   // change the index to leaf node first
   pos += n;
 
   // update the value at the leaf node
   segtree[pos] = value;
 
   while (pos > 1) {
      // move up one level at a time in the tree
      pos >>= 1;
 
      // update the values in the nodes in
      // the next higher level
      segtree[pos] = max(segtree[2 * pos], segtree[2 * pos + 1]);
   }
}
 
pair<int, string> range_query(vector<pair<int, string>>& segtree, 
               int left, int right, int n) {
   // change the index to leaf node first
   left += n;
   right += n;
 
   // initialize maximum to a very low value
   pair<int, string> ma;
   ma.first = INT_MIN;
 
   while (left < right) {
 
      // if left index in odd
      if (left & 1) {
         if (segtree[left].first > ma.first) {
            ma.first = segtree[left].first;
            ma.second = segtree[left].second;
         }
 
         // make left index even
         left++;
      }
 
      // if right index in odd
      if (right & 1) {
         // make right index even
         right--;
 
         if (segtree[right].first > ma.first) {
            ma.first = segtree[right].first;
            ma.second = segtree[right].second;
         }
      }
 
      // move to the next higher level
      left /= 2;
      right /= 2;
   }
   return ma;
}


int main(void) {
   int n;
   cin >> n;
   vector<pair<int,string>> vect;
   vector<int> vect_p;
   
   for (int i = 0; i < n; i++) {
      int a;
      string s;
      cin >> a >> s;
      vect.push_back(make_pair(a, s));
      vect_p.push_back(a);
   }

    /* Construct the segment tree by assigning
    the values to the internal nodes*/
   vector<pair<int, string>> segtree(2 * n);
   construct_segment_tree(segtree, vect, n);
 
   int q;
   cin >> q;
   char queries[q];
   unsigned int l[q];
   long long int r[q];

   for (int i = 0; i < q; i++)
      cin >> queries[i] >> l[i] >> r[i];

   for (int i = 0; i < q; i++) {
      pair<int, string> maxi;
      if (queries[i] == 'q') {
         maxi = range_query(segtree, l[i] - 1, r[i], n);
         cout << maxi.second << endl;
      } else {
         pair<int, string> p;
         int newValue = vect[l[i] - 1].first + r[i];
         p.first = newValue;
         p.second = vect[l[i] - 1].second;
         vect[l[i] - 1] = p;
         update(segtree, l[i] - 1, p, n);
      }
   }
    return 0;
}