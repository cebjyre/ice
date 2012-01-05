package main;

use sys;

func main() int32 {
    var arr *array[string];
    var msg string;

    arr = new array[string];

    sys.writeline("pushing message");
    msg = "Hello World";
    arr.push(msg);

    sys.writeline("popping message");
    msg = arr.pop();
    sys.writeline(msg);

    delete arr;
    return 0;
}

