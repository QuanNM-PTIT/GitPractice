void Login()
{
    string userName, password;
    cout << "Nhap Email: \n";
    cin >> userName;
    cout << "Nhap password: \n";
    cin >> password;
    ifstream filein("users.txt");
    if (!filein.is_open())
    {
        cout << "Khong the mo tep users.txt\n";
    }
    else
    {
        string tmp;
        while (getline(filein, tmp))
        {
            if (tmp.find(userName) != string::npos && tmp.find(password) != string::npos)
            {
                cout << "Dang nhap thanh cong\n";
                loggedIn = true; // Đánh dấu đã đăng nhập thành công
                filein.close();  // Đóng file users.txt trước khi tiếp tục
                ifstream peopleFile("people.txt");
                if (!peopleFile.is_open())
                {
                    cout << "Khong the mo tep people.txt\n";
                }
                else
                {
                    string name;
                    while (getline(peopleFile, tmp))
                    {
                        if (tmp.find(userName) != string::npos)
                        {
                            // Tìm thấy email trong file people.txt
                            // Sử dụng stringstream để lấy tên từ dòng chứa email
                            stringstream ss(tmp);
                            string bracket;
                            ss >> bracket;          // Bỏ qua ký tự '['
                            getline(ss, name, ']'); // Lấy tên đến khi gặp ký tự ']'

                            name = name.substr(2); // Bỏ đi dấu [ ở đầu tên
                            cout << "Welcome " << name << "!\n";
                            break; // Kết thúc vòng lặp sau khi tìm thấy tên
                        }
                    }
                    peopleFile.close();
                }
                return;
            }
        }
        cout << "Dang nhap that bai\n";
    }
    filein.close();
}