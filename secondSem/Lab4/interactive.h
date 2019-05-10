#include <functional>
#include <optional>
#include <thread>
#include <regex>
#include <map>

using std::cin;
using std::cout;


void msg () {

    cout << "\n****************************\n"
         << "          Done!             \n\n";

    std::this_thread::sleep_for (0.8s);
}

void interactive (Filesystem &fs, bool show) {

    static std::map <int, std::function <void ()>> funcs {

            {1, [&fs, show] {

                std::string path, name;

                cout << "Enter path to parent directory : ";
                cin >> path;

                if (show) {
                    cout << path << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                cout << "Enter name :";
                cin >> name;

                if (show) {
                    cout << name << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                if (fs.findDirectory (path))
                    fs.createDir (path, name);

                else {
                    cout << "No such directory!\n";
                    return;
                }
                msg();
            }},

            {2, [&fs, show] {

                std::string path, name;
                int size;

                cout << "Enter path to parent directory : ";
                cin >> path;

                if (show) {
                    cout << path << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                cout << "Enter name of file : ";
                cin >> name;

                if (show) {
                    cout << name << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                cout << "Set file size in bytes : ";
                cin >> size;

                if (show) {
                    cout << size << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                if (fs.findDirectory (path))
                    fs.createFile (path, name, size);
                else {
                    cout << "No such directory!\n";
                    return;
                }
                msg();
            }},

            {3, [&fs, show] {

                std::string path;

                cout << "Enter path to directory/file : ";
                cin >> path;

                if (show) {
                    cout << path << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                if (fs.findDirectory (path))
                    fs.findDirectory (path)->info();

                else if (fs.findFile (path))
                    fs.findFile (path)->info();

                else {
                    cout << "No such file or directory!\n\n";
                    return;
                }

                std::this_thread::sleep_for (0.8s);
            }},

            {4, [&fs, show] {

                std::string path;

                cout << "Enter path to directory / file : ";
                cin >> path;

                if (show) {
                    cout << path << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                if (fs.findDirectory (path))
                    fs.deleteDir (path);

                else if (fs.findFile (path))
                    fs.deleteFile (path);

                else {
                    cout << "No such file or directory!\n\n";
                    return;
                }

                msg();
            }},

            {5, [&fs, show] {

                std::string name;

                cout << "Enter name of directory/file : ";
                cin >> name;

                if (show) {
                    cout << name << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                auto found = fs.findByName (name);

                cout << "Found : \n";

                for (auto &i : found)
                     cout << '\t' << i << '\n';

                std::this_thread::sleep_for (0.8s);
            }},


            {6, [&fs, show] {

                std::string path;

                cout << "Enter path to directory : ";
                cin >> path;

                if (show) {
                    cout << path << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                if (fs.findDirectory(path))
                    fs.findDirectory(path)->showAll();

                cout << '\n';
            }},

            {7, [&fs, show] {

                std::string name;

                size_t minSize,
                       maxSize;

                cout << "Enter regular expression to filter by name or enter \"exit\" to skip\t";
                cin >> name;

                if (show) {
                    cout << name << '\n';
                    std::this_thread::sleep_for (0.6s);
                }


                std::optional <std::regex> optName ((name == "exit") ? std::nullopt : std::optional (name));

                cout << "Set minimal size\t";
                cin >> minSize;

                if (show) {
                    cout << minSize << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                cout << "Set max size or 0 to skip\t";
                cin >> maxSize;

                if (show) {
                    cout << maxSize << '\n';
                    std::this_thread::sleep_for (0.6s);
                }

                std::optional <size_t> optMaxSize ((maxSize == 0) ? std::nullopt : std::optional (maxSize));

                fs.filter ({optName, optMaxSize, minSize});

                msg();

                if (show)
                    exit (0);
            }}
    };


    cout << "\n\n    1. Create new directory.\n"
            "    2. Create file.\n"
            "    3. Get directory / file info.\n"
            "    4. Delete directory or file.\n"
            "    5. Get path by directory/file name.\n"
            "    6. Show all in directory.\n"
            "    7. Filter directories and files\t";

    int choice;

    do
        std::cin >> choice;
    while (choice < 1 || choice > 7);

    if (show) {
        cout << choice << '\n';
        std::this_thread::sleep_for (0.6s);
    }

    cout << '\n';
    funcs [choice] ();
}

void binaryInteractive (BinaryTree <int> &tree) {

    static std::map <int, std::function <void ()>> funcs {

            {1, [&tree] {

                int number;
                cout << "Integer to add : ";
                cin >> number;

                tree.push (number);
                msg();
            }},

            {2, [&tree] {

                tree.print();
                std::this_thread::sleep_for (0.8s);
            }}
    };

    cout << "\t1. Add element.\n"
         << "\t2. Print tree. \n";

    int choice;
    do
        cin >> choice;
    while (choice < 1 || choice > 2);


    funcs [choice] ();
}