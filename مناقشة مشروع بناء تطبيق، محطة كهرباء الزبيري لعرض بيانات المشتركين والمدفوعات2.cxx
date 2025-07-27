#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Subscriber {
    string name;
    string meterNumber;
    string phoneNumber;
    string password;
    double previousReading;
    double currentReading;
    double amountDue;
    time_t invoiceTime;
    time_t dueTime;
    bool isPaid;
};

vector<Subscriber> subscribers;
const double rate = 300;

double calculateBill(double previousReading, double currentReading) {
    return (currentReading - previousReading) * rate;
}

void displayWelcome() {
    cout << "----------------------------------------\n";
    cout << "مرحبًا بكم في محطة الزبيري لتوليد الكهرباء والطاقة\n";
    cout << "----------------------------------------\n";
}

Subscriber registerSubscriber() {
    Subscriber sub;
    cout << "أدخل اسم المشترك: ";
    cin.ignore();
    getline(cin, sub.name);
    cout << "أدخل رقم العداد: ";
    cin >> sub.meterNumber;
    cout << "أدخل رقم الجوال: ";
    cin >> sub.phoneNumber;
    cout << "أدخل كلمة المرور: ";
    cin >> sub.password;
    cout << "أدخل القراءة السابقة: ";
    cin >> sub.previousReading;
    cout << "أدخل القراءة الحالية: ";
    cin >> sub.currentReading;
    sub.amountDue = calculateBill(sub.previousReading, sub.currentReading);
    sub.invoiceTime = time(0);
    sub.dueTime = sub.invoiceTime + 86400;
    sub.isPaid = false;
    return sub;
}

void displayInvoice(Subscriber &sub) {
    double consumption = sub.currentReading - sub.previousReading;
    cout << "\n----------------- الفاتورة -----------------\n";
    cout << "اسم المشترك: " << sub.name << endl;
    cout << "رقم العداد: " << sub.meterNumber << endl;
    cout << "الاستهلاك: " << consumption << " كيلو واط\n";
    cout << "المبلغ المستحق: " << sub.amountDue << " ريال يمني\n";
    cout << "تاريخ الفاتورة: " << ctime(&sub.invoiceTime);
    cout << "تاريخ الاستحقاق: " << ctime(&sub.dueTime);
    cout << "-------------------------------------------\n";

    if (difftime(sub.dueTime, time(0)) <= 0) {
        cout << "تم فصل الكهرباء بسبب عدم الدفع.\n";
        return;
    }

    int paymentMethod;
    cout << "اختر طريقة الدفع:\n1. بطاقة بنكية\n2. تحويل لحساب المحطة\n";
    cin >> paymentMethod;

    if (paymentMethod == 1) {
        double amount;
        cout << "أدخل المبلغ المدفوع: ";
        cin >> amount;
        sub.amountDue -= amount;
        if (sub.amountDue <= 0) {
            sub.isPaid = true;
            cout << "تم دفع الفاتورة بالكامل.\n";
        } else {
            sub.dueTime += (amount / sub.amountDue) * 86400;
            cout << "تم تمديد فترة الفصل.\n";
        }
    } else if (paymentMethod == 2) {
        cout << "يرجى تحويل المبلغ إلى حساب المحطة: 123456789\n";
    } else {
        cout << "خيار غير صالح.\n";
    }
}

void updateSubscriber(Subscriber &sub) {
    int choice;
    cout << "\nاختر ما تريد تعديله:\n";
    cout << "1. الاسم\n2. رقم العداد\n3. القراءة السابقة\n4. القراءة الحالية\n";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "أدخل الاسم الجديد: ";
            cin.ignore();
            getline(cin, sub.name);
            break;
        case 2:
            cout << "أدخل رقم العداد الجديد: ";
            cin >> sub.meterNumber;
            break;
        case 3:
            cout << "أدخل القراءة السابقة الجديدة: ";
            cin >> sub.previousReading;
            sub.amountDue = calculateBill(sub.previousReading, sub.currentReading);
            break;
        case 4:
            cout << "أدخل القراءة الحالية الجديدة: ";
            cin >> sub.currentReading;
            sub.amountDue = calculateBill(sub.previousReading, sub.currentReading);
            break;
        default:
            cout << "خيار غير صالح.\n";
    }
}

void searchSubscriber() {
    string meterNumber, password;
    cout << "أدخل رقم العداد: ";
    cin >> meterNumber;
    cout << "أدخل كلمة المرور: ";
    cin >> password;

    for (auto &sub : subscribers) {
        if (sub.meterNumber == meterNumber && sub.password == password) {
            cout << "اسم المشترك: " << sub.name << endl;
            cout << "رقم الجوال: " << sub.phoneNumber << endl;
            cout << "تاريخ الاشتراك: " << ctime(&sub.invoiceTime);
            cout << "الفواتير:\n";
            cout << "الفاتورة الأخيرة: " << sub.amountDue << " ريال يمني\n";
            cout << "تم الدفع: " << (sub.isPaid ? "نعم" : "لا") << endl;
            return;
        }
    }
    cout << "المشترك غير موجود.\n";
}

int main() {
    displayWelcome();
    char choice;
    do {
        cout << "1. تسجيل مشترك جديد\n2. عرض الفاتورة\n3. تعديل بيانات المشترك\n4. البحث عن مشترك\n5. الخروج\n";
        cin >> choice;
        switch (choice) {
            case '1':
                subscribers.push_back(registerSubscriber());
                break;
            case '2':
                if (!subscribers.empty()) {
                    displayInvoice(subscribers.back());
                } else {
                    cout << "لا يوجد مشتركين.\n";
                }
                break;
            case '3':
                if (!subscribers.empty()) {
                    updateSubscriber(subscribers.back());
                } else {
                    cout << "لا يوجد مشتركين.\n";
                }
                break;
            case '4':
                searchSubscriber();
                break;
            case '5':
                cout << "شكراً لاستخدامكم محطة الزبيري لتوليد الكهرباء والطاقة.\n";
                cout << "إعداد المهندس أيوب حسن الزبيري.\n";
                break;
            default:
                cout << "خيار غير صالح.\n";
        }
    } while (choice != '5');
    return 0;
}