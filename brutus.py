# Allen Montgomery
# Network Security
# Assignment 1
# February 10, 2017
# Brute Forcing Hash Collisions given a weak hashing algorithm
# For use on unix, not Cortana-malware-infested machines
# Writes a string to file1, hashes it, then bruteforces file2 and hashes it, until hashes match
# Depending on character set and length of keyspace, could run until human extinction

# Deliverable 1
# This program successfully detects the weaker collision quickly as evident in:
# 10101110  -> e7e97c8c
# 11111111  -> e7e97c8c

# Deliverable 2
# The weakness in the --strong algorithm lies within the 5th and 6th bytes, being independent of the rest
# aaaaaaaa
# aaaabbaa  Should hash to the same value
# Hash list with several matching hashes is included in text file

import string
import random
import subprocess
import itertools

# VARIABLES #

chars = '10'
#chars = 'abcdefghijklmnopqrstuvwxyz0123456789'     # Whatever characters you want to bruteforce, can also use string.ascii_
file1 = open('./file1.txt', 'w')                    # 'w' is write, 'a' is append, r+ is read/write
hash1 = ''                                          # These will store the output of the hash function for comparison
hash2 = ''
output1 = ''
output2 = ''

# METHODS #

# Generator returns a String of 8 random characters and letters combined
# note: ascii_uppercase and ascii_letters add more entropy, size can be changed
def generator(size=8, charset=string.ascii_lowercase + string.digits):
    return ''.join(random.choice(charset) for _ in range(size))

# Pass filename in pfile to delete the entire contents of any file if needed
def deleteContent(pfile):
    pfile.seek(0)
    pfile.truncate()

# Bruteforce algorithm takes a character set and produces
# aa, ab, ac, ad ... aab, aac, aad... etc based on input length
def bruteforce(charset, maxlength):
    return (''.join(candidate)
        for candidate in itertools.chain.from_iterable(itertools.product(charset, repeat=i)
        for i in range(1, maxlength + 1)))

# MAIN #

# Throw an initial value in file1.txt, just to get a hash... whatever you want
file1.write('10110100')

# Run commands in the shell, produces byte code, convert it to a string and save in the hash
# Obviously add --strong in string after ./a.out for stronger hash function, remove for deliverable 1
output = subprocess.Popen(['./a.out file1.txt'], shell=True, stdout=subprocess.PIPE)
hash1 = output.communicate()[0]
hash1 = hash1.decode()
print(hash1 + ' | Hash1')

# Write to file2 the bruteforce method and check each time to see if the hashes match
# WARNING
# Keep the length low, or the character list low unless you want to create hashes until the heat death of the universe
for attempt in bruteforce(chars, 8):
    if hash1 == hash2:
        print('\n[*] Collision Detected!')
        break
    else:
        with open("file2.txt", 'w') as file2:
            file2.write(attempt)
        output2 = subprocess.Popen(['./a.out file2.txt'], shell=True, stdout=subprocess.PIPE)
        hash2 = output2.communicate()[0]
        hash2 = hash2.decode()
        print(hash2 + ' | Hash2')

# Close files, all done file2 should already be implicitly closed from the with statement
file1.close()
file2.close()
print('Done!')