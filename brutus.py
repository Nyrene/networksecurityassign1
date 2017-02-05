# Allen Montgomery
# Network Security
# Brute Forcing Hash Collisions given a weak Hashing Algorithm

import string
import random
import subprocess

counter = 0
file1 = open('file1.txt', 'w')  # Open file1 with a Write switch
file2 = open('file2.txt', 'w')  # Open file2 with a Write switch
hash1 = ''
hash2 = ''
norwichhash = 'norwichhash.exe' # Hansens hash function

# Returns a String of 8 random characters and letters combined
def generator(size=8, chars=string.ascii_letters + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

# Keep file1 a static random generated string so we can brute force file2 to match it
file1.write(generator())

# Calls Hansens hash function on file1 and stores it in hash1
hash1 = subprocess.call([norwichhash, "file1.txt"])
print() # Only here for new line

while True:
    # Do the same to file 2 in a loop until the hash equals the same
    file2.write(generator())
    hash2 = subprocess.call([norwichhash, "file2.txt"])
    print()

    # When the hashes are equal print them off and break out
    if hash1 == hash2:
        print('[*] Collision Detected!')
        break

# Close files and print done
file1.close()
file2.close()
print('Done!')