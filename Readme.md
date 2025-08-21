# Bencode Decoder

A simple C bare bones implementation of a Bencode decoder that converts Bencode-encoded data into a human-readable JSON-like format.

## What is this project?

This is a learning project that implements a parser for the Bencode encoding format. Bencode is a simple encoding format used primarily by the BitTorrent protocol to store and transmit data. This decoder reads Bencode-encoded files and outputs them in a readable format.

## What can it parse?

The decoder supports all standard Bencode data types:

- **Integers**: `i42e` → `42`
- **Byte strings**: `4:spam` → `"spam"`
- **Lists**: `l4:spami42ee` → `["spam", 42]`
- **Dictionaries**: `d3:cow3:moo4:spam4:eggse` → `{"cow": "moo", "spam": "eggs"}`

The parser can handle nested structures of arbitrary complexity, including lists within dictionaries and dictionaries within lists.

## How to build and run

### Prerequisites
- GCC or any C compiler
- Standard C library

### Building
```bash
gcc -o bencode_decoder main.c
```

### Running
```bash
./bencode_decoder <filename>
```

Where `<filename>` is a file containing Bencode-encoded data.

### Example
```bash
# Create a test file
echo "d4:name4:John3:agei25ee" > test.bencode

# Run the decoder
./bencode_decoder test.bencode
```

Output:
```
String:
{"name": "John", "age": 25}
```

## Project Structure

```
├── main.c          # Main source file containing the decoder implementation
└── README.md       # This file
└── bc.txt          # example bencode file

```


## Learning Outcomes

This project demonstrates:
- **File I/O operations** in C
- **Dynamic memory management** with malloc/realloc
- **String manipulation** and parsing
- **Recursive parsing** for nested structures
- **Error handling** and edge cases

## Bencode Format Quick Reference

| Type | Format | Example | Output |
|------|--------|---------|--------|
| Integer | `i<number>e` | `i42e` | `42` |
| String | `<length>:<string>` | `4:spam` | `"spam"` |
| List | `l<contents>e` | `li42ee` | `[42]` |
| Dictionary | `d<contents>e` | `d3:keyi1ee` | `{"key": 1}` |

## Limitations

- Currently outputs to stdout only
- No JSON formatting (pretty printing)
- Limited error messages for debugging malformed input
- Dictionary key-value separation not implemented in output formatting

## Resources

- [Bencode Specification](https://en.wikipedia.org/wiki/Bencode)
- [BitTorrent Protocol Specification](http://bittorrent.org/beps/bep_0003.html)

---

**Note**: This is a learning project created to understand parsing techniques and the Bencode format. It may not be suitable for production use without additional testing and error handling.