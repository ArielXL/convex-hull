#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Point
{
	int x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

double cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> &p)
{
    int n = p.size(), k = 0;
    vector<Point> h(2 * n);
    sort(p.begin(), p.end());

    for (int i = 0; i < n; h[k++] = p[i++])
        while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) <= 0) --k;

    for (int i = n - 2, t = k + 1; i >= 0; h[k++] = p[i--])
        while (k >= t && cross(h[k - 2], h[k - 1], p[i]) <= 0) --k;

    return vector<Point>(h.begin(), h.begin() + k - (k > 1));
}

void print(vector<Point> hull)
{
    for(int i = 0; i < hull.size(); i++)
    {
        cout << hull[i].x << " " << hull[i].y << endl;
    }
}

int main()
{
    int N, x, y;
    cin >> N;

    Point point;
    vector<Point> p;

    for(int i = 0; i < N; i++)
    {
        cin >> x >> y;
        point.x = x;
        point.y = y;
        p.push_back(point);
    }

    vector<Point> conv_hull = convex_hull(p);

    print(conv_hull);
}
