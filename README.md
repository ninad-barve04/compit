# CompIt: File Compression algorithm

DSA-II project. Lossless Arithmetic encoder and compressor codec

## Installation

```sh
 # Clone this repository to a folder and navigate there
 make
 chmod -rwx ./CompIt
 # This is an optional step to make the command global
 sudo mv ./CompIt /bin/

```

## Running the command

```sh
#Tempelate
 ./CompIt <encode/decode> <input_filename> <output_filename>
```

```sh
 #For example, you want to compress the file audio.wav to compressed.comp
 ./CompIt encode audio.wav compressed.comp
```

```sh
 # To decompres the above file
 ./CompIt decode compressed.comp decoded_audio.wav
```

Maintain the file extension consistency for the original file and decoded output file

## Description

Though the project was done using audio compression as the main aim, using arithmetic encoding algorithm lead it to become a general encoder.

CompIt is a lossless compression program based on adaptive arithmetic encoding algorithm.

### Lossy vs Lossless Compression

|Lossy Compression|Lossless Compression|
|:---------------:|:------------------:|
|Size of the file is reduced by eliminating some information from the file|An intermediate file is created which is a compressed and encoded version of the original file|
|Final compressed output has lower resolution than original file|The compressed file has data stored in specific order so that the correct decoder can decompress the file|
|Usually used in image files, where a slight loss in resolution is preferable over a huge data storage overhead|Usually used in cases where we want the original file, but sharing the huge file size is costly. Also important to be used when encoding program files, text documents, code files, etc.|
|Eg. JPEG, MPEG for images, MP3, MP4 for audio-video files|Eg. GZIP, PNG, Huffman encoding, Arithmetic encoding, etc.|

### Lossless Compression Algorithms

Two major lossless compression algorithms

- Huffman Coding
- Arithmetic coding

Both algorithms fall in the category of entropy coding, where each symbol gets replace with a unique code.  
The length of the code is directly proportional to negative logarithm of probability of the symbol appearing in the file. (-log(probability of the symbol))

### Arithmetic Encoding

Arithmetic Encoding is a lossless algorithm, where frequently used characters will be stored with fewer bits and not-so-frequently occurring characters will be stored with more bits, resulting in fewer bits used in total.  
Arithmetic encoding differs from Huffman coding; rather than separating the input into component symbols and output the codewords to the file, the entire message is coded into a single number. The number is of theoretically infinite precision represented as between a fixed range.  
AE encodes the entire message (full file) using a single number between 0.0 and 1.0. Each symbol in the message takes a sub-interval in the 0-1 interval, corresponding to its probability

### Need for Infinite Precision number

Since the encoded output is a single number, it poses two drawbacks

- The number written in the output file should have a high precision representation
- While decoding, entire encoded file needs to be read to get complete number

For a long string, when we keep dividing the subintervals, the upper and lower bounds become too close to each other.

Normal systems do not have enough floating point precision to represent the bounds as distinct numbers.  
Both effectively become the same number and encoder fails to subdivide the interval further; this results in a failure to decode the symbol.

### Handling the infinite precision requirement

On observing the subinterval bounds in the output, we see that the MSB of both bounds are same after few iteration.

The MSBs are now not required in the encoding process and can be ignored.  
These MSBs are written out to the compressed/encoded file.  
The bounds are left-shifted for every MSB written out, thus increasing the range and thus improving the precision.  

This improvement in precision is due to shifting out the MSB into output, actual precision of the float/double does not change.

In reference to
[Practical Implementations of Arithmetic Coding by Paul G. Howard and Jeffrey Scott Vitter, Brown University, Rhode Island](https://www.ittc.ku.edu/~jsv/Papers/HoV92.actech.pdf)
an alternative method for maintaining precision is used

For the upper and lower bounds, when the MSBs are same, those are written to decoded file and the bounds are modified such that the modified bounds spans across ¼-¾ of the range, thus maintaining sufficiently spaced bounds this maintaining accuracy

## References

- Compression and Decompression of Audio Files Using the Arithmetic Coding Method by Parasian D.P Silitonga and Irene Sri Morina, in Scientific Journal of Informatics  
[https://journal.unnes.ac.id/nju/index.php/sji/article/view/17839](https://journal.unnes.ac.id/nju/index.php/sji/article/view/17839)
- Practical Implementations of Arithmetic Coding by Paul G. Howard and Jeffrey Scott Vitter , Brown University  
[https://faculty.cc.gatech.edu/~jarek/courses/7491/Arithmetic2.pdf](https://faculty.cc.gatech.edu/~jarek/courses/7491/Arithmetic2.pdf)
- Lossless Data Compression Using Arithmetic Encoding in Python  
[https://neptune.ai/blog/lossless-data-compression-using-arithmetic-encoding-in-python-and-its-applications-in-deep-learning](https://neptune.ai/blog/lossless-data-compression-using-arithmetic-encoding-in-python-and-its-applications-in-deep-learning)
- Data Compression With Arithmetic Coding : Mark Nelson  
[https://marknelson.us/posts/2014/10/19/data-compression-with-arithmetic-coding.html](https://marknelson.us/posts/2014/10/19/data-compression-with-arithmetic-coding.html)
