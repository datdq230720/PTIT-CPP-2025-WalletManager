#include <iostream>
#include "SystemManager.h"

using namespace std;

void user_menu(SystemManager& sm);  
void admin_menu(SystemManager& sm);

void main_menu(SystemManager& sm) {
    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Dang ky tai khoan\n";
        cout << "2. Dang nhap\n";
        cout << "3. Quen mat khau\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
	    
        switch (choice) {
            case 1:
                sm.register_user();
                break;
            case 2:
                if (sm.login()) {
				    if (sm.is_admin()) {
				        admin_menu(sm);
				    } else {
				        user_menu(sm);
				    }
				}
                break;
            case 3:
                sm.forgot_password();
                break;
            case 0:
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}

void user_menu(SystemManager& sm) {
    int choice;
    do {
        cout << "\n===== USER MENU =====\n";
        cout << "1. Xem thong tin vi\n";
        cout << "2. Chuyen diem\n";
        cout << "3. Doi mat khau\n";
        cout << "0. Dang xuat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sm.show_wallet_info();
                break;
            case 2:
                sm.transfer_point();
                break;
            case 3:
			    sm.change_password();
			    break;
            case 0:
                cout << "Dang xuat...\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}

void admin_menu(SystemManager& sm) {
    int choice;
    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Xem vi\n";
        cout << "2. Chuyen diem\n";
        cout << "3. Doi mat khau\n";
        cout << "4. Danh sach user\n";
        cout << "5. Tao user moi\n";
        cout << "6. Xoa user\n";
        cout << "0. Dang xuat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1: sm.show_wallet_info(); break;
            case 2: sm.transfer_point(); break;
            case 3: sm.change_password(); break;
            case 4: sm.list_users(); break;
            case 5: sm.create_user_by_admin(); break;
            case 6: sm.delete_user(); break;
            case 0: cout << "Dang xuat...\n"; break;
            default: cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}

int main() {
    SystemManager system_manager;
    system_manager.load_users("users.json");

    main_menu(system_manager);

    return 0;
}

