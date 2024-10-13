#pragma once

#include <Utils/RandomNumberGenerator.hh>
#include <FunctionBase/FunctionBase.hh>

//== NAMESPACES ===================================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================

    class ConvexityTest {
    public:
        using Vec = FunctionBase::Vec; ///< Eigen::VectorXd
        using Mat = FunctionBase::Mat; ///< Eigen::MatrixXd

        ConvexityTest() {}

        ~ConvexityTest() {}

    public:

        /** Checks whether the function given as argument is convex or not.
         * If it is not, it should output a point not satisfying the convexity property
         * before returning false.
         * \param _function a function pointer that should be any class inheriting
         * from FunctionBase, e.g. FunctionQuadraticND
         * \param min the minimum value of all tested points' coordinate
         * \param max the maximum value of all tested points' coordinate
         * \param n_evals the number of evaluations/samples tested on the
         *        line between the two points on the function */
        static bool isConvex(FunctionBase* _function, const double min = -1000., const double max = 1000., const int n_evals = 10) {
    const int n = _function->n_unknowns(); // Dimensionality of the function domain
    RandomNumberGenerator rng(min, max);   // Random number generator for generating test points

    const int max_sampling_points = 1000000;  // Max number of random points to test
    for (int sample = 0; sample < max_sampling_points; ++sample) {
        // Generate two random points x and y in the domain
        Vec x = rng.get_random_nd_vector(n);
        Vec y = rng.get_random_nd_vector(n);

        // Evaluate function at points x and y
        double fx = _function->evaluate(x);
        double fy = _function->evaluate(y);

        // Check convexity condition for several values of theta between 0 and 1
        for (int i = 1; i <= n_evals; ++i) {
            double theta = static_cast<double>(i) / n_evals; // θ ranges from 0 to 1
            Vec z = theta * x + (1.0 - theta) * y;           // Compute convex combination of x and y
            double fz = _function->evaluate(z);              // Evaluate function at point z

            // Check convexity condition: f(z) <= θ f(x) + (1-θ) f(y)
            if (fz > theta * fx + (1.0 - theta) * fy) {
                // Print path info for debugging and return false as counterexample is found
                printPathInfo(x, y, z, theta);
                return false;
            }
        }
    }

    // No counterexample found, so we assume the function is convex
    return true;
}



    private:
        static void printPathInfo(FunctionBase::Vec p1, FunctionBase::Vec p2, FunctionBase::Vec p, double t) {
            std::cout << "path: p(t) = (1 - t) * p1 + t * p2; \nwith:\n"
                      << "  p1 = (" << p1.transpose() << ")\n"
                      << "  p2 = (" << p2.transpose() << ")\n"
                      << "  p (t = " << t << ") = (" << p.transpose() << ")" << std::endl;
        }

    };




}
