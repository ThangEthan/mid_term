#include <iostream>
#include <vector>
using namespace std;
template <typename A, typename B>
void zip(const vector<A> &a, const vector<B> &b, vector<pair<A,B> > &zipped)
{
    for(size_t i=0; i<a.size(); ++i)
    {
        zipped.push_back(make_pair(a[i], b[i]));
    }
}