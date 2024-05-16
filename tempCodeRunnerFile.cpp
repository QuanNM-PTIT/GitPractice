void Signup()
// {
//     string userName, password;
//     cout << "Nhap userName: \n";
//     cin >> userName;
//     cout << "Nhap password: \n";
//     cin >> password;
//     User x(0, userName, password);
//     int id = x.getNextAvailableId();
//     User a(id, userName, password);
//     bool check = a.registerUser();
//     if (check)
//     {
//         string name, email, sex, birthday, address, phoneNumber, role;
//         cout << "Dang ky tai khoan truy cap thanh cong, vui long nhap thong tin ca nhan\n";
//         cout << "Nhap Ho va ten: \n";
//         scanf("\n");
//         getline(cin, name);
//         cout << "Nhap email: \n";
//         cin >> email;
//         cout << "Nhap gioi tinh: \n";
//         cin >> sex;
//         cout << "Nhap ngay thang nam sinh: \n";
//         cin >> birthday;
//         cout << "Nhap dia chi noi o: \n";
//         scanf("\n");
//         getline(cin, address);
//         cout << "Nhap so dien thoai: \n";
//         cin >> phoneNumber;
//         role = "User";
//         Person a(name, email, sex, birthday, address, phoneNumber, role);
//         bool check = a.addPerson();
//         if (check)
//         {
//             cout << "Them thong tin thanh cong\n";
//         }
//         else
//             cout << "Khong the mo tep people.txt de them thong tin\n";
//     }
//     return;
// }