#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <ctime>

enum class Food {
    PIZZA,
    SUP,
    STEAK,
    SALAD,
    SUSHI
};

std::deque<int> orders;
std::deque<int> delivery;

std::string order_to_str(int order){
    switch (order){
        case 0: 
            return "PIZZA";
        case 1: 
            return "SOUP";
        case 2: 
            return "STEAK";
        case 3: 
            return "SALAD";
        case 4: 
            return "SUSHI";
        default: 
            return "Wrong order!";
    }
};

std::mutex delivery_accsess;
std::mutex order_accsess;

void take_order(){
    std::srand(time(nullptr));
    int count = 0;
    while(count < 10){
        int order_time = std::rand()%6 + 5;

        std::this_thread::sleep_for(std::chrono::seconds(order_time));

        int order = std::rand()%5;

        order_accsess.lock();
        orders.push_back(order);
        order_accsess.unlock();

        std::cout << order_to_str(order) << " in order" << std::endl;
        ++count;
    }
};

void cooking(){
    std::srand(time(nullptr));
    int count = 0;
    while (count < 10){   
        int cooking_time = std::rand()%11 + 5;
        std::this_thread::sleep_for(std::chrono::seconds(cooking_time));

        order_accsess.lock();
        int order = orders.front();
        delivery_accsess.lock();
        delivery.push_back(order);
        std::cout << order_to_str(order) << " is cooked." << std::endl;
        orders.pop_front();
        delivery_accsess.unlock(); 
        order_accsess.unlock();
        ++count;
    }
};

void courier(){
    int count = 0;
    while(count < 10){
        std::this_thread::sleep_for(std::chrono::seconds(30));
        delivery_accsess.lock();
        std::cout << order_to_str(delivery.front()) << " delivered." << std::endl;
        delivery.pop_front();
        delivery_accsess.unlock();
        ++count;
    }
};


int main(int, char**){
    std::cout << "Hello, from 28_3_kitchen_online!\n";

    std::thread order(take_order);
    std::thread kitchen(cooking);
    kitchen.detach();
    std::thread delivery(courier);
    
    order.join();
    if(kitchen.joinable()) kitchen.join();
    delivery.join();
}
