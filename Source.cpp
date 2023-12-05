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
        std::cout << "�������: " << name << ", ����: " << price << ", ����������: " << quantity << std::endl;
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
        std::cout << "������: " << name << ", ����: " << price << ", ����������: " << quantity << std::endl;
    }
private:
    std::string name;
    double price;
    int quantity;
};

class Electronics : public Product {
public:
    void displayInfo() const override {
        std::cout << "�����������: " << name << ", ����: " << price << ", ����������: " << quantity << std::endl;
    }
private:
    std::string name;
    double price;
    int quantity;
};

void modifyProduct(Product* product) {
    std::cout << "������� ������. ��� �� ������ ��������?" << std::endl;
    std::cout << "1. �������� ��������" << std::endl;
    std::cout << "2. ����" << std::endl;
    std::cout << "3. ����������" << std::endl;

    int choice;
    std::cout << "������� ��� �����: ";
    std::cin >> choice;

    switch (choice) {
    case 1: {
        std::string newName;
        std::cout << "������� ����� ���: ";
        std::cin >> newName;
        product->setName(newName);
        break;
    }
    case 2: {
        double newPrice;
        std::cout << "������� ����� ����: ";
        std::cin >> newPrice;
        product->setPrice(newPrice);
        break;
    }
    case 3: {
        int newQuantity;
        std::cout << "������� ����� ����������: ";
        std::cin >> newQuantity;
        product->setQuantity(newQuantity);
        break;
    }
    default:
        std::cout << "�������� �����." << std::endl;
    }
}

void saveProductsToFile(const std::vector<Product*>& products, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ������." << std::endl;
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
        std::cout << "����:" << std::endl;
        std::cout << "1. �������� �������" << std::endl;
        std::cout << "2. �������� ������ � ��������" << std::endl;
        std::cout << "3. ������� �������" << std::endl;
        std::cout << "4. ����� �������" << std::endl;
        std::cout << "5. ������� ������ ���������" << std::endl;
        std::cout << "6. ��������� � ����" << std::endl;
        std::cout << "7. ����������� �� ����" << std::endl;
        std::cout << "8. �����" << std::endl;

        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name;
            double price;
            int quantity;

            std::cout << "������� ������ ��������:" << std::endl;
            std::cout << "��������: ";
            std::cin >> name;
            std::cout << "����: ";
            std::cin >> price;
            std::cout << "����������: ";
            std::cin >> quantity;

            products.push_back(new Product(name, price, quantity));

            break;
        }
        case 2: {
            std::string name;
            double price;
            std::cout << "������� ������ �������� ��� ���������:" << std::endl;
            std::cout << "��������: ";
            std::cin >> name;
            std::cout << "����: ";
            std::cin >> price;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name && product->getPrice() == price;
                });

            if (it != products.end()) {
                modifyProduct(*it);
            }
            else {
                std::cout << "������� �� ������." << std::endl;
            }

            break;
        }
        case 3: {
            std::string name;
            double price;
            std::cout << "������� ������ �������� ��� ��������:" << std::endl;
            std::cout << "���: ";
            std::cin >> name;
            std::cout << "����: ";
            std::cin >> price;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name && product->getPrice() == price;
                });

            if (it != products.end()) {
                delete* it;
                products.erase(it);
                std::cout << "������� ������." << std::endl;
            }
            else {
                std::cout << "������� �� ������." << std::endl;
            }

            break;
        }
        case 4: {
            std::string name;
            double price;
            std::cout << "������� ������ �������� ��� ������:" << std::endl;
            std::cout << "��������: ";
            std::cin >> name;
            std::cout << "����: ";
            std::cin >> price;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name && product->getPrice() == price;
                });

            if (it != products.end()) {
                (*it)->displayInfo();
            }
            else {
                std::cout << "������� �� ������." << std::endl;
            }

            break;
        }
        case 5: {
            std::cout << "������ ���������:" << std::endl;
            for (const auto* product : products) {
                product->displayInfo();
            }
            break;
        }
        case 6: {
            std::cout << "������� ��� ����� ��� ���������� ������: ";
            std::cin >> filename;
            saveProductsToFile(products, filename);
            break;
        }
        case 7: {
            std::sort(products.begin(), products.end(), Product::compareByPrice);
            std::cout << "������ ��������� ������������ �� ����." << std::endl;
            break;
        }
        case 8:
            std::cout << "�����." << std::endl;
            break;
        default:
            std::cout << "�������� �����." << std::endl;
        }
    } while (choice != 8);

    for (const auto* product : products) {
        delete product;
    }

    return 0;
}