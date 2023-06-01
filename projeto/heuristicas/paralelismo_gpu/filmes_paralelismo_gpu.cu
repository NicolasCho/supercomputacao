#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/transform_iterator.h>
#include <thrust/functional.h>
#include <thrust/reduce.h>
#include <thrust/execution_policy.h>
#include <vector>

struct knapsack_functor
{
    int* start_times;
    int* end_times;
    int* categories;
    int* L;
    int* results;
    int num_films;
    int num_categories;

    knapsack_functor(int* _start_times, int* _end_times, int* _categories, int* _L, int* _results, int _num_films, int _num_categories)
        : start_times(_start_times), end_times(_end_times), categories(_categories), L(_L), results(_results), num_films(_num_films), num_categories(_num_categories) {}

    __host__ __device__
    int operator()(const thrust::tuple<int, int>& t)
    {
        int i = thrust::get<0>(t);
        int c = thrust::get<1>(t);

        int max_count = 0;
        for (int k = 0; k < i; k++) {
            if (end_times[k] <= start_times[i] && results[k * num_categories + c - 1] <= L[c - 1]) {
                max_count = max(max_count, results[k * num_categories + c - 1] + 1);
            } else {
                max_count = max(max_count, results[k * num_categories + c - 1]);
            }
        }
        return max_count;
    }
};

int knapsack(int num_films, int num_categories, int* start_times, int* end_times, int* categories, int* L)
{
    thrust::device_vector<int> d_start_times(start_times, start_times + num_films);
    thrust::device_vector<int> d_end_times(end_times, end_times + num_films);
    thrust::device_vector<int> d_categories(categories, categories + num_films);
    thrust::device_vector<int> d_L(L, L + num_categories + 1);

    thrust::device_vector<int> d_results(num_films * num_categories, 0);
    thrust::device_vector<int> d_updated_results(num_films * num_categories, 0);

    thrust::counting_iterator<int> film_iter(0);
    thrust::counting_iterator<int> cat_iter(0);

    thrust::zip_iterator<thrust::tuple<thrust::counting_iterator<int>, thrust::counting_iterator<int>>> iter =
        thrust::make_zip_iterator(thrust::make_tuple(film_iter, cat_iter));

    thrust::transform(iter, iter + (num_films * num_categories),
                      d_updated_results.begin(), knapsack_functor(thrust::raw_pointer_cast(d_start_times.data()),
                                                                   thrust::raw_pointer_cast(d_end_times.data()),
                                                                   thrust::raw_pointer_cast(d_categories.data()),
                                                                   thrust::raw_pointer_cast(d_L.data()),
                                                                   thrust::raw_pointer_cast(d_results.data()),
                                                                   num_films, num_categories));

    thrust::copy(d_updated_results.begin(), d_updated_results.end(), d_results.begin());

    int max_value = thrust::reduce(thrust::device, d_results.begin(), d_results.end(), 0, thrust::maximum<int>());

    return max_value;
}

int main(int argc, char* argv[])
{
    int N = 0;
    int M = 0;

    std::cin >> N >> M;

    // Vector initialization
    std::vector<int> start_times_dev(N);
    std::vector<int> end_times_dev(N);
    std::vector<int> categories_dev(N);
    std::vector<int> L_dev(M + 1); // Increase the size by 1 to account for category 0

    // Preencher vetor de categorias
    int n_filmes_categoria;
    for (int i = 0; i < M; i++) {
        std::cin >> n_filmes_categoria;
        L_dev[i + 1] = n_filmes_categoria; // Use indexing instead of push_back()
    }

    // Preencher vetores de horarios (inicio e fim)
    int inicio, fim, categoria;
    for (int i = 0; i < N; i++) {
        std::cin >> inicio;
        std::cin >> fim;
        std::cin >> categoria;
        start_times_dev[i] = inicio;     
        end_times_dev[i] = fim;          
        categories_dev[i] = categoria;   
    }

    int max_value = knapsack(N, M, start_times_dev.data(), end_times_dev.data(), categories_dev.data(), L_dev.data());

    std::cout << "Max Value: " << max_value << std::endl;

    return 0;
}
