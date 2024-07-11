    Admin admin;
    admin.login(); // Track admin login status

    if(admin.getIsLoggedIn()){
        int choice;
        bool isAdminRunning = true;
    



   while (isAdminRunning) {
            cout << "\nAdmin Menu:\n";
            cout << "1. Add Student\n";
            cout << "2. Remove Student\n";
            cout << "3. Update Student Data\n";
            cout << "4. View All Results\n";
            cout << "5. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    admin.addStudent();
                    break;
                case 2:
                    admin.removeStudent();
                    break;
                case 3:
                    admin.updateStudentData();
                    break;
                case 4:
                    admin.viewAllResults();
                    break;
                case 5:
                    admin.logout();
                    isAdminRunning = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
    }
}

else {
        cout << "Exiting program due to failed admin login.\n";
}