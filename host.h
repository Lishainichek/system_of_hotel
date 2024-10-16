//
// Created by Fedor Orlov on 10/6/24.
//

#ifndef HOST_H
#define HOST_H

#include <QWidget>
#include<QPaintEvent>
#include<vector>
#include<QPushButton>
#include<chrono>
#include<thread>
#include<QLabel>
#include<QTimer>
#include<vector>
#include<QPainter>
#include<QPainter>
#include<QApplication>
#include<QPixmap>
 #include<string>
#include<map>
#include<iostream>
#include <utility>
 #include<vector>
#include<QIcon>
#include<QString>
#include<QLineEdit>
 #include<random>
//#include "Room.h"

extern std::mt19937 rnd;

QT_BEGIN_NAMESPACE
namespace Ui { class host; }
QT_END_NAMESPACE















#include <QtWidgets>
#include <QObject>
#include <QThread>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class Animation : public QObject {
    Q_OBJECT

public:
    explicit Animation(QObject *parent = nullptr) : QObject(parent) {}
    Animation(std::vector <QPoint>& v, QObject *parent = nullptr) : QObject(parent) {
        points = v;
    }
    public slots:
        void startAnimation(QLabel *&targetObject, std::vector <QGraphicsItem*> &item) {
        QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup;
        for(int i = 1; i < points.size(); ++i){
            animation = new QPropertyAnimation(targetObject, "pos");
            int dur = (int) (fmax(abs(points[i-1].x() - points[i].x()), abs(points[i-1].y() - points[i].y())));
            animation->setDuration(dur * 2);
            animation->setStartValue(points[i-1]);
            animation->setEndValue(points[i]);
            animationGroup->addAnimation(animation);
        }
        animationGroup->start();

        // animationGroup->deleteLater();

        connect(animation, &QSequentialAnimationGroup::finished, this, &Animation::animationFinished);
    }
    signals:
        void animationFinished();

private:
    std::vector <QPoint> points;
    QPropertyAnimation *animation;
    QPropertyAnimation *process;

    //ура
};
class But;
class But1;






class Guest {
public:
    Guest(const std::string& name, int cur_day, int duration, int kol_guests, int type)
            : name_(name), cur_day_(cur_day), duration_(duration), kol_guests_(kol_guests), wanted_type(type) {}
    std::string getName() const { return name_; }
    int getCurDay() const { return cur_day_; }
    int getDuration() const { return duration_; }
    int getKolGuests() const {return kol_guests_; }
    int get_wanted_type() {
        return wanted_type;
    }
private:

    std::string name_;
    int kol_guests_;
    int cur_day_;
    int duration_;
    int wanted_type;

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
        if (kol_seats_ < guest->getKolGuests()) {
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
        int end_day = guest->getDuration();
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
    std::vector<Guest*> guests_;
public:
    int price_;
    int number_of_guests_;
    bool occupancy_[30]; ;

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





struct room {
    int num;
    int profit = 0;
    bool is_empty = 0;
    int type;
    std::pair<int, int> from_to;
    std::string cur_guest = "None";
    std::map<std::string, int> profit_from_guest;
    std::vector<std::string> guests;



    QLabel* page_of_room;
    But* num_of_room;
    QPushButton* button_for_foto;
    But1* back;
    QLabel* line_for_guest;
    QLabel* line_for_dates;
    QLabel* line_for_type;
    QLabel* line_for_profit;
    QLabel* line_for_num;
    QLineEdit* line_for_time;
    Guest* guest;
    Room* rom;
    std::vector<std::vector<Animation>>* coridors;

    QLabel* line_bool;



    // QIcon* foto;
};

class But : public QPushButton {
    Q_OBJECT
public:
    But(QWidget* parrent = nullptr) {setParent(parrent);}
    Q_SLOT void pressed() {
        room.page_of_room->show();
        update();
    }
    void setRoom(room room_) {
        room = std::move(room_);
    }
    room room;
};



class But1 : public QPushButton {
    Q_OBJECT
public:
    But1(QWidget* parrent = nullptr) {setParent(parrent);}
    Q_SLOT void pressed() {
        room.page_of_room->hide();
        update();
    }
    void setRoom(room room_) {
        room = std::move(room_);
    }
    room room;
};


class host : public QWidget {
Q_OBJECT

public:
    explicit host(QWidget *parent = nullptr);
    ~host() override;
    QLabel* background;
    std::vector<room*> rooms;
    QPushButton* help;
    QLineEdit* line_for_time_and_date;
    QPushButton* play;
    int current_hours;
    int current_day;
    int current_month;
    int current_year;
    int count = 0;
    void show_Label(room* room);
private:
    Ui::host *ui;
    void add_time();
    void update();
    void add_guest();
    void start_programm();
    void do_animation();
    void start();
    void clear();
};


#endif //HOST_H
