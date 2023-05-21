#include <iostream>
#include <vector>
#include <set>

struct Point {
    double x;
    double y;

    // Define the less than operator for Point
    bool operator<(const Point& other) const {
        if (x < other.x)
            return true;
        if (x > other.x)
            return false;
        return y < other.y;
    }
};

// Function to check if three points are collinear
bool areCollinear(const Point& p1, const Point& p2, const Point& p3) {
    return (p2.y - p1.y) * (p3.x - p2.x) == (p3.y - p2.y) * (p2.x - p1.x);
}

// Function to check if all points lie on the same side of the line
bool arePointsOnSameSide(const Point& p1, const Point& p2, const Point& linePoint1, const Point& linePoint2) {
    double a = linePoint2.y - linePoint1.y;
    double b = linePoint1.x - linePoint2.x;
    double c = linePoint1.x * linePoint2.y - linePoint1.y * linePoint2.x;

    bool allPointsOnSameSide = true;
    for (const Point& p : { p1, p2 }) {
        double result = a * p.x + b * p.y - c;
        if (result != 0) {
            if (allPointsOnSameSide) {
                allPointsOnSameSide = (result > 0);
            }
            else {
                return false;  // Points on different sides
            }
        }
    }

    return true;  // All points are on the same side
}

// Function to find the convex hull of a set of points
std::vector<Point> findConvexHull(const std::vector<Point>& points) {
    std::vector<Point> convexHull;
    std::set<Point> uniquePoints;  // Store unique convex hull points

    int n = points.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool allPointsOnSameSide = true;

            for (int k = 0; k < n; ++k) {
                if (k != i && k != j) {
                    if (!arePointsOnSameSide(points[i], points[j], points[k], points[(k + 1) % n])) {
                        allPointsOnSameSide = false;
                        break;
                    }
                }
            }

            if (allPointsOnSameSide) {
                // Check if the line segment is part of the convex hull
                bool isValidSegment = true;
                for (int k = 0; k < n; ++k) {
                    if (k != i && k != j) {
                        if (areCollinear(points[i], points[j], points[k])) {
                            isValidSegment = false;
                            break;
                        }
                    }
                }

                if (isValidSegment) {
                    uniquePoints.insert(points[i]);
                    uniquePoints.insert(points[j]);
                }
            }
        }
    }

    // Convert the set of unique points to a vector
    convexHull.assign(uniquePoints.begin(), uniquePoints.end());

    return convexHull;
}

int main() {
    std::vector<Point> points1 = { {0, 0}, {1, 1}, {2, 2}, {3, 1}, {2, 0} };
    std::vector<Point> points2 = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4} };
    std::vector<Point> points3 = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {0, 3} };
    std::vector<Point> points4 = { {0, 0}, {1, 2}, {3, 1}, {2, 3}, {4, 4}, {1, 4}, {3, 2}, {4, 1} };

    std::vector<Point> convexHull1 = findConvexHull(points1);
    std::vector<Point> convexHull2 = findConvexHull(points2);
    std::vector<Point> convexHull3 = findConvexHull(points3);
    std::vector<Point> convexHull4 = findConvexHull(points4);

    std::cout << "Convex Hull Points 1:\n";
    for (const Point& p : convexHull1) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    std::cout << "Convex Hull Points 2:\n";
    for (const Point& p : convexHull2) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    std::cout << "Convex Hull Points 3:\n";
    for (const Point& p : convexHull3) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    std::cout << "Convex Hull Points 4:\n";
    for (const Point& p : convexHull4) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
