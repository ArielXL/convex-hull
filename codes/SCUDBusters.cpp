#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

const double EPS = 1e-9;

struct point
{
    int x, y;
    
    point() { }
    
    point(const int _x, const int _y)
    {
        x =_x; 
        y =_y;
    }
    
    bool operator < (const point &p) const
    {
        if(x != p.x) 
            return x < p.x;
        else
            return y < p.y;
    }
};

bool ccw(const point &p1, const point &p2, const point &p3)
{
    return (p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.y * 
                            p2.x - p2.y * p3.x - p3.y * p1.x) > 0;
}

vector<point> convex_hull(vector<point> &P)
{
    sort(P.begin(), P.end());
    
    int n = P.size(), k=0;
    point H[2 * n];
    
    for(int i = 0; i < n; i++)
    {
        while(k >= 2 && !ccw(H[k - 2], H[k - 1], P[i])) 
            k--;
        H[k++] = P[i];
    }
    
    for(int i = n - 2, t = k; i >= 0; i--)
    {
        while(k > t && !ccw(H[k - 2], H[k - 1], P[i])) 
            k--;
        H[k++] = P[i];
    }
    
    return vector<point> (H, H + k - 1);
}

bool point_inside_polygon(const point P, const vector<point> &polygon)
{
    bool inside = 0;
    int n = polygon.size();
    
    for(int i = 0, j = n - 1; i < n; j = i++)
    {
        if((polygon[i].y <= P.y && P.y < polygon[j].y) || 
                            (polygon[j].y <= P.y && P.y < polygon[i].y))
        {
            if(P.x - EPS < (polygon[j].x - polygon[i].x) * (P.y - polygon[i].y) * 
                                1.0 / (polygon[j].y - polygon[i].y) + polygon[i].x) 
                inside ^= 1;
        }
    }
    
    return inside;
}

double signed_area(const vector<point> &polygon)
{
    int n = polygon.size();
    int area = 0;

    for(int i = 1; i < n; i++)
    {
        area += polygon[i].x * (polygon[i + 1 < n ? i + 1 : i + 1 - n].y - polygon[i - 1].y);
    }
    area += polygon[0].x * (polygon[1].y - polygon[n - 1].y);
    
    return area / 2.0;
}

double get_solution(vector<vector<point> > L, bool valid[], int n)
{
    double solution = 0;
    for(int i = 0; i < n; i++)
    {
        if(!valid[i]) 
            solution += fabs(signed_area(L[i]));
    }
    return solution;
}

int main()
{
    ios_base :: sync_with_stdio(0);
    cin.tie(0);

    int N, x, y, n = 0;
    
    vector< vector<point> > L;
    vector<point> hull,aux2;
    
    while(true)
    {
        scanf("%d", &N);

        if(N == -1) 
            break;
        
        n++;
        
        hull.clear();
        
        for(int i = 0; i < N; i++)
        {
            scanf("%d %d", &x, &y);
            hull.push_back(point(x, y));
        }
        
        vector<point> conv_hull = convex_hull(hull);
        L.push_back(conv_hull);
    }
    
    bool valid[n];
    memset(valid, true, sizeof(valid));
    
    while(scanf("%d %d", &x, &y) != EOF)
    {
        // scanf("%d %d", &x, &y);
        for(int i = 0; i < n; i++)
        {
            if(!valid[i]) 
                continue;
            if(point_inside_polygon(point(x,y), L[i]))
            {
                valid[i] = false;
                break;
            }
        }
    }
    
    double solution = get_solution(L, valid, n);

    printf("%.2f\n", solution);
}