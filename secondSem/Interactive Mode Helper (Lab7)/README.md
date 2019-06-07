<h2>Interactive Mode Creator </h2>
________________________________________________________________________________________________

Class Helper implements Interactive mode in command line for any functions except generic lambdas :

```C++
#include "Interactive.hpp"

Helper example {"Name", "Size"};

example.bind ([&fs] (std::string name, size_t size) mutable {
        fs.createFile (name, size) 
        std::cout << "File created succesfully!\n";
        };
```  
or

```C++
void createFile (std::string name, size_t size) {

        ...implementation...
        std::cout << "File created succesfully!\n";
        } 
        
example.bind (createFile);
```

To start interacting use operator ():  `example ();`

Output:

```C++
Name : user input
Size : user input

File created succesfully!
```

For collecting a lot of functions use special container for Helpers:
```C++
Helpers example = Helper {"Name", "Size"}
                | Helper {"Parent dir", "Name of new file"}
                | Helper {"File to rename", "New name"};
               
example.bind (createFile, [&fs] (std::string par, std::string rename) mutable {
                                implementation... }, 
              [&fs] (std::string path, std::string name) mutable {
                    impl... };
                    
example.launchAll ();
```
Also Helpers can be initialized in common way :

```C++
Helpers example = {Helper {"Name", "Size"},
                   Helper {"Parent dir", "Name of new file"},
                   Helper {"File to rename", "New name"}}
```                   