//
// Created by Fedor Orlov on 10/6/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_host.h" resolved

#include "host.h"
#include "ui_host.h"
std::vector<std::string> types({"LUX", "SEMI_LUX", "SINGLE", "DOUBLE-SIMPLE", "SIMPLE"});
std::vector<std::string> names({"Vova", "Sergey", "John", "Fred", "Suzy", "Stella", "Morgan", "Katy"});
std::vector<std::string> surnames({"Smit", "Freeman", "Costello", "Muller", "Messi"});
std::mt19937 rnd(std::time(nullptr));
bool stop = 0;
long double sum = 0;
int free_ = 0;
int first = 0;
int second = 0;
int third = 0;
int fourth = 0;
int count_of_done = 0;
int count_of_gotten;

bool fifty_fifty() {
    return rnd() % 2;
}
host::host(QWidget *parent) :
    QWidget(parent), ui(new Ui::host) {
    ui->setupUi(this);
    this -> setGeometry(0, 0, 1280, 900);

    this -> current_day = 1;
    this -> current_hours = 0;
    this -> current_month = 9;
    this -> current_year = 2024;





    QIcon* icon1 = new QIcon("/Users/fedororlov/Desktop/fedor/fedor/system_of_hotels/4146-03-2000-roo-LTMO.jpg.thumb.768.768.jpg");
    QIcon* icon2 = new QIcon("/Users/fedororlov/Desktop/fedor/fedor/system_of_hotels/2-Elite-Balcony-Single2.jpg");
    QIcon* icon3 = new QIcon("/Users/fedororlov/Desktop/fedor/fedor/system_of_hotels/f46badb1b7e3f599f96aebe0b032b7ac.jpg");
    QIcon* icon4 = new QIcon("/Users/fedororlov/Desktop/fedor/fedor/system_of_hotels/Deluxe-room-3-1024x683.jpg");
    QIcon* icon5 = new QIcon("/Users/fedororlov/Desktop/fedor/fedor/system_of_hotels/chambre-single-11.jpg");



    std::vector<QIcon*> arr_of_icons;
    arr_of_icons.push_back(icon1);
    arr_of_icons.push_back(icon2);
    arr_of_icons.push_back(icon3);
    arr_of_icons.push_back(icon4);
    arr_of_icons.push_back(icon5);



    background = new QLabel(this);
    background -> setStyleSheet("QLabel {background-color : #EAD8B1;}");
    background -> setFixedSize(this -> size());



    play = new QPushButton(background);

    play -> setGeometry(1200, 800, 80, 100);
    QIcon* icon_for_play = new QIcon("/Users/fedororlov/Desktop/fedor/fedor/system_of_hotels/png-clipart-computer-icons-social-media-google-play-button-social-media-angle-text.png");
    play -> setIcon(*icon_for_play);
    play -> setIconSize(play -> size());


    line_for_time_and_date = new QLineEdit(background);
    line_for_time_and_date -> setGeometry(0, 800, 1200, 100);
    line_for_time_and_date -> setStyleSheet("QLineEdit {font-size : 40px}");
    line_for_time_and_date -> setReadOnly(true);
    line_for_time_and_date -> setText("DATE:                                         "
                                      "                                           07.09.2007 12:00"
                                      );

    int count = 1;
    int cur_y = 50, cur_type = 0;
    for (int ii = 1; ii <= 5; ++ii) {
        for (int jj = 1 ;jj <= 4; ++jj) {
            room *current = new room();

            current  -> num = count;
            current -> type = cur_type;

            current -> page_of_room = new QLabel(this);
            current -> page_of_room -> setFixedSize(this -> size());
            current -> page_of_room->setFixedSize(this -> size());
            current -> page_of_room-> setStyleSheet("QLabel {background-color : #EAD8B1"
                                                 "}");
            current -> page_of_room -> hide();



            current -> num_of_room = new But(background);
            current -> num_of_room -> setGeometry((jj - 1) * 320, cur_y,  320, 100);
            current -> num_of_room -> show();
            current -> num_of_room->setRoom(*current);
            current -> num_of_room -> setText(QString::fromStdString(std::to_string(count++)));
            current -> num_of_room -> setStyleSheet("QPushButton {"
                                                 "background-color : #798645;"
                                                 "font-size : 30px;"
                                                 "color : black;"
                                                 "}");

            current -> button_for_foto = new QPushButton(current -> page_of_room);
            current -> button_for_foto -> setGeometry(0, 100, 600, 600);
            current -> button_for_foto -> setIcon(*arr_of_icons[ii - 1]);
            current -> button_for_foto -> setIconSize(current -> button_for_foto -> size());



            current -> line_for_time = new QLineEdit(current -> page_of_room);
            current -> line_for_time -> setGeometry(0, 800, 1280, 100);
            current -> line_for_time -> setStyleSheet("QLineEdit {font-size : 40px}");
            current -> line_for_time -> setReadOnly(true);
            current-> line_for_time -> setText(line_for_time_and_date -> text());



            current -> back = new But1(current -> page_of_room);
            current -> back -> setGeometry(0, 0, 400, 100);
            current -> back->setRoom(*current);
            current -> back -> setText("RETURN");
            current -> back -> setStyleSheet("QPushButton {"
                                                // "background-color : #798645;"
                                                 "color : black;"
                                                 "font-size : 40px;"
                                                 "}");

            current ->line_for_guest = new QLabel(current -> page_of_room);
            current -> line_for_guest -> setGeometry(650, 200, 700, 100);
            current ->line_for_guest -> setStyleSheet("QLabel {"
                                                    "color : black;"
                                                    "font-size : 40px;"
                                                    "}");
            current ->line_for_guest -> setText("Guest : None");




            current ->line_for_dates = new QLabel(current -> page_of_room);
            current -> line_for_dates -> setGeometry(650, 300, 700, 100);
            current ->line_for_dates -> setStyleSheet("QLabel {"
                                                    "color : black;"
                                                    "font-size : 40px;"
                                                    "}");
            current ->line_for_dates -> setText("From , To : xx.xx.xx, xx.xx.xx");


            current ->line_for_type = new QLabel(current -> page_of_room);
            current -> line_for_type -> setGeometry(650, 400, 700, 100);
            current ->line_for_type -> setStyleSheet("QLabel {"
                                                    "color : black;"
                                                    "font-size : 40px;"
                                                    "}");
            current ->line_for_type -> setText("TYPE: " + QString::fromStdString(types[current -> type]));


            current ->line_for_num = new QLabel(current -> page_of_room);
            current -> line_for_num -> setGeometry(650, 500, 700, 100);
            current ->line_for_num -> setStyleSheet("QLabel {"
                                                    "color : black;"
                                                    "font-size : 40px;"
                                                    "}");
            current -> line_for_num -> setText("ROOM: " + QString::fromStdString(std::to_string(current -> num)));


            current ->line_bool = new QLabel(current -> page_of_room);
            current -> line_bool -> setGeometry(650, 600, 700, 100);
            current ->line_bool -> setStyleSheet("QLabel {"
                                                    "color : black;"
                                                    "font-size : 40px;"
                                                    "}");
            current -> line_bool -> setText("Status : Free");



            current -> rom = new Room(1000, 5);
            current -> guest = new Guest("HUESOS", 0, 5, 3, 1);












            rooms.push_back(current);
            connect(current ->num_of_room, SIGNAL(clicked()), current -> num_of_room, SLOT(pressed()));
            connect(current->back, SIGNAL(clicked()), current->back, SLOT(pressed()));
        }
        cur_y += 150;
        cur_type++;
    }


    background -> show();
    this -> show();
    connect(play, &QPushButton::clicked, this, &host::start);

}
void host::show_Label(room* room) {
    background->hide();
}


void host::update() {
    line_for_time_and_date -> setText("DATE:                                                                                       " +
        QString::fromStdString(std::to_string(current_day))
        + "." + QString::fromStdString(std::to_string(current_month)) + "." + QString::fromStdString(std::to_string(current_year))
        + " " + QString::fromStdString(std::to_string(current_hours)) + ".00");
    for (auto ii : rooms) {
        if (ii -> rom -> occupancy_[count] == 1) {
            ii -> num_of_room -> setStyleSheet("QPushButton {"
                                                "background-color : red;"
                                                "font-size : 30px;"
                                                "color : black;"
                                                "}");
            ii -> line_for_guest -> setText("Guest " + QString::fromStdString(ii -> guest -> getName()));
            ii -> line_for_dates -> setText("From: " + QString::fromStdString(std::to_string(ii -> guest -> getCurDay())) + ".09.2007 "
                + "To: "
                + QString::fromStdString(std::to_string(ii -> guest -> getDuration()))
                + ".09.2007");
            ii -> line_bool -> setText("Status : engaged");
        } else {
            ii -> num_of_room -> setStyleSheet("QPushButton {"
                                                "background-color : #798645;"
                                                "font-size : 30px;"
                                                "color : black;"
                                                "}");
            ii -> line_for_guest -> setText("Guest : None");
            ii ->line_for_dates -> setText("From , To : xx.xx.xx, xx.xx.xx");
            ii -> line_bool -> setText("Status: Free");
        }
        ii -> line_for_time -> setText(line_for_time_and_date -> text());
    }

}


int randomInRange(int min, int max) {
    static std::random_device rd; // получаю случайное значение
    static std::mt19937 gen(rd()); // инициализирую генератор
    std::uniform_int_distribution<> dis(min, max); // определяю равномерное распределение
    return dis(gen);
}



Guest* createRandomGuest(int day) {
    std::string name = names[rnd() % 7];
    int type = rnd() % 100;
    int duration = rnd() % 8;
    if (type <= 35) {
        type = 0;
    } else if (type <= 60) {
        type = 1;
    } else if (type <= 75) {
        type = 2;
    } else if (type <= 90) {
        type = 3;
    } else {
        type = 4;
    }
    return  new Guest(name, day, day + duration, 1, type);
}
void do_animation() {

}


void host::start() {
    if (count < 5) {
        start_programm();
    } else {
        std::cout << sum << ' ' << 1.0 *  count_of_done / count_of_gotten  * 100 << '\n';
        std::cout << "first :" << 1.0 * first / 30 * 100 << '\n';
        std::cout << "second :" << 1.0 * second / 30 * 100<< '\n';
        std::cout << "third :" << 1.0 * third / 30 * 100 << '\n';
        std::cout << "fourth :" << 1.0 * fourth / 30 * 100 << '\n';

    }
}

void host::start_programm() {
    count_of_gotten++;
    free_ = 0;
    for (auto ii : rooms) {
        free_ += ii -> rom -> occupancy_[count];
    }
    auto current = createRandomGuest(count);
    int idx = 0;
    while (idx < 20) {
        if (rooms[idx] -> type >= current -> get_wanted_type() && rooms[idx] -> rom -> occupancy_[count] == 0) {
            break;
        }
        idx++;
    }
    if (idx == 20) {
        goto pin;
    }
    if (current -> get_wanted_type() == rooms[idx] -> type) {
        count_of_done++;
        int rz = current -> getDuration() - current -> getCurDay();
        if (rooms[idx] -> type == 0) {
            first += rz;
        } else if (rooms[idx] -> type == 1) {
            second += rz;
        } else if (rooms[idx] -> type == 2) {
            third += rz;
        } else {
            fourth += rz;
        }
        rooms[idx] -> guest = current;
        rooms[idx] -> rom -> add_guest(current);
        sum += rooms[idx] -> rom -> getPrice() * (current -> getDuration() - current -> getCurDay()) + ((free_ > 15) ? 500
                * (current -> getDuration() - current -> getCurDay()) : 0);
    } else {
        idx = 19;
        for (int ii = 19; ii >= 0 && rooms[ii] -> rom -> occupancy_[count] == 1; --ii) {
           idx--;
        }
        if (free_ > 17) {
            goto pin;
        }

        if (fifty_fifty()) {
            rooms[idx] -> guest = current;
            rooms[idx] -> rom -> add_guest(current);
            sum += rooms[idx] -> rom -> getPrice() * (current -> getDuration() - current -> getCurDay()) + ((free_ > 15) ? 500
                * (current -> getDuration() - current -> getCurDay()) : 0);
            count_of_done++;
            int rz = current -> getDuration() - current -> getCurDay();
            if (rooms[idx] -> type == 0) {
                first += rz;
            } else if (rooms[idx] -> type == 1) {
                second += rz;
            } else if (rooms[idx] -> type == 2) {
                third += rz;
            } else {
                fourth += rz;
            }
        }
    }
    pin:
    add_time();
    update();
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



void host::add_time() {
    current_hours += 5;
    if (current_hours >= 24) {
        count++;
        current_day++;
        current_hours %= 24;
        if (current_day > 31) {
            current_day = 1;
            current_month++;
            if (current_month == 13) {
                current_month = 1;
                current_year++;
            }
        }
    }
}



void host::clear() {
    for (auto ii : rooms) {
        if (ii -> guest ->  getDuration() == count) {
            ii -> is_empty = 0;
        }
    }
}
host::~host() {
    delete ui;
}
