#include <chrono>

template <class T>
void Stopwatch<T>::start()
{
	start_time = clock::now();
}

template <class T>
int Stopwatch<T>::elapsed()
{
	auto elapsed_time = std::chrono::duration_cast<T>(clock::now() - start_time);
	return elapsed_time.count();
}

template <class T>
int Stopwatch<T>::restart()
{
	auto elapsed_time = elapsed();
	start_time = clock::now();
	return elapsed_time;
}
