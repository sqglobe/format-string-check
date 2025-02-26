# Formatting  

This project demonstrates **parsing and validating format strings at compile time**. It is provided as a single header file: [format-string-check.h](./format-string-check/include/format-string-check.h).  

To format a list of parameters into a string, use the `format` function, as shown in the example:  

```cpp
format<"{} {}">(123, "aa");
```  

Placeholders **must** be `{}`, and **no additional formatting features are supported**.

If format isn't correct, than compilation error is rised.
