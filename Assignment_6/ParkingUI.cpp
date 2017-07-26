#include "ParkingUI.h"

void GetUsersArrangement(int NumberOfSlots, std::vector<unsigned>& arrangement) {
    std::cout << "Enter an arrangement of cars at the parking lot" << std::endl;
    unsigned car;
    for (int i = 0; i < NumberOfSlots; ++i) {
        std::cin >> car;
        arrangement.push_back(car);
    }
}

void ParkingUI::Run() {
    int NumberOfSlots;
    std::cout << "Set a number of the parking places:" << std::endl;
    std::cin >> NumberOfSlots;
    std::vector<unsigned> arrangement;
    GetUsersArrangement(NumberOfSlots, arrangement);
    CarParking parking = CarParking(arrangement);
    Rearrangings(NumberOfSlots, parking);
}

void ParkingUI::Rearrangings(int NumberOfSlots, CarParking& parking) {
    std::string user_answer;
    while (1) {
        std::cout << "Do you want to rearrange the cars (yes/no)?" << std::endl;
        std::cin >> user_answer;
        if (user_answer == "no") {
            break;
        }
        if (user_answer != "yes") {
            std::cout << "Please write 'yes' or 'no'" << std::endl;
            continue;
        }
        std::vector<unsigned> new_arrangement;
        GetUsersArrangement(NumberOfSlots, new_arrangement);
        std::cout << "Rearranging process:" << std::endl;
        parking.Rearrange(new_arrangement);
        parking.PrintLastActions(std::cout);
        std::cout << std::endl;
    }
    while (1) {
        std::cout << "Do you want to enter another arrangement (yes/no)?" << std::endl;
        std::cin >> user_answer;
        if (user_answer == "no") {
            break;
        }
        if (user_answer != "yes") {
            std::cout << "Please write 'yes' or 'no'" << std::endl;
            continue;
        }
        Run();
        break;
    }
}
