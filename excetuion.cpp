#include <iostream>

int main() {
    // cin ve cout arasındaki varsayılan bağlamayı koparıyoruz
    std::cin.tie(NULL);
    
    // Birkaç işlem
    int x;
    std::cin >> x; // Bu işlem sırasında cout tamponu boşaltılmayacaktır

    std::cout << "Bu, cin.tie(NULL) kullanımı sonrası yazdırılıyor.\n";

    // cin ve cout'u yeniden bağlıyoruz
    std::cin.tie(&std::cout);

    std::cin >> x; // Bu işlem sırasında cout tamponu boşaltılacaktır
    std::cout << "Bu, cin.tie(&std::cout) kullanımı sonrası yazdırılıyor.\n";

    return 0;
}
