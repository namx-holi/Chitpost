

"""
create_random_word_files.py

Creates files in Words/ with random line count and line lengths.
Used for debugging main.c.

@author: namx-holi
@date:   2018-03-19
"""


from random import randrange
from math import ceil, log10
from os import path


number_of_files = int(raw_input("Number of files: "))
min_lines, max_lines = raw_input("Range of lines separated by space: ").split(" ")
min_line_length, max_line_length = raw_input("Range of line length separated by space: ").split(" ")

min_lines = int(min_lines)
max_lines = int(max_lines)
min_line_length = int(min_line_length)
max_line_length = int(max_line_length)

directory = "../Words_Test"

file_number_length = int(ceil(log10(number_of_files+1)))

for file_number in range(number_of_files):

	text_lines = []

	filename = "file_"+("{0:0>"+str(file_number_length)+"}").format(file_number+1)+".txt"

	line_count = randrange(min_lines, max_lines+1)

	for line_number in range(line_count):
		line_length = randrange(min_line_length, max_line_length+1)

		part = "line"+("{0:0>"+str(file_number_length)+"}").format(line_number+1)
		part_length = len(part)

		line = (int(ceil(1.0*line_length/part_length))*part)[:line_length]

		text_lines.append(line)

	f = open(path.join(directory, filename), "w")
	f.write("\n".join(text_lines))
	f.close()