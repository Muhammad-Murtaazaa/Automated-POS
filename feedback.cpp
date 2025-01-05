// #include <iostream>
// #include <fstream>
// #include <string>
// #include <ctime>
// #include <iomanip>
// using namespace std;

// class FeedbackSystem
// {
// public:
//     void collectFeedback();
//     void saveFeedback(const string& name, const string& email, const string& feedback);

// private:
//     string getCurrentTime() const;
// };

// void FeedbackSystem::collectFeedback()
// {
//     string name, email, feedback;

//     cout << "=============== USER FEEDBACK INTERFACE ===============" << endl;
//     cout << "Enter your name: ";
//     getline(cin, name);
//     cout << "Enter your email: ";
//     getline(cin, email);
//     cout << "Enter your feedback: ";
//     getline(cin, feedback);

//     saveFeedback(name, email, feedback);

//     cout << "Thank you for your feedback!" << endl;
// }

// void FeedbackSystem::saveFeedback(const string& name, const string& email, const string& feedback)
// {
//     ofstream file("feedback.txt", ios::app);
//     if (!file)
//     {
//         cerr << "Error opening feedback file for writing!" << endl;
//         return;
//     }

//     file << "=============== FEEDBACK ENTRY ===============" << endl;
//     file << "Name: " << name << endl;
//     file << "Email: " << email << endl;
//     file << "Date: " << getCurrentTime() << endl;
//     file << "Feedback: " << feedback << endl;
//     file << "==============================================" << endl;
//     file.close();
// }

// string FeedbackSystem::getCurrentTime() const
// {
//     time_t now = time(0);
//     tm *ltm = localtime(&now);
//     char buffer[50];
//     strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", ltm);
//     return string(buffer);
// }

// int main()
// {
//     FeedbackSystem feedbackSystem;
//     feedbackSystem.collectFeedback();
//     return 0;
// }
