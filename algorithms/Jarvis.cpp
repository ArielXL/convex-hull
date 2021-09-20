#include <bits/stdc++.h>
#define endl "\n"

using namespace std;

struct Point
{
    int x, y;
};

// to find orientation of ordered triplet (p, q, r)
// 0 --> p, q and r are colinear
// 1 --> clockwise
// 2 --> counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if(val == 0)
        return 0;
    else if(val > 0)
        return 1;
    else
        return 2;
}

// return convex hull of a set of N points
vector<Point> convex_hull(int n, Point points[])
{
    // initialize Result
    vector<Point> hull;

    // find the leftmost point
    int l = 0;
    for(int i = 1; i < n; i++)
    {
        if(points[i].x < points[l].x)
            l = i;
    }

    // start from leftmost point, keep moving counterclockwise
    // until reach the start point again.  This loop runs O(h)
    // times where h is number of points in result or output.
    int p = l, q;
    do
    {
        // add current point to result
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x,
        // q) is counterclockwise for all points 'x'. The idea
        // is to keep track of last visited most counterclock-
        // wise point in q. If any point 'i' is more counterclock-
        // wise than q, then update q.
        q = (p + 1) % n;
        for(int i = 0; i < n; i++)
        {
           // if i is more counterclockwise than current q, then
           // update q
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }

        // now q is the most counterclockwise with respect to p
        // set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;

    } while(p != l);  // while we don't come to first point

    return hull;
}

void print(vector<Point> hull)
{
    for(int i = 0; i < hull.size(); i++)
    {
        cout << "(" << hull[i].x << ", " << hull[i].y << ")" << endl;
    }
}

int main()
{
    int N = 7;
    Point S[] = { {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3} };

    // there must be at least 3 points
    if(N < 3)
        return 0;

    vector<Point> hull = convex_hull(N, S);

    print(hull);
}
