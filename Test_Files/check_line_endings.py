#!/bin/python
# -*- coding: utf-8 -*-

"""
check_line_endings.py

Just displays each character and the bytes of the character

@author: namx-holi
@date:   2018-03-19
"""


filename = raw_input("Filename: ")

f = open("../Words/"+filename, "r")
text = f.read()
f.close()

for character in text:
	print("char: %s" % character)
	print("byte: %d" % ord(character))

	print("")

