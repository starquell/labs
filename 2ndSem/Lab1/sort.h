#include <algorithm>

void countingSort (std::vector <Monster> &monsters) {       // sorting by attack type

    static std::map <std::string, int> keys = {

            {"Double attack", 0},
            {"Repeat attack", 1},
            {"Heal", 2},
            {"Paralyse enemy", 3}
    };

    constexpr int range = 4;    // 4 attack types

    int count [4] = {0, 0, 0, 0}; //  0 0 1 1
    std::vector <Monster> temp (monsters);

    for (auto &i : monsters)
        ++count [keys[i.attackType]];

    for (int i = 1; i < range; ++i)
        count[i] += count [i - 1];

    for (int i = monsters.size() - 1; i >= 0; --i) {

        temp [ count [ keys[monsters[i].attackType] ]  - 1] = monsters[i];
        --count [keys[monsters[i].attackType]];
    }

    monsters = std::move(temp);
}

void radixSort (std::vector <Monster> &monsters) {

    int max = 0;

    for (auto &i : monsters) {

        if (i.hp > max)
            max = i.hp;
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {

        std::vector <Monster> temp (monsters);

        int count [10] = {0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0};

        for (auto &i : monsters)
            ++count [(i.hp / exp) % 10];

        for (int i = 1; i < 10; ++i)
            count[i] += count[i - 1];

        for (int i = monsters.size() - 1; i >= 0; --i) {

            temp [count [(monsters[i].hp / exp) % 10] - 1] = monsters [i];
            --count [(monsters[i].hp / exp) % 10];
        }

        monsters = std::move (temp);
    }
}

void customSort (std::vector <Monster> &monsters) {

    using compareFunc = std::function <int (Monster, Monster)>;

    static std::map <int, compareFunc> compareParameters = {

            {1, [] (const Monster &lhs, const Monster &rhs) {

                return strcmp (lhs.name, rhs.name);
            }},

            {2, [] (const Monster &lhs, const Monster &rhs) {

                if (lhs.hp == rhs.hp)
                    return 0;
                else if (lhs.hp < rhs.hp)
                    return -1;
                else
                    return 1;
            }},

            {3, [] (const Monster &lhs, const Monster &rhs) {

                if (lhs.ap == rhs.ap)
                    return 0;
                else if (lhs.ap < rhs.ap)
                    return -1;
                else
                    return 1;
            }},

            {4, [] (const Monster &lhs, const Monster &rhs) {

                if (lhs.attackChance == rhs.attackChance)
                   return 0;
                else if (lhs.attackChance < rhs.attackChance)
                    return -1;
                else
                    return 1;
            }},

            {5, [] (const Monster &lhs, const Monster &rhs) {

                return strcmp(lhs.attackType, rhs.attackType);
            }},

            {6, [] (const Monster &lhs, const Monster &rhs) {

                if (lhs.timeInSec == rhs.timeInSec)
                    return 0;
                else if (lhs.timeInSec < rhs.timeInSec)
                    return -1;
                else
                    return 1;
            }}
    };

    menuOut ("- sort first", "- sort second");

    int choice, choice2;

    cin >> choice;
    cout << '\n';

    menuOut ("- sort second", "eof");

    cin >> choice2;

    if (choice2 < 1 || choice2 > 6)
       choice2 = choice;

    auto func = compareParameters [choice],
         func1 = compareParameters [choice2];

    std::stable_sort (monsters.begin(), monsters.end(),

            [&func, &func1] (const Monster &lhs, const Monster &rhs) {

                if (func (lhs, rhs) != 0)
                    return func (lhs, rhs) < 0;
                else
                    return func1(lhs, rhs) < 0;
    });

    cout << "\n\nSorted!\n\n";
}