#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Point 
{
    double x, y;
};

Point P[1000], CH[1000];

double get_area(Point P[], int n)
{
    double area = 0;
    for(int i = 0; i < n; i++)
        area += P[i].x * P[i + 1].y - P[i].y * P[i + 1].x;
    return fabs(area) / 2;
}

double cross(Point o, Point a, Point b)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool cmp(Point a, Point b)
{
    if(a.x != b.x)
        return a.x < b.x;
    else
        return a.y < b.y;
}

int get_convex_hull(int n)
{
    sort(P, P+n, cmp);
    int i, m, t;
    m = 0;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(CH[m-2], CH[m-1], P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(CH[m-2], CH[m-1], P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    return m;
}

int main()
{
    cout << setprecision(2) << fixed;

    int n, cases = 1;
    double x, y;
    Point point;

    while(true)
    {
        cin >> n;

        if(n == 0)
            break;

        for(int i = 0; i < n; i++)
        {
            cin >> x >> y;
            point.x = x;
            point.y = y;
            P[i] = point;
        }

        P[n] = P[0];
        
        double area_polygon = get_area(P, n);
        
        int m = get_convex_hull(n);

        double area_convex_hull = get_area(CH, m - 1);
        
        double por_ciento = (area_convex_hull - area_polygon) * 100 / area_convex_hull;

        cout << "Tile #" << cases << endl;
        cout << "Wasted Space = " << por_ciento << " %" << endl;

        cases++;
        cout << endl;
    }
}
