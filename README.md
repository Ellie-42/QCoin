# QCoin
A highly secure and resilient cryptocurrency. The name is still being vetted. QuantumCoin, but its too close to Qunata...

The coin is designed with two things in mind. Be resistant to quantum computer attacks and prevent ASIC miners from taking over the network.

The public key signature scheme is still up for debate, but will use either Dilithium or Rainbow, both NIST contenders for the Post Quantum Computing challenge.

The PoW algorithm is of custom origin, utilizing a rotating hash scheme, witha wrapping of a 128bit hash.
The round one hash is detirmiend from the block index, picking between Skein-512, Blake2b, SHA-3, and SHA-256
The round two hash is based off the last character of the base58 encoded hash from the previous block, and thi sone can pick between Balke2b (256 bits), SHA-256, Whirlpool, or SHAKE-256
Then, the final hash is SHAKE-128 to wrap up the hash into a short value to reduce overall blocksize.

this rotating scheme, which I will call Rot42 henceforth, completely prevents ASICS from working because the amount of chips necessary to exist in a single machine would make them not only too expensive, but too power hungry as well, as there would be no way to predict the next hash set for the next future block until the current block is verified.

This is also sbject to change to further secure against ASIC machines while still permittign GPU miners, wher the algortihm may turn from index then previous block hash to the previous block's hash plus the resulting hash fromt he round one hash.

While detirministic once values are known, this further increases security by forcing a possible attacker to not only calulate a new hash, but two changing types of hashes for each block, which creates a very obvious deviance from the proper chain very quickly.

Block times are every minute, with the difficulty changing every five blocks (subject to change)

Block rewards are to be detrimiend, as is the supply cap.
As this is intended to be a daily use coin, the block rewards will be initially high, and decrease over time, while encorageing high transaction fees to secure both the network and ensure longevity.

This is also a mere proof of concept at the moment.

It utilizes both JsonCPP and Botan, s packaged from MSYS2, and using the MSYS2 Mingw-w64 compiler. My IDE is code::blocks at the moment.
This will change as i work out the fine details of the coin and move more production level code.

Also as the Peoples Coin of Tomorrow, any recommendations and pull requests will be taking into heavy regard.
Also, in the nature of security, there will be two protocols regarding transaction broadcast.
If designated to be a "Secure" transaction, the transaction can only be sent OVER the TOR network to a node that exists on the TOR network. 
Also in the nature of anomity, the transaction data will be secured using the TOR node's .onion address. Due to the nature of TOR networks, these fees may be increased to accomdate server uptime, security against attacks, etc.

The first 100,000 blocks will be premined by the those who contributed most, to both build a supply and to encourage contribution to the project.

The wallet address public keys will be prefixed with the base58 equivalent of "QCO" + the address scheme revision, i.e. the intial wallet address will be prefixed with the bsae58 equivalent of "QCO0"

All the code will be written in C++, as much as possible, for speed, portability, and such. This is not to turn awya a python implementation either, as those are absolutly encourage.
I just prefer C++ for its use of headers and soruce files to help distinguish code from one another. This is helpign to build a robust core that permits a fast and simple change where needed.
