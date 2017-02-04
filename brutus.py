# Allen Montgomery
# Network Security
# Brute Forcing Hash Collisions given a weak Hashing Algorithm

import string
import random
import subprocess
import io
import os

counter = 0

file1 = open('file1.txt', 'w')  # Open file1 with a Write switch
file2 = open('file2.txt', 'w')  # Open file2 with a Write switch
hash1 = ''
hash2 = ''
hashlist = []
norwichhash = 'norwichhash.exe' # Hansens hash function

# Function that returns a String of 8 random characters and letters combined
def generator(size=8, chars=string.ascii_letters + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

# Keep file1 a static random generated string so we can brute force file2 to match it
file1.write(generator())

# 4000 is a solid number, maybe
while counter <= 4000:
    # When the hashes are equal print them off and break out
    if hash1 == hash2:
        print('[*] Collision Detected!')
        print(hash1 + ' ' + hash2)
        break
    # Otherwise we are going to iterate through and change file 2 over and over
    else:
        string2 = generator()
        file2.write(string2)
        counter += 1

# Close files and print done
file1.close()
file2.close()
print('Done!')