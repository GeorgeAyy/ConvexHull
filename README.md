#Convex Hull Brute Force Algorithm

This algorithm finds the convex hull of a set of 2D points using a brute force approach. The convex hull is the smallest convex polygon that contains all the given points.

##Algorithm Overview:

1. Define a structure to represent a 2D point with x and y coordinates.

2. Define a function to check if three points are collinear. This function calculates the determinant of the three points' coordinates and checks if it equals zero.

3. Define a function to check if all points lie on the same side of a line. This function calculates the equation of the line using two points and checks if all other points lie on the same side of the line.

4. Define a function to find the convex hull of a set of points. This function follows a brute force approach by iterating over all pairs of points and checks if all other points lie on the same side of the line segment formed by the pair. Additionally, it checks if the line segment is part of the convex hull by verifying that no other point is collinear with the pair.

5. Initialize a set to store unique points of the convex hull.

6. Iterate over all pairs of points in the set of input points.

7. For each pair, iterate over all other points and check if they lie on the same side of the line segment.

8. If all points are on the same side, check if the line segment is part of the convex hull by verifying collinearity.

9. If the line segment is part of the convex hull, add the two points to the set of unique points.

10. Convert the set of unique points to a vector to represent the convex hull.

11. Return the vector of convex hull points.

##Example Usage:

1. Create a vector of 2D points representing the input points.

2. Call the findConvexHull function with the vector of points to obtain the convex hull.

3. The function returns a vector of points representing the convex hull.

Note: The brute force algorithm has a time complexity of O(n^3), where n is the number of input points. It is suitable for small input sizes but may become inefficient for large datasets.

# Divide and Conquer Convex Hull Algorithm

This algorithm finds the convex hull of a set of 2D points using a divide and conquer approach. The convex hull is the smallest convex polygon that contains all the given points.

## Algorithm Overview

1. Define a structure to represent a 2D point with x and y coordinates.

2. Define a function to calculate the orientation of three points (p, q, r). This function returns 0 for collinear points, 1 for clockwise orientation, and 2 for counterclockwise orientation.

3. Define a recursive function to find the convex hull given a set of points. This function takes the following parameters:
   - The vector of points.
   - The number of points.
   - The leftmost point (p1) and the rightmost point (pn) of the current subset.
   - The vector to store the convex hull points.

4. In the recursive function:
   - If the number of points is less than 1, return.
   - Find the point with the maximum distance from the line formed by p1 and pn.
   - Add the farthest point to the convex hull.
   - Partition the points into two sets based on their orientation with respect to p1 and pn.
   - Recursively find the convex hull of the left and right sets.
   - Merge the convex hulls of the left and right sets.

5. Define a function to compute the convex hull of a set of points. This function takes the following steps:
   - Check if there are enough points to form a convex hull (less than 3 points).
   - Initialize an empty vector to store the convex hull points.
   - Find the point with the minimum and maximum x-coordinates.
   - Add the minimum and maximum points to the convex hull.
   - Partition the points into two sets based on their orientation with respect to the minimum and maximum points.
   - Recursively find the convex hull of the left and right sets.
   - Merge the convex hulls of the left and right sets.
   - Return the vector of convex hull points.

## Example Usage

1. Create a vector of 2D points representing the input points.

2. Call the `computeConvexHull` function with the vector of points to obtain the convex hull.

3. The function returns a vector of points representing the convex hull.

**Note**: The divide and conquer algorithm has a time complexity of O(n log n), where n is the number of input points. It is more efficient than the brute force approach for larger datasets.

