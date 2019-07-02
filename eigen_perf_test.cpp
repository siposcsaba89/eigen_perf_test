#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;
using namespace Eigen;

int main()
{
    const vector<size_t> num_mat_multiplication = { 10000, 100000, 1000000 };
    for (auto num_iter : num_mat_multiplication)
    {
        auto start_t = steady_clock::now();
        Matrix<float, 6, 1> b = Matrix<float, 6, 1>::Random();
        Matrix<float, 6, 6> A = Matrix<float, 6, 6>::Zero();
        for (size_t i = 0; i < num_iter; ++i)
        {
            Matrix<float, 2, 6> tmp = Matrix<float, 2, 6>::Random();
            A += tmp.transpose() * tmp;
        }
        Matrix<float, 6, 1> x = A.llt().solve(b);
        duration<double> diff = steady_clock::now() - start_t;
#if __clang__
        cout << "compiler is Clang, version " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << endl;
#elif _MSC_VER
        cout << "compiler is MSVC, version " << _MSC_FULL_VER << endl;
#elif __GNUC__
        std::cout << "compiler is GNUC(gcc), version " << __GNUC__ << "." << __GNUC_MINOR__ << endl;
#endif
        cout << num_iter << " iteration took " << diff.count() << endl;
    }
    return 0;
}