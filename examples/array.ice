package main;

use sys;

func main() {
    var arr array[string];
    arr.push("Hello, World");
    sys.writeline(arr.pop());
}

