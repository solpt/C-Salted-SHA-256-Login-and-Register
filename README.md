# C++ Salted SHA-256 Login and Register

This program allows users to register with a username and password which is salted and encrypted with SHA-256 (Using [OpenSSL](https://github.com/openssl/openssl)).

The data is stored in a text file called "users.txt" at the location of the program.
```
SolPT
;Y+ZVj:r/TL)(P8>]Nze^9`d-GcK'fO.
06a3dbd6e01e449c9525c7253cfbacc2a4971bf212decdf6f0d61bfea7f3ca67
```
The first line is the username, the second is the salt, and the third is the encrypted password.

## Requirements

[OpenSSL](https://github.com/openssl/openssl) must be built and then added to the "include" folder must be added to the dependencies of the dependencies of the project