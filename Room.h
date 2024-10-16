//
// Created by Fedor Orlov on 10/8/24.
//

#ifndef ROOM_H
#define ROOM_H
// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <random>
// #include <chrono>
// #include <thread>
class Guest {
public:
    Guest(const std::string& name, int cur_day, int duration, int kol_guests)
            : name_(name), cur_day_(cur_day), duration_(duration), kol_guests_(kol_guests) {}

    std::string getName() const { return name_; }
    int getCurDay() const { return cur_day_; }
    int getDuration() const { return duration_; }
    int getKolGuests() const {return kol_guests_; }
private:

    std::string name_;
    std::vector <std::string> guests;
    int kol_guests_;
    int cur_day_;
    int duration_;

};
class Room {
public:
    Room(int price, int kol_seats) : price_(price), kol_seats_(kol_seats), number_of_guests_(0) {
        std::fill(std::begin(occupancy_), std::end(occupancy_), false);
    }
    virtual ~Room() {
        for (Guest* guest : guests_) {
            delete guest;
        }
    }
    bool check(Guest* guest) {
        int start_day = guest->getCurDay();
        int end_day = start_day + guest->getDuration();
        //std::cout << "check" << kol_seats_ << guest->getKolGuests();
        if (kol_seats_ < guest->getKolGuests()) {
            //std::cout << "check " << kol_seats_ << guest->getKolGuests() << std::endl;
            return true;
        }
        for (int day = start_day; day < end_day; ++day) {
            if (occupancy_[day]) {
                return false; // комната занята
            }
        }
        return true; // свободна
    }
    void add_guest(Guest* guest) {
        int start_day = guest->getCurDay();
        int end_day = start_day + guest->getDuration();
        for (int day = start_day; day < end_day; ++day) {
            occupancy_[day] = true; // дни заняты
        }
        guests_.push_back(guest);
        number_of_guests_++;
    }


    void delete_guest(Guest* guest) {
        auto it = std::find(guests_.begin(), guests_.end(), guest);
        if (it != guests_.end()) {
            int start_day = guest->getCurDay();
            int end_day = start_day + guest->getDuration();
            for (int day = start_day; day < end_day; ++day) {
                occupancy_[day] = false; // освобождаю дни
            }
            guests_.erase(it);
            number_of_guests_--;
        }
    }

    int getPrice() const { return price_; }

private:
    int price_;
    int number_of_guests_;
    bool occupancy_[30]; ;
    std::vector<Guest*> guests_;
    int rooms_rate[30];
    int kol_seats_;

};
class Luxury : public Room {
public:
    Luxury(int price = 5000) : Room (price, 3) {}
};
class Semi_luxury : public Room {
public:
    Semi_luxury(int price = 4500) : Room (price, 2) {}
};
class Single : public Room {
public:
    Single (int price = 4000) : Room (price, 1) {}
};
class Double_simple : public Room {
public:
    Double_simple (int price = 3500) : Room (price, 2) {}
};
class Double_with_sofa : public Room {
public:
    Double_with_sofa (int price = 2500) : Room (price, 2) {}
};
int randomInRange(int min, int max) {
    static std::random_device rd; // получаю случайное значение
    static std::mt19937 gen(rd()); // инициализирую генератор
    std::uniform_int_distribution<> dis(min, max); // определяю равномерное распределение
    return dis(gen);
}
Guest* createRandomGuest(int day) {
    std::string names[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    std::string name = names[randomInRange(0, 4)];
    int duration = randomInRange(1, 5); //  от 1 до 5 дней
    int kol_guests = randomInRange(1, 3);
    return new Guest(name, day, duration, kol_guests);
}
std::pair<Room*,int> createRandomRoom() {
    int roomType = randomInRange(0, 4); // случайный выбор типа комнаты
    switch (roomType) {
        case 0: return std::pair <Room*, int> (new Luxury, 0);
        case 1: return  std::pair <Room*, int> (new Semi_luxury, 1);
        case 2: return std::pair <Room*, int> (new Single, 1) ;
        case 3: return std::pair <Room*, int> (new Double_simple, 1);
        case 4: return std::pair <Room*, int> (new Double_with_sofa, 1);
        //default: return nullptr;
    }
}
#endif //ROOM_H
