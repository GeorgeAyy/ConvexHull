#include <iostream>
#include <vector>

// Structure to represent a point in the Cartesian plane
struct Point {
    int x, y;
};

// Function to calculate the orientation of three points (p, q, r)
// Returns 0 for collinear, 1 for clockwise, and 2 for counterclockwise
int orientation(const Point& p, const Point& q, const Point& r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;  // Collinear points
    return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
}

// Recursive function to find the convex hull given a set of points
void findHull(const std::vector<Point>& points, int n, const Point& p1, const Point& pn, std::vector<Point>& hull) {
    if (n < 1)
        return;

    int maxDist = -1;
    int maxIndex = -1;

    // Find the point with the maximum distance from the line (p1, pn)
    for (int i = 0; i < n; i++) {
        int dist = std::abs(orientation(p1, pn, points[i]));
        if (dist > maxDist) {
            maxDist = dist;
            maxIndex = i;
        }
    }

    const Point& pFarthest = points[maxIndex];
    hull.push_back(pFarthest);

    std::vector<Point> leftSet, rightSet;

    // Partition the points into two sets based on their orientation
    for (int i = 0; i < n; i++) {
        if (orientation(p1, pFarthest, points[i]) == 2)
            leftSet.push_back(points[i]);
        else if (orientation(pFarthest, pn, points[i]) == 2)
            rightSet.push_back(points[i]);
    }

    // Recursively find the convex hull of the left and right sets
    findHull(leftSet, leftSet.size(), p1, pFarthest, hull);
    findHull(rightSet, rightSet.size(), pFarthest, pn, hull);
}

// Function to compute the convex hull of a set of points
std::vector<Point> computeConvexHull(std::vector<Point>& points) {
    int n = points.size();
    if (n < 3)
        return {}; // Not enough points to form a convex hull

    std::vector<Point> hull;
    int min_x = 0, max_x = 0;

    // Find the point with the minimum and maximum x-coordinates
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[min_x].x)
            min_x = i;
        if (points[i].x > points[max_x].x)
            max_x = i;
    }

    const Point& p1 = points[min_x];
    const Point& pn = points[max_x];
    hull.push_back(p1);

    // If p1 and pn are distinct points, add pn to the hull
    if (p1.x != pn.x || p1.y != pn.y)
        hull.push_back(pn);

    std::vector<Point> leftSet, rightSet;

    // Partition the points into two sets based on their orientation
    for (int i = 0; i < n; i++) {
        if (orientation(p1, pn, points[i]) == 2)
            leftSet.push_back(points[i]);
        else if (orientation(pn, p1, points[i]) == 2)
            rightSet.push_back(points[i]);
    }

    // Recursively find the convex hull of the left and right sets
    findHull(leftSet, leftSet.size(), p1, pn, hull);
    findHull(rightSet, rightSet.size(), pn, p1, hull);

    return hull;
}

int main() {
    std::vector<Point> points1 = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3} };
    std::vector<Point> convexHull1 = computeConvexHull(points1);

    std::cout << "Convex Hull Points 1:\n";
    for (const auto& point : convexHull1) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }
    std::cout << "\n";

    std::vector<Point> points2 = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {1, 3}, {3, 1} };
    std::vector<Point> convexHull2 = computeConvexHull(points2);

    std::cout << "Convex Hull Points 2:\n";
    for (const auto& point : convexHull2) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }
    std::cout << "\n";

    std::vector<Point> points3 = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 1}, {1, 3}, {3, 1}, {3, 3} };
    std::vector<Point> convexHull3 = computeConvexHull(points3);

    std::cout << "Convex Hull Points 3:\n";
    for (const auto& point : convexHull3) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }
    std::cout << "\n";

    std::vector<Point> points4 = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {1, -1}, {3, -1} };
    std::vector<Point> convexHull4 = computeConvexHull(points4);

    std::cout << "Convex Hull Points 4:\n";
    for (const auto& point : convexHull4) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }
    std::cout << "\n";

    return 0;
}
