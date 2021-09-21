#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Point
{
    int x, y;
};

// a globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;

// a utility function to find next to top in a stack
Point next_to_top(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// a utility function to swap two points
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// a utility function to return square of distance
// between p1 and p2
int dist_square(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}

// to find orientation of ordered triplet (p, q, r).
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if(val == 0)
        return 0;
    else if(val > 0)
        return 1;
    else
        return 2;
}

// a function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // find orientation
    int o = orientation(p0, *p1, *p2);
    if(o == 0)
    {
        if((dist_square(p0, *p2) >= dist_square(p0, *p1)))
            return -1;
        else
            return 1;
    }
    else if(o == 2)
        return -1;
    else
        return 1;
}

void print(stack<Point> S)
{
    // now stack has the output points, print contents of stack
    while(!S.empty())
    {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y <<")" << endl;
        S.pop();
    }
}

// prints convex hull of a set of n points.
void convex_hull(Point points[], int n)
{
    // find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        // pick the bottom-most or chose the left
        // most point in case of tie
        if((y < ymin) || (ymin == y && points[i].x < points[min].x))
        {
            ymin = points[i].y;
            min = i;
        }
    }

    // place the bottom-most point at first position
    swap(points[0], points[min]);

    // sort n-1 points with respect to the first point,
    // a point p1 comes before p2 in sorted ouput if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // if two or more points make same angle with p0,
    // remove all but the one that is farthest from p0
    // remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for(int i = 1; i < n; i++)
    {
        // keep removing i while angle of i and i+1 is same
        // with respect to p0
        while(i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;

        points[m] = points[i];
        m++;  // update size of modified array
    }

    // if modified array of points has less than 3 points,
    // convex hull is not possible
    if(m < 3)
        return;

    // create an empty stack and push first three points
    // to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // process remaining n-3 points
    for(int i = 3; i < m; i++)
    {
        // keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while(orientation(next_to_top(S), S.top(), points[i]) != 2)
            S.pop();

        S.push(points[i]);
    }

    print(S);
}

int main()
{
    int N = 7;

    Point points[] = { {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3} };

    convex_hull(points, N);
}
