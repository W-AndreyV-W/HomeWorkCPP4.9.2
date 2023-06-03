#include <iostream>
#include <vector>

class big_integer {

public:

    big_integer(const std::string& num) {

        for (int i = static_cast<int>(num.size()) - 1; i >= 0; i--) {
            big_num.push_back(static_cast<int>(num[i]) - 48);
        }
    }

    big_integer(std::vector<int> num) : big_num(num) {}

    //big_integer(const big_integer&) = delete;

    big_integer(big_integer&& other) noexcept : big_num(std::move(other.big_num)) {}

    ~big_integer() {}

    //big_integer& operator = (const big_integer&) = delete;

    big_integer& operator = (big_integer&& other) noexcept {

        if (this != &other) {
            std::swap(big_num, other.big_num);
        }

        return *this;
    }

    big_integer operator + (big_integer& other) {

        int i = 0;
        int num = 0;
        std::vector<int> arr_new;
        auto arr_this = big_num;
        auto arr_other = other.big_num;

        if (arr_this.size() < arr_other.size()) {
            auto thm = arr_this;
            arr_this = arr_other;
            arr_other = arr_this;
        }

        std::vector<int>::iterator num_o = arr_other.begin();
        for (const auto& num_t : big_num) {
            if (num_o != arr_other.end()) {
                arr_new.push_back((num_t + *num_o + num) % 10);
                num = (num_t + *num_o + num) / 10;
                num_o++;
            }
            else {
                arr_new.push_back((num_t + num) % 10);
                num = (num_t + num) / 10;
            }
        }
        if (num > 0) {
            arr_new.push_back(num);
        }

        return big_integer(arr_new);
    }

    big_integer operator * (int other) {

        int num = 0;
        std::vector<int> arr_new;

        for (const auto& num_i : big_num) {
            arr_new.push_back((num_i * other + num) % 10);
            num = (num_i * other + num) / 10;
        }

        if (num > 0) {
            arr_new.push_back(num);
        }

        return big_integer(arr_new);
    }

    friend std::ostream& operator << (std::ostream&, const big_integer& num) {

        for (int i = static_cast<int>(num.big_num.size()) - 1; i >= 0; i--) {
            std::cout << num.big_num[i];
        }

        return std::cout;
    }

private:

    std::vector<int> big_num;
};

int main()
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    auto result2 = number1 * 2;
    std::cout << result << "\t" << result2 << std::endl; // 193099
}