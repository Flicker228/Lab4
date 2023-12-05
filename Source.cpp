#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h> 

template <typename T1, typename T2>
class Pair {
public:
    Pair() {}
    Pair(const T1& name, const T2& price) : name(name), price(price) {}

    void displayPair() const {
        std::cout << name << ": " << price << std::endl;
    }

    void savePairToFile(std::ofstream& outFile) const {
        outFile << name << " " << price << " ";
    }

private:
    T1 name;
    T2 price;
};


class Product {
public:
    Product(const std::string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    ~Product() {}

    const std::string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    virtual void displayInfo() const {
        std::cout << "Продукт: " << name << ", Цена: " << price << ", Количество: " << quantity << std::endl;
    }

    void saveToFile(std::ofstream& outFile) const {
        outFile << name << " " << price << " " << quantity << " ";
    }

    static bool compareByPrice(const Product* product1, const Product* product2) {
        return product1->getPrice() < product2->getPrice();
    }

private:
    std::string name;
    double price;
    int quantity;
};

class Clothing : public Product {
public:
    void displayInfo() const override{
        std::cout << "Одежда: " << name << ", Цена: " << price << ", Количество: " << quantity << std::endl;
    }
private:
    std::string name;
    double price;
    int quantity;
};

class Electronics : public Product {
public:
    void displayInfo() const override {
        std::cout << "Электроника: " << name << ", Цена: " << price << ", Количество: " << quantity << std::endl;
    }
private:
    std::string name;
    double price;
    int quantity;
};

void modifyProduct(Product* product) {
    std::cout << "Продукт найден. Что вы хотите изменить?" << std::endl;
    std::cout << "1. Название продукта" << std::endl;
    std::cout << "2. Цену" << std::endl;
    std::cout << "3. Количество" << std::endl;

    int choice;
    std::cout << "Введите ваш выбор: ";
    std::cin >> choice;

    switch (choice) {
    case 1: {
        std::string newName;
        std::cout << "Введите новое имя: ";
        std::cin >> newName;
        product->setName(newName);
        break;
    }
    case 2: {
        double newPrice;
        std::cout << "Введите новую цену: ";
        std::cin >> newPrice;
        product->setPrice(newPrice);
        break;
    }
    case 3: {
        int newQuantity;
        std::cout << "Введите новое количество: ";
        std::cin >> newQuantity;
        product->setQuantity(newQuantity);
        break;
    }
    default:
        std::cout << "Неверный выбор." << std::endl;
    }
}

void saveProductsToFile(const std::vector<Product*>& products, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
        return;
    }

    for (const auto* product : products) {
        product->saveToFile(outFile);
    }

    outFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<Product*> products;

    int choice;
    std::string filename;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить продукт" << std::endl;
        std::cout << "2. Изменить данные о продукте" << std::endl;
        std::cout << "3. Удалить продукт" << std::endl;
        std::cout << "4. Найти продукт" << std::endl;
        std::cout << "5. Вывести список продуктов" << std::endl;
        std::cout << "6. Сохранить в файл" << std::endl;
        std::cout << "7. Сортировать по цене" << std::endl;
        std::cout << "8. Выход" << std::endl;

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name;
            double price;
            int quantity;

            std::cout << "Введите данные продукта:" << std::endl;
            std::cout << "Название: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> price;
            std::cout << "Количество: ";
            std::cin >> quantity;

            products.push_back(new Product(name, price, quantity));

            break;
        }
        case 2: {
            std::string name;
            double price;
            std::cout << "Введите данные продукта для изменения:" << std::endl;
            std::cout << "Название: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> price;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name && product->getPrice() == price;
                });

            if (it != products.end()) {
                modifyProduct(*it);
            }
            else {
                std::cout << "Продукт не найден." << std::endl;
            }

            break;
        }
        case 3: {
            std::string name;
            double price;
            std::cout << "Введите данные студента для удаления:" << std::endl;
            std::cout << "Имя: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> price;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name && product->getPrice() == price;
                });

            if (it != products.end()) {
                delete* it;
                products.erase(it);
                std::cout << "Продукт удален." << std::endl;
            }
            else {
                std::cout << "Продукт не найден." << std::endl;
            }

            break;
        }
        case 4: {
            std::string name;
            double price;
            std::cout << "Введите данные продукта для поиска:" << std::endl;
            std::cout << "Название: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> price;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name && product->getPrice() == price;
                });

            if (it != products.end()) {
                (*it)->displayInfo();
            }
            else {
                std::cout << "Продукт не найден." << std::endl;
            }

            break;
        }
        case 5: {
            std::cout << "Список продуктов:" << std::endl;
            for (const auto* product : products) {
                product->displayInfo();
            }
            break;
        }
        case 6: {
            std::cout << "Введите имя файла для сохранения данных: ";
            std::cin >> filename;
            saveProductsToFile(products, filename);
            break;
        }
        case 7: {
            std::sort(products.begin(), products.end(), Product::compareByPrice);
            std::cout << "Список продуктов отсортирован по цене." << std::endl;
            break;
        }
        case 8:
            std::cout << "Выход." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    } while (choice != 8);

    for (const auto* product : products) {
        delete product;
    }

    return 0;
}