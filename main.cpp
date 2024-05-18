#include <bits/stdc++.h>
#include "./class/Book.h"
#include "./class/EBook.h"
#include "./class/BorrowInfo.h"
#include "./class/User.h"

using namespace std;

void printTitle(){
    cout << "Hello Main!!\n";
    cout << "WELCOME TO YEN LIBRARY!!!\n\n";
    return;
}
void getEnterKey(){
    cout << "Nhan Enter de quay lai!\n";
    cin.ignore();
    cin.get();
    return;
}

int main(){
    // Insert code here
    
	    
    bool isOut = false;
    bool isLogged = false;
    bool isLegalChoose = true;
    Person person = Person();

    while (1) {
        system("cls");
        printTitle();
        if (person.getPersonName() != "") {
            isLogged = true;
        }
        else {
            isLogged = false;
        }
    	if (isLogged) {
    		cout << "WELCOME " << person.getPersonName() << " " << person.getPersonRole() << "\n\n";
		}
        else {
            cout << "Ban chua dang nhap!!!\n\n";
        }
        cout << "MENU\n";
        cout << "1. Dang nhap.\n";
        cout << "2. Dang ki.\n";
        cout << "3. Them sach.\n";
        cout << "4. Sua thong tin sach.\n";
        cout << "5. Xoa sach.\n";
        cout << "6. Muon sach.\n";
        cout << "7. Tra sach.\n";
        cout << "8. Lay thong tin cac quyen sach.\n";
        cout << "9. Lay thong tin 1 quyen sach.\n";
        cout << "10. Lay thong tin tat ca cac eBook hien co.\n";
        cout << "11. Lay thong tin 1 ebook.\n";
        cout << "12. Hien thi tat ca cac quyen sach da muon.\n";
        cout << "13. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon.\n";
        cout << "14. Chinh sua thong tin ca nhan.\n";
        cout << "15. Chinh sua thong tin ca nhan cua Users.\n";
        cout << "16. Dang xuat.\n";
        cout << "17. Thoat chuong trinh.\n";
        cout << "\n";
        int choose;
        if (isLegalChoose) {
            cout << "Nhap lua chon: ";
        }
        else {
            isLegalChoose = true;
            cout << "Lua chon khong hop le!!!\n";
            cout << "Vui long chon lai: ";
        }
        cin >> choose;
        
        switch (choose) {
        case 1: //cout << "1. Dang nhap.\n";
            if (!isLogged) {
                person = loginUser();
            }
            else {
                cout << "Ban da dang nhap roi!!\n";
                getEnterKey();
            }
            break;
        case 2: //cout << "2. Dang ki.\n";
            registerUser();
            break;
        case 3: //cout << "3. Them sach.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "Admin") {
                    addBook();
                    cout << "Them sach thanh cong!!\n";
                }
                else {
                    cout << "Chuc nang nay chi danh cho ADMIN!!\n";
                }
            }
            getEnterKey();
            break;
        case 4: //cout << "4. Sua thong tin sach.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "Admin") {
                    updateBook();
                }
                else {
                    cout << "Chuc nang nay chi danh cho ADMIN!!\n";
                }
            }
            getEnterKey();
            break;
        case 5: //cout << "5. Xoa sach.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "Admin") {
                    deleteBook();
                }
                else {
                    cout << "Chuc nang nay chi danh cho ADMIN!!\n";
                }
            }
            getEnterKey();
            break;
        case 6: //cout << "6. Muon sach.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "User") {
                    addBorrowInfo();
                }
                else {
                    cout << "Chuc nang nay chi danh cho User!!\n";
                }
            }
            getEnterKey();
            break;
        case 7: //cout << "7. Tra sach.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "User") {
                    deleteBorrowInfo();
                }
                else {
                    cout << "Chuc nang nay chi danh cho ADMIN!!\n";
                }
            }
            getEnterKey();
            break;
        case 8: //cout << "8. Lay thong tin cac quyen sach.\n";
            displayBook();
            getEnterKey();
            break;
        case 9: //cout << "9. Lay thong tin 1 quyen sach.\n";
            getOneBook();
            getEnterKey();
            break;
        case 10: //cout << "10. Lay thong tin tat ca cac eBook hien co.\n";
            displayEBook();
            getEnterKey();
            break;
        case 11:
            cout << "11. Lay thong tin 1 ebook.\n";
            getOneEBook();
            getEnterKey();
            break;
        case 12: //cout << "12. Hien thi tat ca cac quyen sach da muon.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "User") {
                    showBorrowedBook(person.getPersonId());
                }
                else {
                    cout << "Chuc nang nay chi danh cho User!!\n";
                }
            }
            getEnterKey();
            break;
        case 13: //cout << "13. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "Admin") {
                    showBorrowedBookWithUserId();
                }
                else {
                    cout << "Chuc nang nay chi danh cho Admin!!\n";
                }
            }
            getEnterKey();
            break;
        case 14: //cout << "14. Chinh sua thong tin ca nhan.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                updatePeopleInfo(person.getPersonId());
            }
            getEnterKey();
            break;
        case 15: //cout << "15. Chinh sua thong tin ca nhan cua Users.\n";
            if (!isLogged) {
                cout << "Ban chua dang nhap!!\n";
                cout << "Hay dang nhap de su dung tinh nang nay!!\n";
            }
            else {
                if (person.getPersonRole() == "Admin") {
                    updatePeopleInfoByAdmin();
                }
                else {
                    cout << "Chuc nang nay chi danh cho Admin!!\n";
                }
            }
            getEnterKey();
            break;
        case 16: //cout << "16. Dang xuat.\n";
            if (isLogged) {
                person = logoutUser(person);
            }
            else {
                cout << "Ban chua dang nhap!!\n";
                cout << "Nhan Enter de quay lai!\n";
                cin.ignore();
                cin.get();
            }
            break;
        case 17: //cout << "17. Thoat chuong trinh.\n";
            cout << "17. Thoat chuong trinh.\n";
            isOut = true;
            break;
        
        default:
            isLegalChoose = false;
            break;
        }
        if (isOut) {
            cout << "Hen gap lai!!!\n";
            break;
        }
    }
    return 0;
}
