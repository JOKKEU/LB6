#include <iostream>
#include <cstdlib>
#include <ctime>

int** create_weighted_adjacency_matrix(size_t size)
{
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (!matrix)
    {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[i] = (int*)malloc(size * sizeof(int));
        if (!matrix[i])
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            return nullptr;
        }
    }

    // Инициализация матрицы нулями
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            matrix[i][j] = 0;
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            matrix[i][j] = rand() % 4;
            matrix[j][i] = matrix[i][j];
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[i][i] = 0;
    }

    return matrix;
}

void print_matrix(int** matrix, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void free_matrix(int** matrix, size_t size)
{
    if (!matrix)
    {
        return;
    }
    else
    {
        for (size_t i = 0; i < size; ++i)
        {
            free(matrix[i]);
        }
        free(matrix);
    }
}

void select_random_verticles(size_t size, int* v1, int* v2)
{
    *v1 = rand() % size;
    *v2 = rand() % size;
    while (*v2 == *v1)
    {
        *v2 = rand() % size;
    }
}

int** contraction_of_a_graph_edge(int** matrix, size_t size)
{
    int v1, v2;
    select_random_verticles(size, &v1, &v2);

    for (size_t i = 0; i < size; ++i)
    {
        if (i != v1 && i != v2)
        {
            matrix[v1][i] += matrix[v2][i];
            matrix[i][v1] = matrix[v1][i];
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[v2][i] = 0;
        matrix[i][v2] = 0;
    }

    return matrix;
}

void start()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    std::cout << "Enter size matrix (type size_t) : ";
    size_t size;
    std::cin >> size;
    if (!size)
    {
        return;
    }
    int** matrix = create_weighted_adjacency_matrix(size);
    if (!matrix)
    {
        std::cerr << "Error allocate\n";
        return;
    }
    print_matrix(matrix, size);
    std::cout << std::endl;
    contraction_of_a_graph_edge(matrix, size);
    std::cout << "after contraction_of_a_graph_edge\n";
    print_matrix(matrix, size);
    free_matrix(matrix, size);
}

int main() {
    start();
}
