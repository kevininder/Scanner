# Scanner
Scanner acts as a translator between raw program text and the compiler. It reads a stream of characters and identifies meaningful words and symbols, and transforms them into a structured sequence of tokens that can be easily understood, or used in later stages.

## Introduction
1. Scanner takes in a string file path and yields a result in vector data structure with a custom type FileInfo.
2. Scanner accpets C family files, or cpp/c, hpp/h.
3. Scanner is of a utility function, and hence it is thread safe.
4. Scanner lacks complete semantic information of your project, use it at your own risk.
5. Scanner requires additional information regarding your custom defined data type. Please define those in the Table.txt. Note that anything that is supposed to be a DataType but without a proper definition beforehand will be an identifier by default. More in Misc. section.
6. Scanner throws an exception when any unrecognizable token is detected.
7. Scanner falls short of cpp related keywords.

## Misc.
1. To add your own data type, you can either enter it into the Table.txt with a new line character, see the file for details, as a runtime option, or insert it into the gDataTypes as a compile-time choice.
2. FileInfo contains helpful information, e.g. Type, Content, Row and isHead, for each token.
-Type: There are ten types, including the invalid type.
-Content: For what the token really is.
-Row: Literally the row number you see in an IDE.
-isHead: This member variable makes the vector a map-like data structure.