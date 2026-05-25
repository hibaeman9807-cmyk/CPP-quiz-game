#include <iostream>
#include <fstream>
#include <string>
#include <ctime>  
#include <cstdlib>
#include <cctype>  
#include <iomanip>  

using namespace std;

const int MAX_Q = 100;

const int Q_PER_GAME = 10;
const int MAX_LIFELINES = 4;

int qLevel[MAX_Q];
string qText[MAX_Q];
string qOptions[MAX_Q][4];
char qAnswer[MAX_Q];

int totalQ = 0;

string playerName;
int score = 0;
int streak = 0;
int wrongList[Q_PER_GAME];
char userAns[Q_PER_GAME];
int wrongCount = 0;
int currentDifficulty = 1;

void clearScreen();
void delay(int seconds);
void showMainMenu();
bool loadQuestions(string filename, int difficulty);
void shuffle(int arr[], int n);
void startNewQuiz();
void showQuestion(int bankIndex, int num);
void lifelineMenu(int selectedIndices[], int qIndex, bool used[], int& timeLeft);
void lifeline5050(int bankIndex);
void lifelineSkip();
void lifelineSwap(int selectedIndices[], int qIndex);
void applyStreakBonus();
void applyNegative(int diff);
void updateLeaderboard();
void viewLeaderboard();
void logQuiz();
void reviewMode(int selectedIndices[]);

int main() {
    srand((unsigned int)time(0));
    int choice;

    while (true) {
        clearScreen();
        showMainMenu();
        cout << "Enter choice (1-3): ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n'); // To clean the buffer, so program not show error
            delay(1);
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            startNewQuiz();
        }
        else if (choice == 2) {
            viewLeaderboard();
            cout << "\nPress Enter to return...";
            cin.get(); // Only charcter input ( including tab, spaces)
        }
        else if (choice == 3) {
            cout << "\nThank you for playing!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
            delay(2);
        }
    }
    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls"); // to clearance in the window
#else
    system("clear");
#endif
}

void delay(int seconds) {
    clock_t start = clock(); //Defination of Delay
    while ((clock() - start) / CLOCKS_PER_SEC < seconds);
}

void showMainMenu() {
    cout << setw(10) << "QUIZ GAME" << endl;
    cout << " " << endl;
    cout << setw(5) << " " << "1. Start New Quiz" << endl;
    cout << setw(5) << " " << "2. View Leaderboard" << endl;
    cout << setw(5) << " " << "3. Exit" << endl;
    cout << " \n" << endl;

}

void shuffle(int arr[], int n) {
    if (n <= 0) return;
    for (int i = n - 1; i > 0; i--) { // i 1-5 is trh huga
        int j = rand() % (i + 1); // first element random swap with [i]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

bool loadQuestions(string filename, int difficulty) {
    ifstream file(filename.c_str());

    if (!file) {
        cout << "\nError: Question file '" << filename << "' not found! Please create it.\n";
        return false;
    }

    totalQ = 0;
    string line;
    int step = 0;
    int currentLevel = 0;
    char currentAnswer = ' ';

    while (getline(file, line)) {

        // 1. Remove carriage return for Windows compatibility
        if (!line.empty() && line.back() == '\r') line.pop_back();

        // 2. CRITICAL FIX: Skip lines that are empty or contain only spaces
        // This prevents blank lines from being read as Questions or Options
        bool isOnlySpaces = true;
        for (size_t i = 0; i < line.length(); i++) {
            if (!isspace(static_cast<unsigned char>(line[i]))) {
                isOnlySpaces = false;
                break;
            }
        }
        if (line.empty() || isOnlySpaces) {
            continue; // Skip this loop iteration immediately
        }

        // Safety Break if we exceed buffer
        if (totalQ >= MAX_Q) break;

        // 3. Parsing Steps
        if (step == 0) { // Looking for Difficulty Number (1, 2, or 3)

            // Search the line for a digit (handles invisible BOM characters)
            size_t p = 0;
            while (p < line.size() && !isdigit(static_cast<unsigned char>(line[p]))) {
                p++;
            }

            // If no digit found on this line, skip it
            if (p >= line.size()) continue;

            int val = line[p] - '0'; // Convert char to int

            if (val >= 1 && val <= 3) {
                currentLevel = val;
                step++; // Found it, move to Step 1 (Question Text)
            }
        }
        else if (step == 1) {
            qText[totalQ] = line;
            step++;
        }
        else if (step == 2) { qOptions[totalQ][0] = line; step++; }
        else if (step == 3) { qOptions[totalQ][1] = line; step++; }
        else if (step == 4) { qOptions[totalQ][2] = line; step++; }
        else if (step == 5) { qOptions[totalQ][3] = line; step++; }
        else if (step == 6) {
            // Looking for Answer (A, B, C, D)
            // We strip spaces to find the single letter
            size_t p = 0;
            while (p < line.size() && isspace(static_cast<unsigned char>(line[p]))) p++;

            if (p < line.size()) {
                char c = toupper(static_cast<unsigned char>(line[p]));

                // Allow answers like '1' (which means A)
                if (c >= '1' && c <= '4') c = 'A' + (c - '1');

                if (c >= 'A' && c <= 'D') {
                    currentAnswer = c;

                    // If difficulty matches, save the question
                    if (currentLevel == difficulty) {
                        qLevel[totalQ] = currentLevel;
                        qAnswer[totalQ] = currentAnswer;
                        totalQ++;
                    }
                }
            }
            step = 0; // Reset to look for the next Difficulty number

        }
    }
    file.close();

    return totalQ >= Q_PER_GAME;
}

void startNewQuiz() {
    clearScreen(); // on wrong input clear the screen
    cout << "Enter your name: ";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, playerName);
    while (true) {
        bool valid = true;
        for (char c : playerName) {
            int ascii = (int)c;
            if (!((ascii >= 65 && ascii <= 90) ||
                (ascii >= 97 && ascii <= 122) ||
                ascii == 32)) {
                valid = false;
                break;
            }
        }

        if (valid && !playerName.empty()) break;
        cout << "Invalid name! Only A-Z, a-z, and space allowed.\n";
        cout << "Enter your name again: ";
        getline(cin, playerName);
    }

    int cat = 0;
    string catInput;
    while (true) {
        cout << "\nChoose Category:\n1. Computer Science\n2. Science\n3. Sports\n4. History\n";
        cout << "Enter choice (1-4): ";
        if (!getline(cin, catInput)) { cin.clear(); continue; }
        if (catInput.empty()) { cout << "Invalid input. Please input from 1-4.\n"; continue; }
        if (catInput.size() == 1 && isdigit(catInput[0])) {
            cat = catInput[0] - '0'; //charcter to integer
            if (cat >= 1 && cat <= 4) break;
        }
        cout << "Invalid input. Please input from 1-4.\n";
    }

    string file;
    if (cat == 1) file = "computer.txt";
    else if (cat == 2) file = "science.txt";
    else if (cat == 3) file = "sports.txt";
    else if (cat == 4) file = "history.txt";

    int diff = 1; //No cracsh on default value
    string diffInput;
    while (true) {
        cout << "\nChoose Difficulty:\n1. Easy\n2. Medium\n3. Hard\nEnter (1-3): ";
        if (!getline(cin, diffInput)) { cin.clear(); continue; } //getline sy input read krna, spaces bhi handle krta he
        if (diffInput.empty()) { cout << "Invalid input. Please input from 1-3.\n"; continue; }
        if (diffInput.size() == 1 && isdigit(diffInput[0])) {
            diff = diffInput[0] - '0';
            if (diff >= 1 && diff <= 3) break;
        }
        cout << "Invalid input. Please input from 1-3.\n";
    }

    currentDifficulty = diff;

    if (!loadQuestions(file, diff)) {
        cout << "Error: Not enough questions found for level " << diff << " in " << file << ". Found " << totalQ << endl;
        delay(4);
        return;
    }

    int indices[MAX_Q];
    for (int i = 0; i < totalQ; i++) indices[i] = i;
    shuffle(indices, totalQ); //random q

    int selectedIndices[Q_PER_GAME];
    for (int i = 0; i < Q_PER_GAME; i++) {
        selectedIndices[i] = indices[i];
    }

    score = 0; streak = 0; wrongCount = 0;
    for (int k = 0; k < Q_PER_GAME; ++k) { wrongList[k] = -1; userAns[k] = ' '; } //Wrong Q, streak, total sbko dekh rha
    bool lifelines[MAX_LIFELINES] = { true, true, true, true };

    cout << "\nQuiz starting in 3.2.1.";
    delay(3);

    for (int i = 0; i < Q_PER_GAME; i++) {
        int currentBankIndex = selectedIndices[i]; //konsa  Q kis pole sy
        int original_diff = qLevel[currentBankIndex];

        clearScreen();
        showQuestion(currentBankIndex, i + 1); // ye function actual Q or Option display kre ga
        //lifeline wali array hai condition check hoti bool ke through
        cout << "\nLifelines: ";
        if (lifelines[0]) cout << "[1]50:50 ";
        if (lifelines[1]) cout << "[2]Skip ";
        if (lifelines[2]) cout << "[3]Swap ";
        if (lifelines[3]) cout << "[4]Time+10s ";
        cout << "\n \n";
        //Max time 10 sec ,answer mai user input store hota,bool checks user ne ans diya ya nhi
        int timeLimit = 10;
        char answer = ' ';
        bool answered = false;

        clock_t start_time = clock();
        string input;
        // MAIN LOOP: jab tak time khatam na ho jaye aur user jawab na de, loop chalta rahega

        while (((clock() - start_time) / CLOCKS_PER_SEC) < timeLimit && !answered) {

            int remaining_time = timeLimit - (int)((clock() - start_time) / CLOCKS_PER_SEC);
            cout << "\rTime left: " << remaining_time << " sec. Enter A/B/C/D or 1-4: ";

            if (getline(cin, input)) {
                if (((clock() - start_time) / CLOCKS_PER_SEC) >= timeLimit) {
                    break;
                }

                if (input.length() == 1) {
                    char ch = toupper(input[0]);
                    // CASE 1: agar user ne A/B/C/D enter kiya ho (answer)

                    if (ch >= 'A' && ch <= 'D') {
                        answer = ch;
                        answered = true;
                    }
                    // CASE 2: agar user ne 1, 2, 3, ya 4 enter kiya (lifeline)

                    else if (ch >= '1' && ch <= '4') {
                        int lifeline_choice = ch - '1';
                        if (lifeline_choice < 0 || lifeline_choice >= MAX_LIFELINES) {
                            cout << "\nInvalid lifeline choice.\n";
                            continue;
                        }
                        if (!lifelines[lifeline_choice]) {
                            cout << "\nLifeline already used.\n";
                            continue;
                        }

                        lifelines[lifeline_choice] = false;
                        cout << "\n-- LIFELINE ACTIVATED --\n";

                        if (lifeline_choice == 0) {
                            lifeline5050(currentBankIndex);
                            start_time = clock();
                            continue;
                        }
                        // LIFELINE 1: Skip Question

                        else if (lifeline_choice == 1) {
                            answered = true;
                            answer = 'K';
                            break;
                        }
                        // LIFELINE 2: Swap Question (naya question dena)

                        else if (lifeline_choice == 2) {
                            lifelineSwap(selectedIndices, i);
                            i--;
                            answered = true;
                            answer = 'S';
                            break;
                        }
                        // LIFELINE 3: Add +10 seconds

                        else if (lifeline_choice == 3) {
                            timeLimit += 10;
                            cout << "Time increased by 10s!\n";
                            start_time = clock();
                            continue;
                        }
                    }
                    else {
                        cout << "\nInvalid input! Enter A/B/C/D or 1-4.\n";
                    }
                }
                // agar user ne koi aur character diya (na A-D, na 1-4)

                else if (!input.empty()) {
                    cout << "\nInvalid input! Enter a single character.\n";
                }
            }
        }

        if (answer == 'S') continue;
        // agar answer 'S' hai to matlab user ne Swap lifeline use ki hai,
        // is liye purana question skip karke next iteration chalay ga.
        if (answer == 'K') { lifelineSkip(); continue; }

        if (!answered) {
            cout << "\n\nTIME UP!\n";
            applyNegative(original_diff);
            streak = 0;
            cout << "Correct: " << qAnswer[currentBankIndex] << endl;
            userAns[i] = ' ';
            wrongList[wrongCount++] = i;
        }
        else if (answer >= 'A' && answer <= 'D') {
            userAns[i] = answer;
            if (answer == qAnswer[currentBankIndex]) {
                int points = (original_diff == 1) ? 10 : (original_diff == 2) ? 15 : 20;
                // difficulty = easy → 10, medium → 15, hard → 20 points

                score += points;
                streak++;
                applyStreakBonus();
                cout << "\nCORRECT! +" << points << " points\n";
            }
            else {
                applyNegative(original_diff);
                streak = 0;
                cout << "\nWRONG! Correct: " << qAnswer[currentBankIndex] << endl;
                wrongList[wrongCount++] = i;
            }
        }
        delay(2);
    }
    // thodi der rukne ke liye (2 seconds delay)

    updateLeaderboard();
    logQuiz();
    reviewMode(selectedIndices);
    cout << "Final Score: " << score << endl;
    delay(5);
}

void showQuestion(int bankIndex, int num) {
    cout << "\n \n";
    cout << "Question " << num << "/10 Score: " << score << " Streak: " << streak << endl;
    cout << "\n \n";

    cout << qText[bankIndex] << endl << endl;
    for (int i = 0; i < 4; i++) {
        cout << " " << (char)('A' + i) << ". " << qOptions[bankIndex][i] << endl;
    }
}

void lifelineMenu(int selectedIndices[], int qIndex, bool used[], int& timeLeft) {
}

void lifeline5050(int bankIndex) {
    cout << "\n50:50 Activated! Two incorrect options removed.\n";
    int incorrect1 = -1, incorrect2 = -1;
    int correct = -1;

    for (int i = 0; i < 4; i++) {
        if (toupper('A' + i) == qAnswer[bankIndex]) {
            correct = i;
        }
        else if (incorrect1 == -1) {
            incorrect1 = i;
        }
        else {
            incorrect2 = i;
        }
    }

    int kept_incorrect = (rand() % 2 == 0) ? incorrect1 : incorrect2;

    for (int i = 0; i < 4; i++) {
        if (i == correct || i == kept_incorrect) {
            cout << " " << (char)('A' + i) << ". " << qOptions[bankIndex][i] << endl;
        }
        else {
            cout << " " << (char)('A' + i) << ". \n";
        }
    }
}

void lifelineSkip() { cout << "\nQuestion SKIPPED! No penalty. Moving to next question.\n"; }

void lifelineSwap(int selectedIndices[], int qIndex) {
    cout << "\nQuestion SWAPPED!\n";
    int newIndex;
    int safety = 0;
    do {
        newIndex = rand() % totalQ;
        safety++;
    } while (qText[newIndex] == qText[selectedIndices[qIndex]] && safety < 100);

    selectedIndices[qIndex] = newIndex;
    cout << "A new question has been loaded in its place.\n";
}

void applyStreakBonus() {
    if (streak == 3) { score += 5; cout << " STREAK BONUS +5!\n"; }
    else if (streak == 5) { score += 15; cout << " MEGA STREAK +15!\n"; }
}

void applyNegative(int diff) {
    int neg = (diff == 1) ? -2 : (diff == 2) ? -3 : -5;
    score += neg;
    cout << " Negative marking: " << neg << " points\n";
}

void updateLeaderboard() {
    ofstream file("high_scores.txt", ios::app);
    time_t now = time(0);
    // ctime() directly converts time to a readable string
    char dateTimeStr[80];
    ctime_s(&dateTimeStr[0], 80, &now);   // copy ctime result into array
    // remove newline added by ctime()
    dateTimeStr[strcspn(dateTimeStr, "\n")] = '\0';
    //if no characters from str2 are found in str1, strcspn returns the entire length of str1
    string diffStr = (currentDifficulty == 1) ? "Easy" :
        (currentDifficulty == 2) ? "Medium" : "Hard";

    file << playerName << " | "
        << dateTimeStr << " | "
        << score << " | "
        << diffStr << endl;

    file.close();
}

void viewLeaderboard() {
    clearScreen();
    cout << " LEADERBOARD (Top Scores)\n";
    ifstream file("high_scores.txt");
    if (!file) { cout << "No scores file found!\n"; return; }

    string lines[100];
    int scores[100];
    int count = 0;
    string line;

    while (getline(file, line) && count < 100) {
        if (line.length() < 5) continue;
        lines[count] = line;

        size_t firstPipe = line.find('|');//find() = searches for a character
        size_t secondPipe = line.find('|', firstPipe + 1);
        size_t thirdPipe = line.find('|', secondPipe + 1);

        if (secondPipe != string::npos) {
            string scoreStr;
            if (thirdPipe != string::npos) {
                scoreStr = line.substr(secondPipe + 1, thirdPipe - secondPipe - 1);//substr(start, length) = get part of a string
            }
            else {
                scoreStr = line.substr(secondPipe + 1);
            }
            try {
                scores[count] = stoi(scoreStr);
            }
            catch (...) {
                scores[count] = 0;
            }
        }
        else {
            scores[count] = 0;
        }
        count++;
    }
    file.close();

    for (int i = 0; i < count - 1; i++) {//Bubble Sort
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                int tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;

                string tempLine = lines[j];
                lines[j] = lines[j + 1];
                lines[j + 1] = tempLine;
            }
        }
    }

    cout << "RANK | DATA (Name | Date | Score | Difficulty)\n";
    int displayLimit = (count < 5) ? count : 5;
    for (int i = 0; i < displayLimit; i++) {
        cout << i + 1 << ". " << lines[i] << endl;
    }
    if (count == 0) cout << "No scores yet!\n";
}

void logQuiz() {
    ofstream log("quiz_logs.txt", ios::app);
    time_t now = time(0);
    char dateTimeStr[80];

    ctime_s(&dateTimeStr[0], 80, &now);
    // Remove newline added by ctime()
    dateTimeStr[strcspn(dateTimeStr, "\n")] = '\0';
    int correctCount = Q_PER_GAME - wrongCount;

    log << "Player: " << playerName
        << " | Score: " << score
        << " | Time: " << dateTimeStr
        << " | Attempted: " << Q_PER_GAME
        << " | Correct: " << correctCount
        << " | Wrong: " << wrongCount << endl;

    log.close();
}

void reviewMode(int selectedIndices[]) {
    cout << "\n\nREVIEW MODE - Questions you got wrong:\n";
    if (wrongCount == 0) {
        cout << "PERFECT SCORE! All correct!\n";
        return;
    }
    for (int i = 0; i < wrongCount; i++) {
        int wrongListIndex = wrongList[i];
        int originalBankIndex = selectedIndices[wrongListIndex];//Converts quiz index → original question bank index

        cout << "Q" << wrongListIndex + 1 << ": " << qText[originalBankIndex] << endl;
        cout << "Your answer: " << userAns[wrongListIndex] << " | Correct: " << qAnswer[originalBankIndex] << endl << endl;
        delay(5);
    }
}
