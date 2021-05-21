#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string.h>
#include <iostream>

using namespace std;

/* Função que retorna o maior valor encontrado no vetor */
int max(int *numbers, int length)
{
    int max = INT32_MIN;

    for (int i = 0; i < length; i++)
    {
        int number = numbers[i];
        if (number > max)
            max = number;
    }

    return max;
}

/* Counting Sort */
int *counting_sort(int *numbers, int length, int max)
{
    ++max; //Incrementa-se o max para criar um vetor de frequência com índices de 0 até max

    int *frequency = new (nothrow) int[max]; // Criando o vetor de frequência (contagem)
    int *result = new (nothrow) int[length]; // Criando o vetor de saída

    /* Inicializando os dois vetores com o valor 0 */
    for (int i = 0; i < max; i++)
    {
        frequency[i] = 0;
        if (i < length)
        {
            result[i] = 0;
        }
    }

    /* Realizando a contagem dos valores presentes no vetor de entrada chamado numbers */
    for (int i = 0; i < length; i++)
    {
        frequency[numbers[i]]++;
    }

    /* Somando cada valor do vetor de frequência (contagem) com o seu anterior */
    for (int i = 1; i < max; i++)
    {
        frequency[i] = frequency[i - 1] + frequency[i];
    }

    /* 
        Colocando cada valor presente no vetor de entrada em 
        seu respectivo índice no vetor de saída
    */
    for (int i = length - 1; i > -1; i--)
    {
        --frequency[numbers[i]]; //Decrementa-se o valor 
        //Insere o número no índice indicado pelo vetor de frequência
        result[frequency[numbers[i]]] = numbers[i]; 
    }

    /* Por fim, retorna o vetor ordenado */
    return result;
}

/* Função que gera um número aleatoriamente entre um determinado intervalo fechado */
int generate_random_number_between(int min, int max)
{
    int number;

    number = (rand() % (max - min + 1)) + min;

    return number;
}

/* Função que cria um array com n números aleatórios de um determinado intervalo fechado */
int *create_array(int size, int min, int max)
{
    int *array = new (nothrow) int[size];

    for (int i = 0; i < size; i++)
        array[i] = generate_random_number_between(min, max);

    return array;
}

void print_array(int *array, int length, bool sorted)
{
    cout << "Array" << (sorted ? " ordenado" : " inicial") << ": [" << array[0];
    for (int i = 1; i < length; i++)
        cout << ", " << array[i];
    cout << "]" << endl;
}

/* 
    Função que calcula o tempo decorrido de uma determinada função. 

    Neste caso, foi para calcular o tempo de execução do counting sort
    para ordenar um determinado vetor passado como parâmetro.
*/
void calculate_elapsed_time(int *(*f)(int *, int, int), int *array, int length, int max)
{
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    int *sorted_array = f(array, length, max);
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

    cout << "------------------------------------------------------" << endl;
    print_array(array, length, false);
    print_array(sorted_array, length, true);
    cout << "Maior valor dentro do array: " << max << endl;

    uint64_t execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    if (execution_time != 0)
    {
        cout << "Tempo de execução: " << execution_time << " milissegundos";
    }
    else
    {
        execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

        if (execution_time != 0)
        {
            cout << "Tempo de execução: " << execution_time << " microsegundos";
        }
        else
        {
            execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

            cout << "Tempo de execução: " << execution_time << " nanosegundos";
        }
    }
    cout << endl
         << "------------------------------------------------------" << endl;
}

int main()
{
    srand((unsigned)time(0));

    int length, min_value, max_value;

    while (cin >> length)
    {
        cout << "Valor mínimo do array: ";
        cin >> min_value;

        cout << "Valor máximo do array: ";
        cin >> max_value;

        int *array = create_array(length, min_value, max_value);

        calculate_elapsed_time(counting_sort, array, length, max(array, length));
    }

    return 0;
}
