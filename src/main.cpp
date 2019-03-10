#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>

void thread_function(std::vector<int> v, int &acum)
{
    for (int i = 0; i < v.size(); i++){
        acum += v[i] * v[i];
    }
}
int main()  
{
    // initialize random test vectors
    std::vector<int> v0;
    for (int i = 0; i < 100000; i++){
        v0.push_back(rand()%100);
    }

    std::vector<int> v1;
    for (int i = 0; i < 100000; i++){
        v1.push_back(rand()%100+1000);
    }

    // Serial Implemention
    int acum_0_s = 0;
    int acum_1_s = 0;
    std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
    thread_function(v0,acum_0_s);
    thread_function(v1,acum_1_s);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();

    // Threaded Implementation
    int acum_0 = 0;
    int acum_1 = 0;
    t0 = std::chrono::high_resolution_clock::now();
    std::thread threadObj1(thread_function,v0,std::ref(acum_0));
    std::thread threadObj2(thread_function,v1,std::ref(acum_1));
    t1 = std::chrono::high_resolution_clock::now();
    threadObj1.join();    
    threadObj2.join();   
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();

    // Compare execution time and make sure results are the same
    std::cout << "Serial Implementation: " << duration << " ans = " << acum_0_s << "," << acum_1_s <<std::endl;
    std::cout << "Threaded Implementation: " << duration2 << " ans = " << acum_0 << "," << acum_1 <<std::endl;


    return 0;
}