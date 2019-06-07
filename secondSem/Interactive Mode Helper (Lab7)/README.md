### Interactive Mode Creator 

Class Helper implements CLI for any function :

```C++
#include <Interactive.hpp>

Helper example {"Name", "Size"};

example.bind ([&fs] (std::string name, size_t size) mutable {
        fs.createFile (name, size) 
        };
        
example ();
```

   or
   
```C++
void createFile (std::string name, size_t size) {
        implementation...
        }
        
example.bind (createFile);

example ();
```

For collecting a lot of functions use Helpers or HelperContainer :

```C++
Helpers example = Helper {"Name", "Size"}
                | Helper {"Parent dir", "Name of new file"}
                | Helper {"File to rename", "New name"};
               
example.bind (createFile, [&fs] (std::string par, std::string rename) {
                                implementation... }, 
              [&fs] (std::string path, std::string name) {
                    impl... };
                    
example.launchAll ();
```
Also Helpers can be initialized in common way :

```C++
Helpers example = {Helper {"Name", "Size"},
                   Helper {"Parent dir", "Name of new file"},
                   Helper {"File to rename", "New name"}}
```                   

