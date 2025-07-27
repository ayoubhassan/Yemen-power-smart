#include <iostream>  // مكتبة لإدخال وإخراج البيانات
#include <string>    // مكتبة للتعامل مع النصوص
#include <vector>    // مكتبة للتعامل مع المصفوفات الديناميكية
#include <ctime>     // مكتبة للتعامل مع الوقت والتاريخ
using namespace std; // استخدام مساحة الأسماء القياسية

struct Subscriber {   // تعريف هيكل بيانات المشترك
    string name;      // اسم المشترك
    string meterNumber; // رقم العداد
    string phoneNumber; // رقم الجوال
    string password;   // كلمة المرور
    double previousReading; // القراءة السابقة
    double currentReading;  // القراءة الحالية
    double amountDue;       // المبلغ المستحق
    time_t invoiceTime;    // وقت إصدار الفاتورة
    time_t dueTime;        // موعد استحقاق الدفع
    bool isPaid;            // حالة الدفع (تم الدفع أم لا)
};

vector<Subscriber> subscribers; // قائمة لتخزين بيانات المشتركين
const double rate = 300;         // سعر الكيلو واط

// دالة لحساب الفاتورة
double calculateBill(double previousReading, double currentReading) {
    return (currentReading - previousReading) * rate; // حساب الفاتورة
}

// دالة لعرض واجهة الترحيب
void displayWelcome() {
    cout << "----------------------------------------\n";
    cout << "مرحبًا بكم في محطة الزبيري لتوليد الكهرباء والطاقة\n";
    cout << "----------------------------------------\n";
}

// دالة لتسجيل مشترك جديد
Subscriber registerSubscriber() {
    Subscriber sub; // إنشاء كائن جديد من نوع Subscriber
    cout << "أدخل اسم المشترك: ";
    cin.ignore(); // تجاهل الأحرف غير المرغوب فيها
    getline(cin, sub.name); // إدخال اسم المشترك

    cout << "أدخل رقم العداد: ";
    cin >> sub.meterNumber; // إدخال رقم العداد

    cout << "أدخل رقم الجوال: ";
    cin >> sub.phoneNumber; // إدخال رقم الجوال

    cout << "أدخل كلمة المرور: ";
    cin >> sub.password; // إدخال كلمة المرور

    cout << "أدخل القراءة السابقة (كيلو واط): ";
    cin >> sub.previousReading; // إدخال القراءة السابقة

    cout << "أدخل القراءة الحالية (كيلو واط): ";
    cin >> sub.currentReading; // إدخال القراءة الحالية

    sub.amountDue = calculateBill(sub.previousReading, sub.currentReading); // حساب الفاتورة
    sub.invoiceTime = time(0); // تعيين وقت إصدار الفاتورة
    sub.dueTime = sub.invoiceTime + 86400; // تعيين موعد الاستحقاق بعد 24 ساعة
    sub.isPaid = false; // تعيين حالة الدفع إلى "غير مدفوع"

    return sub; // إرجاع بيانات المشترك
}

// دالة لعرض الفاتورة
void displayInvoice(Subscriber &sub) {
    double consumption = sub.currentReading - sub.previousReading; // حساب الاستهلاك
    cout << "\n----------------- الفاتورة -----------------\n";
    cout << "اسم المشترك: " << sub.name << endl;
    cout << "رقم العداد: " << sub.meterNumber << endl;
    cout << "الاستهلاك: " << consumption << " كيلو واط\n";
    cout << "التكلفة لكل كيلو واط: " << rate << " ريال يمني\n";
    cout << "المبلغ المستحق: " << sub.amountDue << " ريال يمني\n";
    cout << "-------------------------------------------\n";
}

// دالة للدفع
void makePayment(Subscriber &sub) {
    double amount;
    cout << "أدخل المبلغ الذي تريد دفعه: ";
    cin >> amount; // إدخال المبلغ المدفوع

    if (amount >= sub.amountDue) {
        sub.isPaid = true; // إذا تم دفع المبلغ كاملاً
        cout << "تم دفع الفاتورة بالكامل.\n";
    } else {
        sub.amountDue -= amount; // خصم المبلغ المدفوع من المبلغ المستحق
        sub.dueTime += (amount / sub.amountDue) * 86400; // تمديد فترة الاستحقاق
        cout << "تم تمديد فترة الاستحقاق.\n";
    }
}

// دالة للبحث عن مشترك
void searchSubscriber() {
    string meterNumber, password;
    cout << "أدخل رقم العداد: ";
    cin >> meterNumber; // إدخال رقم العداد
    cout << "أدخل كلمة المرور: ";
    cin >> password; // إدخال كلمة المرور

    for (Subscriber &sub : subscribers) { // البحث في قائمة المشتركين
        if (sub.meterNumber == meterNumber && sub.password == password) {
            displayInvoice(sub); // عرض الفاتورة إذا تم العثور على المشترك
            return;
        }
    }
    cout << "لم يتم العثور على المشترك.\n"; // رسالة خطأ إذا لم يتم العثور على المشترك
}

// الدالة الرئيسية
int main() {
    displayWelcome(); // عرض واجهة الترحيب

    while (true) {
        int choice;
        cout << "\nاختر الإجراء:\n1. تسجيل مشترك جديد\n2. البحث عن مشترك\n3. الخروج\n";
        cin >> choice; // إدخال اختيار المستخدم

        if (choice == 1) {
            Subscriber sub = registerSubscriber(); // تسجيل مشترك جديد
            subscribers.push_back(sub); // إضافة المشترك إلى القائمة
            displayInvoice(sub); // عرض الفاتورة
        } else if (choice == 2) {
            searchSubscriber(); // البحث عن مشترك
        } else if (choice == 3) {
            break; // الخروج من البرنامج
        } else {
            cout << "خيار غير صالح.\n"; // رسالة خطأ إذا كان الاختيار غير صالح
        }
    }

    cout << "\nشكراً لاستخدامكم محطة الزبيري لتوليد الكهرباء والطاقة.\n";
    cout << "إعداد المشروع: المهندس أيوب حسن الزبيري\n"; // رسالة الختام
    return 0;
}