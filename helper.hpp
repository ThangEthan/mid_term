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

template <typename A, typename B>
void unzip(const vector<pair<A,B> > &zipped, vector<A> &a, vector<B> &b)
{
    for(size_t i=0; i<a.size(); i++)
    {
        a[i] = zipped[i].first;
        b[i] = zipped[i].second;
    }
}