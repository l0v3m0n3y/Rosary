# Rosary
api for therosaryapi.cf site provides various endpoints to access rosary prayers for different days and occasions
# main
```cpp
#include "Rosary.h"
#include <iostream>

int main() {
   Rosary api;
    auto list = api.get_list().then([](json::value result) {
        std::cout << result<< std::endl;
    });
    list.wait();
    
    return 0;
}
```

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```
