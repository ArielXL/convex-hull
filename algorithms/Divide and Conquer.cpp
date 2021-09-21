#include<bits/stdc++.h>
#define endl "\n"
#define pii pair<int, int>

using namespace std;

// stores the centre of polygon (It is made
// global because it is used in compare function)
pii mid;

// determines the quadrant of a point
// (used in compare())
int quad(pii p)
{
    if(p.first >= 0 && p.second >= 0)
        return 1;
    else if(p.first <= 0 && p.second >= 0)
        return 2;
    else if(p.first <= 0 && p.second <= 0)
        return 3;
    else
        return 4;
}

// checks whether the line is crossing the polygon
int orientation(pii a, pii b, pii c)
{
    int res = (b.second - a.second) * (c.first - b.first) -
              (c.second - b.second) * (b.first - a.first);

    if(res == 0)
        return 0;
    else if(res > 0)
        return 1;
    else
        return -1;
}

// compare function for sorting
bool compare(pii p1, pii q1)
{
    pii p = make_pair(p1.first - mid.first, p1.second - mid.second);
    pii q = make_pair(q1.first - mid.first, q1.second - mid.second);

    int one = quad(p);
    int two = quad(q);

    if(one != two)
        return (one < two);
    else
        return (p.second * q.first < q.second * p.first);
}

// finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<pii> merger(vector<pii> a, vector<pii> b)
{
    // n1 -> number of points in polygon a
    // n2 -> number of points in polygon b
    int n1 = a.size(), n2 = b.size();

    int ia = 0, ib = 0;
    for(int i = 1; i < n1; i++)
    {
        if(a[i].first > a[ia].first)
            ia = i;
    }

    // ib -> leftmost point of b
    for(int i = 1; i < n2; i++)
    {
        if(b[i].first < b[ib].first)
            ib = i;
    }

    // finding the upper tangent
    int inda = ia, indb = ib;
    bool done = 0;
    while(!done)
    {
        done = 1;
        while(orientation(b[indb], a[inda], a[(inda + 1) % n1]) >= 0)
            inda = (inda + 1) % n1;

        while(orientation(a[inda], b[indb], b[(n2 + indb - 1) % n2]) <= 0)
        {
            indb = (n2 + indb - 1) % n2;
            done = 0;
        }
    }

    int uppera = inda, upperb = indb;
    inda = ia, indb = ib;
    done = 0;
    int g = 0;

    //finding the lower tangent
    while(!done)
    {
        done = 1;
        while(orientation(a[inda], b[indb], b[(indb + 1) % n2]) >= 0)
            indb = (indb + 1) % n2;

        while(orientation(b[indb], a[inda], a[(n1 + inda - 1) % n1]) <= 0)
        {
            inda = (n1 + inda - 1) % n1;
            done = 0;
        }
    }

    int lowera = inda, lowerb = indb;
    vector<pii> ret;

    // ret contains the convex hull after merging the two convex hulls
    // with the points sorted in anti-clockwise order
    int ind = uppera;
    ret.push_back(a[uppera]);
    while(ind != lowera)
    {
        ind = (ind + 1) % n1;
        ret.push_back(a[ind]);
    }

    ind = lowerb;
    ret.push_back(b[lowerb]);
    while(ind != upperb)
    {
        ind = (ind + 1) % n2;
        ret.push_back(b[ind]);
    }
    return ret;
}

// brute force algorithm to find convex hull for a set
// of less than 6 points
vector<pii> brute_hull(vector<pii> a)
{
    // take any pair of points from the set and check
    // whether it is the edge of the convex hull or not.
    // if all the remaining points are on the same side
    // of the line then the line is the edge of convex
    // hull otherwise not
    set<pii> s;

    for(int i = 0; i < a.size(); i++)
    {
        for(int j = i + 1; j < a.size(); j++)
        {
            int x1 = a[i].first, x2 = a[j].first;
            int y1 = a[i].second, y2 = a[j].second;

            int a1 = y1 - y2;
            int b1 = x2 - x1;
            int c1 = x1 * y2 - y1 * x2;
            int pos = 0, neg = 0;

            for(int k = 0; k < a.size(); k++)
            {
                if(a1 * a[k].first + b1 * a[k].second + c1 <= 0)
                    neg++;
                if(a1 * a[k].first + b1 * a[k].second + c1 >= 0)
                    pos++;
            }
            if(pos == a.size() || neg == a.size())
            {
                s.insert(a[i]);
                s.insert(a[j]);
            }
        }
    }

    vector<pii> ret;
    for(auto e : s)
    {
        ret.push_back(e);
    }

    // sorting the points in the anti-clockwise order
    mid = {0, 0};
    int n = ret.size();
    for(int i = 0; i < n; i++)
    {
        mid.first += ret[i].first;
        mid.second += ret[i].second;
        ret[i].first *= n;
        ret[i].second *= n;
    }

    sort(ret.begin(), ret.end(), compare);

    for(int i = 0; i < n; i++)
        ret[i] = make_pair(ret[i].first / n, ret[i].second / n);

    return ret;
}

// returns the convex hull for the given set of points
vector<pii> divide(vector<pii> a)
{
    // if the number of points is less than 6 then the
    // function uses the brute algorithm to find the
    // convex hull
    if(a.size() <= 5)
        return brute_hull(a);

    // left contains the left half points
    // right contains the right half points
    vector<pii>left, right;
    for(int i = 0; i < a.size() / 2; i++)
        left.push_back(a[i]);
    for(int i = a.size() / 2; i < a.size(); i++)
        right.push_back(a[i]);

    // convex hull for the left and right sets
    vector<pii> left_hull = divide(left);
    vector<pii> right_hull = divide(right);

    // merging the convex hulls
    return merger(left_hull, right_hull);
}

void print(vector<pii> ans)
{
    for(auto e : ans)
    {
       cout << e.first << " " << e.second << endl;
    }
}

int main()
{
    int N, x, y;
    cin >> N;

    vector<pii> a;

    for(int i = 0; i < N; i++)
    {
        cin >> x >> y;
        a.push_back(make_pair(x, y));
    }

    // sorting the set of points according
    // to the x-coordinate
    sort(a.begin(), a.end());
    vector<pii> ans = divide(a);

    print(ans);
}
