# RSAAES-Implementation
This is a manual implementation of A hybrid cryptoscheme.

As a use case, parties would exchange a private key with the RSA algorithm with whom they wanted to communicate with secretly.
After all parties have agreed on a private key, they are then free to encrypt/decrypt messages with the AES algorithm for encryption 
and decryption.

This implementation is not perfect - for a more in depth information please read the pdf architecture description -,
the current RSA implementation is not efficient enough for practical use (512bit), the AES implemenation is not exact; to have
working encryption/decryption I had to remove the byte substitution from multiple steps, I believe this might be due to 
a carried bit being lost, but more testing is required to find where exactly a bit is being lost.
