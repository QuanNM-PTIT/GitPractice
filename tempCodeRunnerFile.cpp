string name, email, sex, birthdate, address, phoneNumber, role, password;
    std::cout << "Nhap ten: ";
    cin.ignore();
    getline(cin, name);
    
    // Validate email
    bool validEmail = false;
    while (!validEmail)
    {
        cout << "Nhap email: ";
        getline(cin, email);
        // Perform email validation here
        if (validateEmail(email))
        {
            validEmail = true;
        }
        else
        {
            cout << "Email khong hop le. Vui long nhap lai.\n";
        }
    }
    
    // Validate password
    bool validPassword = false;
    while (!validPassword)
    {
        cout << "Nhap mat khau: ";
        getline(cin, password);
        // Perform password validation here
        if (validatePassword(password))
        {
            validPassword = true;
        }
        else
        {
            cout << "Mat khau khong hop le. Vui long nhap lai.\n";
        }
    }
    
    cout << "Nhap gioi tinh: ";
    getline(cin, sex);
    cout << "Nhap ngay sinh: ";
    getline(cin, birthdate);
    cout << "Nhap dia chi: ";
    getline(cin, address);
    cout << "Nhap so dien thoai: ";
    getline(cin, phoneNumber);
    cout << "Nhap vai tro (User/Admin): ";
    getline(cin, role);

    Person p(name, email, sex, birthdate, address, phoneNumber, role);
    User u(User::getNextAvailableId(), email, password);

    if (u.registerUser() && p.addPerson())
    {
        dsUsers.push_back(u);
        dsPeople.push_back(p);
        cout << "Dang ki thanh cong!\n";
    }
    else
    {
        cout << "Dang ki that bai!\n";
    }