#include <stdio.h>
#include<iostream>
#include<conio.h>
#include <iomanip>
#include <windows.h>

using namespace std;

class Account; // Делаем объявление класса, так как Account используется в других классах
class Payment;

class User { // Пользователь
public:
    char FULL_NAME[50]; // ФИО
    int ID;
    int PIN_code;
};

class Collector : public User {    // Инкассатор
public:
    void top_up_of_the_bank(ATM& atm, int amount) {
        cout << "Был пополнен банкомат" << endl;
    }
};

class Client: public User { // клиент
public:
    int Account; // Счёт
    char List_payments[50]; // Список платежей

    void payment_services(Account& account, int amount, const char* comment) {  // Оплата услуг
        if (account.Balance >= amount) { // Проверяем, достаточно ли средств на счете
            account.Balance -= amount; // Снимаем сумму со счета
            cout << "Была выполнена оплата услуги" << endl;
        } else {
            cout << "На счету недостаточно средств." << endl;
        }
    }

    void deduction_account(Account& account, int amount) {       // Вычет счёта 
        cout << "Был выдан счёт." << endl;
    }

    void replenishment_of_the_account(Account& account, int amount) {        // Пополнение счёта
        cout << "Был пополнен счёт." << endl;
    }

    void view_account(Account& account) const {        // Просмотр счёта
        cout << "Просмотр счёта" << endl;
        cout << " Просмотр баланса" << endl;
    }
};

class Payment : public Account {    // Платёж
public:
    int Amount; // Сумма
    char Comment[50]; // Комментарий

    void withdraw_summu_service(Payment& payment) {        // Снять сумму за услугу
        cout << " Была снята сумма за услугу" << endl;
    }
};

class ATM {    // Банкомат 
public:
    int Authorized_User; // Авторизованный пользователь
    int current_account; // Текущий счет

    void checkIdentification() {
        int account_number, pin_code;
        bool authenticated = false;

        cout << "Введите номер счета: ";
        cin >> account_number;
        cout << "Введите PIN-код: ";
        cin >> pin_code;

        // Ищем в базе данных пользователя с указанным номером счета
        for (int i = 0; i < num_accounts; i++) {
            if (accounts[i].getNumber() == account_number) {
                // Если пользователь найден, проверяем его PIN-код
                if (accounts[i].checkPIN(pin_code)) {
                    authenticated = true;
                    current_account = i;
                    break;
                }
            }
        }

        if (authenticated) {
            cout << "Вы успешно идентифицированы." << endl;
        } else {
            cout << "Ошибка идентификации. Проверьте номер счета и PIN-код." << endl;
        }
    }

    bool authorization(int id, int pin_code) { // Авторизация
        if (id == Authorized_User && pin_code == PIN_code) {
            Authorized_User = id;
            return true;
        }
        return false;
    }

    void issue_of_the_amount(Account& account, int amount) { // Выдача суммы
        if (account.Balance >= amount) {
            account.Balance -= amount;
            cout << "Сумма " << amount << " выдана." << endl;
        } else {
            cout << "На счету недостаточно средств." << endl;
        }
    }

    void change_status(Account& account, Client& client, Collector& collector) {
        cout << "Был изменён статус." << endl;     // Изменение статуса
    }

    void top_up(int amount) {
        cout << "Был пополнен банкомат." << endl;     // Пополнение банкомата
    }
};

class Account {     // Счёт
public:
    int Number; // Номер счёта
    int Balance; // Баланс

    int getNumber() const {
        return Number;
    }

    bool checkPIN(int pin) const {
        return pin == PIN;
    }

private:
    int PIN; // PIN-код
};

int main() {
   
       SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Client client;
    Account account;
    ATM atm;
    Payment payment;
    Collector collector;

    // Вызов методов
    client.payment_services(account, 500, "Оплата услуги");
    client.view_account(account);
    atm.authorization(123456, 7890);
    atm.issue_of_the_amount(account, 1000);
    atm.top_up(500);
    collector.top_up_of_the_bank(atm, 10000);

    return 0;
}