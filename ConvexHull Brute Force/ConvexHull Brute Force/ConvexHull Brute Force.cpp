#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    double x, y;

    // Overloading the equality operator to compare two points
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // Overloading the inequality operator to compare two points
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

// Function to compute the cross product of vectors (p1 - p0) and (p2 - p0)
double crossProduct(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

// Function to check if a point pk is inside the triangle formed by points pi, pj, and ph
bool isInsideTriangle(const Point& pi, const Point& pj, const Point& ph, const Point& pk) {
    // Compute the cross products
    double cross1 = crossProduct(pi, pj, pk);
    double cross2 = crossProduct(pj, ph, pk);
    double cross3 = crossProduct(ph, pi, pk);

    // Check if pk is inside the triangle or on its boundary
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}

// Function to compute the convex hull using a brute force approach
std::vector<Point> convexHull(std::vector<Point>& points) {
    std::vector<Point> hull;

    // Iterate over all points
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < points.size(); ++j) {
            if (i == j) continue;

            bool isInside = true;
            // Check if all other points are on the same side of the line formed by points i and j
            for (size_t k = 0; k < points.size(); ++k) {
                if (k == i || k == j) continue;

                // Compute the cross product to determine if point k is on the same side
                if (crossProduct(points[i], points[j], points[k]) > 0) {
                    isInside = false;
                    break;
                }
            }

            // If all other points are on the same side, add points i and j to the hull
            if (isInside) {
                bool duplicate = false;
                // Check if points i and j are already present in the hull
                for (const auto& p : hull) {
                    if (p == points[i] || p == points[j]) {
                        duplicate = true;
                        break;
                    }
                }
                // Add points i and j to the hull if they are not duplicates
                if (!duplicate) {
                    hull.push_back(points[i]);
                    hull.push_back(points[j]);
                }
            }
        }
    }

    // Sort and remove duplicate points from the hull
    std::sort(hull.begin(), hull.end(), [](const Point& a, const Point& b) {
        if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
        });
    hull.erase(std::unique(hull.begin(), hull.end()), hull.end());

    return hull;
}

int main() {
    // Define the input points
    std::vector<Point> points = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {2, 0}, {3, 1}, {3, -1} };

    // Compute the convex hull
    std::vector<Point> hull = convexHull(points);

    // Print the points in the convex hull
    for (const auto& p : hull) {
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }

    return 0;
}
