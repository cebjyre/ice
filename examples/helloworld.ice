package main;

use sys as Sys;

func say_hello() {
    Sys.writeline(1.str());
    Sys.writeline("Hello, World!");
}

func main() int32 {
    say_hello();
    return 0;
}
