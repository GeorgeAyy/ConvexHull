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
bool areCollinear(const Point& p1, const Point& p2, const Point& p3, int& numOperations) {
    numOperations += 3; // Increment the operation count

    double crossProduct = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return (crossProduct == 0);
}



// Function to check if all points lie on the same side of the line
bool arePointsOnSameSide(const Point& p1, const Point& p2, const Point& linePoint1, const Point& linePoint2, int& numOperations) {
    numOperations += 5; // Increment the operation count

    double a = linePoint2.y - linePoint1.y;
    double b = linePoint1.x - linePoint2.x;
    double c = linePoint1.x * linePoint2.y - linePoint1.y * linePoint2.x;

    double result1 = a * p1.x + b * p1.y - c;
    double result2 = a * p2.x + b * p2.y - c;

    if (result1 != 0 && result2 != 0) {
        if ((result2 < 0 && result1 < 0) || (result2 > 0 && result1 > 0)) {
            return true; // Points are on the same side
        }
        return false; // Points are on different sides
    }

    return false; // Points are collinear or coincident
}


// Function to find the convex hull of a set of points
std::vector<Point> findConvexHull(const std::vector<Point>& points, int& numOperations) {
    numOperations = 0;
    numOperations += 1; // Increment the operation count

    std::vector<Point> convexHull;
    std::set<Point> uniquePoints;  // Store unique convex hull points

    int n = points.size();
    for (int i = 0; i < n; i++) { //outermost loop iterates over all the points in the vector
        numOperations += 1; // Increment the operation count

        for (int j = i + 1; j < n; j++) { // j = i + 1 to avoid unnecessary iterations
            numOperations += 1; // Increment the operation count

            bool allPointsOnSameSide = true;
            for (int k = 0; k < n; k++) {
                numOperations += 1; // Increment the operation count

                if (k != i && k != j && (((k + 1) % n) != i) && (((k + 1) % n) != j)) {
                    numOperations += 1; // Increment the operation count

                    if (!arePointsOnSameSide(points[i], points[j], points[k], points[(k + 1) % n], numOperations)) {
                        allPointsOnSameSide = false;
                        break;
                    }
                }
            }

            if (allPointsOnSameSide) {
                // Check if the line segment is part of the
                bool isValidSegment = true;
                for (int k = 0; k < n; k++) {
                    numOperations += 1; // Increment the operation count

                    if (k != i && k != j) {
                        numOperations += 1; // Increment the operation count

                        if (areCollinear(points[i], points[j], points[k], numOperations)) {
                            isValidSegment = false;
                            break;
                        }
                    }
                }

                if (isValidSegment) {
                    numOperations += 4; // Increment the operation count

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
    std::vector<Point> points1 = { {0, 0}, {1, 1}, {2, 2},{3,0} };
    std::vector<Point> points2 = { { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}};
    std::vector<Point> points3 = { {0, 0}, {1, 0}, {2, 0}, {3, 3}, {0, 3} };
    std::vector<Point> points4 = { {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2}, {0, 1} };

    int numOperations = 0; // Counter for the number of operations

    std::vector<Point> convexHull1 = findConvexHull(points1, numOperations);


    std::cout << "Convex Hull Points 1:\n";
    for (const Point& p : convexHull1) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }
    std::cout << "Total Number of Operations: " << numOperations << std::endl;
    std::vector<Point> convexHull2 = findConvexHull(points2, numOperations);
    std::cout << "Convex Hull Points 2:\n";
    for (const Point& p : convexHull2) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }
    std::cout << "Total Number of Operations: " << numOperations << std::endl;
    std::vector<Point> convexHull3 = findConvexHull(points3, numOperations);
    std::cout << "Convex Hull Points 3:\n";
    for (const Point& p : convexHull3) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }
    std::cout << "Total Number of Operations: " << numOperations << std::endl;
    std::vector<Point> convexHull4 = findConvexHull(points4, numOperations);
    std::cout << "Convex Hull Points 4:\n";
    for (const Point& p : convexHull4) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }
    std::cout << "Total Number of Operations: " << numOperations << std::endl;

    return 0;
}
