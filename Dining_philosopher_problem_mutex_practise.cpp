#include <iostream>
#include<mutex>


using namespace std;


// template<class L>
// void lock(L &l0,L& l1){
//     if(l0.mutex()<l1.mutex()){
//         std::unique_lock<L> u0(l0);
//         l1.lock();
//         u0.release();
//     }else{
//         std::unique_lock<L> u1(l1);
//         l0.lock();
//         u1.release();
//     }
// }


// template<class L>
// void persistent_lock(L &l0,L& l1){
//     while(true){
//         std::unique_lock<L> u0(l0);
//         if(l1.try_lock()){ //true means blocked
//             u0.release();
//             return;
//         }
//     }
// }


//std::implementation
template<class L>
void smart_lock(L &l0,L& l1){
    while(true){
        std::unique_lock<L> u0(l0);
        if(l1.try_lock()){ //true means blocked
            u0.release();
            return;
        }
    }
    std::this_thread::yield();
    {
        std::unique_lock<L> u1(l1);
        if(l0.try_lock()){ //true means blocked
            u1.release();
            return;
        }
        // l1 is unlocked
    }
}


int main()
{
    // std::lock(m1,m2);
    // std::lock(m2,m1);
    
    return 0;
}
