// Copyright 2022 UNN-IASR
#include <thread>
#include <cstdlib> 
#include <iostream> 
#include "task.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    int OTP = 10;
    int Current;
    int Nym = 0;
    int Lenght = 10; //максимальная длина очереди
    int prtime = 10; //скорость обработки товара на кассе
    int averagepr = 10; //среднее колличество продуктов в тележке
    int threads_count = 3; //количество касс
    double client_intensivity = (double)1 / Lenght; //интенсивность потока покупателей
    int TOTAL = 5000;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Shop shop = Shop(threads_count, Lenght, prtime);
    shop.Start();
    int Per_time_unit;
    int product_count;

    while (std::chrono::duration_cast <std::chrono::milliseconds> (std::chrono::steady_clock::now() - begin).count() < TOTAL) {
        Per_time_unit = rand() % int(2 * OTP * client_intensivity);
        for (int i = 0; i < Per_time_unit; i++) {
            product_count = rand() % (2 * averagepr);
            Client client = Client(Nym, product_count);
            shop.add_to_queue(client);
            Nym++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(OTP));
    }
    shop.Stop();

    int sr = shop.stats.queue / shop.stats.observations_count;
    int me = shop.stats.wait / shop.stats.served;
    double re = (double)shop.stats.rejected / (shop.stats.served + shop.stats.rejected);
    double rel = 1 - (double)shop.stats.rejected / (shop.stats.served + shop.stats.rejected);
    double cl = client_intensivity * (1 - (double)shop.stats.rejected / (shop.stats.served + shop.stats.rejected));

    std::cout << "1) Колличество обслуженных клиентов: " << shop.stats.served << "\n";
    std::cout << "2) Колличество необслуженных клиентов: " << shop.stats.rejected << "\n";
    std::cout << "3) Средняя длина очереди: " << sr << "\n";
    std::cout << "4) Среднее ожидание клиента : " << me << "\n";
    std::cout << "5) Вероятность отказа: " << re << "\n";
    std::cout << "6) Относительную пропускная способность магазина: " << rel << "\n";
    std::cout << "7) Абсолютная пропускная способность: " << cl << std::endl;

    return 0;

}
