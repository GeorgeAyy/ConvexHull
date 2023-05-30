#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent a point in the Cartesian plane
struct Point {
    int x, y;
};

// Function to calculate the orientation of three points (p, q, r)
// Returns 0 for collinear, 1 for clockwise, and 2 for counterclockwise
int orientation(const Point& p, const Point& q, const Point& r, int& numOperations) {
    numOperations += 7; // Increment the operation count

    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) {
        return 0; // Collinear points
    }
    return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
}

// Function to calculate the squared distance between a point and a line
int squaredDistanceToLine(const Point& p, const Point& lineStart, const Point& lineEnd, int& numOperations) {
    numOperations += 11; // Increment the operation count

    int dx = lineEnd.x - lineStart.x;
    int dy = lineEnd.y - lineStart.y;
    int numerator = std::abs(dy * p.x - dx * p.y + lineEnd.x * lineStart.y - lineEnd.y * lineStart.x);
    int denominator = dx * dx + dy * dy;
    return (numerator * numerator) / denominator;
}

// Recursive function to find the convex hull given a set of points
void findHull(const std::vector<Point>& points, int n, const Point& p1, const Point& pn, std::vector<Point>& hull, int& numOperations) {
    numOperations += 2; // Increment the operation count

    if (n < 1) {
        return;
    }

    int maxDist = -1;
    int maxIndex = -1;

    // Find the point with the maximum distance from the line (p1, pn)
    for (int i = 0; i < n; i++) {
        numOperations += 4; // Increment the operation count

        int dist = squaredDistanceToLine(points[i], p1, pn, numOperations);
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
        numOperations += 5; // Increment the operation count

        if (orientation(p1, pFarthest, points[i], numOperations) == 2) {
            leftSet.push_back(points[i]);
        }
        else if (orientation(pFarthest, pn, points[i], numOperations) == 2) {
            rightSet.push_back(points[i]);
        }
    }

    // Recursively find the convex hull of the left and right sets
    findHull(leftSet, leftSet.size(), p1, pFarthest, hull, numOperations);
    findHull(rightSet, rightSet.size(), pFarthest, pn, hull, numOperations);
}

// Function to compute the convex hull of a set of points
std::vector<Point> computeConvexHull(std::vector<Point>& points, int& numOperations) {
    numOperations += 2; // Increment the operation count

    int n = points.size();
    if (n < 3) {
        return {}; // Not enough points
    }
    std::vector<Point> hull;
    int min_x = 0, max_x = 0;

    // Find the point with the minimum and maximum x-coordinates
    for (int i = 1; i < n; i++) {
        numOperations += 4; // Increment the operation count

        if (points[i].x < points[min_x].x) {
            min_x = i;
        }
        if (points[i].x > points[max_x].x) {
            max_x = i;
        }
    }

    const Point& p1 = points[min_x];
    const Point& pn = points[max_x];

    hull.push_back(p1);
    hull.push_back(pn);

    std::vector<Point> leftSet, rightSet;

    // Partition the points into two sets based on their orientation
    for (int i = 0; i < n; i++) {
        numOperations += 5; // Increment the operation count

        if (orientation(p1, pn, points[i], numOperations) == 2) {
            leftSet.push_back(points[i]);
        }
        else if (orientation(pn, p1, points[i], numOperations) == 2) {
            rightSet.push_back(points[i]);
        }
    }

    // Recursively find the convex hull of the left and right sets
    findHull(leftSet, leftSet.size(), p1, pn, hull, numOperations);
    findHull(rightSet, rightSet.size(), pn, p1, hull, numOperations);

    return hull;
}

int main() {
    std::vector<Point> points1 = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3} };
    int numOperations1 = 0;
    std::vector<Point> convexHull1 = computeConvexHull(points1, numOperations1);

    std::cout << "Convex Hull Points 1:\n";
    for (const auto& point : convexHull1) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }

    std::cout << "Number of Operations 1: " << numOperations1 << "\n\n";

    std::vector<Point> points2 = { { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {1, 3}, {3, 1} } };
    int numOperations2 = 0;
    std::vector<Point> convexHull2 = computeConvexHull(points2, numOperations2);

    std::cout << "Convex Hull Points 2:\n";
    for (const auto& point : convexHull2) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }

    std::cout << "Number of Operations 2: " << numOperations2 << "\n\n";

    std::vector<Point> points3 = { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 1}, {1, 3}, {3, 1}, {3, 3} };
    int numOperations3 = 0;
    std::vector<Point> convexHull3 = computeConvexHull(points3, numOperations3);

    std::cout << "Convex Hull Points 3:\n";
    for (const auto& point : convexHull3) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }

    std::cout << "Number of Operations 3: " << numOperations3 << "\n\n";

    std::vector<Point> points4 = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {1, -1}, {3, -1} };
    int numOperations4 = 0;
    std::vector<Point> convexHull4 = computeConvexHull(points4, numOperations4);

    std::cout << "Convex Hull Points 4:\n";
    for (const auto& point : convexHull4) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }

    std::cout << "Number of Operations 4: " << numOperations4 << "\n\n";

    return 0;
}
