LAB1\_INTRO: Introduction To Classes in C++[¶](#lab1_intro-introduction-to-classes-in-c "Permalink to LAB1_INTRO: Introduction To Classes in C++")
==================================================================================================================================================

Due date: **2025-03-17 23:59**.

The very first data structure you'll create is a `class` designed to store a single RGB pixel. The implementation of this class as well as two functions are missing from the set of files, classes, and functions that we provide to you below. Your assignment is to complete the missing parts.

Download The Provided Files[¶](#download-the-provided-files "Permalink to Download The Provided Files")
-------------------------------------------------------------------------------------------------------

Before you start working on your implementation, please make sure to download the necessary files from the provided link. The files can be found at [lab1\_intro.zip](https://drive.google.com/file/d/15SsYSsKAoOveFS2jYEbY0m9LiLk0K4je/view?usp=sharing).

Once you download the package, move it to your home directory in WSL. Next, you can uncompress the **.zip** file from Windows as you normally would, or from the WSL with:

unzip lab1\_intro.zip

However, you may not have zip/unzip installed yet:

sudo apt install zip

### Provided Files[¶](#provided-files "Permalink to Provided Files")

Once you uncompressed the provided file, the code for this lab will reside in the **lab1\_intro** directory. Get there by typing the following line in the terminal while in your working directory:

cd lab1\_intro/

You should have the following files in your **lab1\_intro** directory now:

*   **Makefile**
*   **main.cpp**
*   **png.h**
*   **png.cpp**
*   **rgbapixel.h**
*   **rhbapixel.cpp**
*   **sample.png**
*   **overlay.png**
*   **target\_output.png**

### References for the Linux Command Line and Text Editor[¶](#references-for-the-linux-command-line-and-text-editor "Permalink to References for the Linux Command Line and Text Editor")

If you need a refresher on the Linux command line and text editors refer to these resources for help:

1.  [Setup Instructions: Linux Command Line](https://lovelace.oulu.fi/c-programming/c-programming/cpp-lab-setup-instructions/#linux-command-line)
2.  [Setup Instructions: Text Editors](https://lovelace.oulu.fi/c-programming/c-programming/cpp-lab-setup-instructions/#text-editor)

Writing Your First Class: RGBAPixel[¶](#writing-your-first-class-rgbapixel "Permalink to Writing Your First Class: RGBAPixel")
------------------------------------------------------------------------------------------------------------------------------

Inside the provided files **rgbapixel.h**, **rhbapixel.cpp**, define a class called `RGBAPixel`. As you will use this class a lot throughout the next labs, its API is intentionally simple. The class should contain four `public` member variables:

*   `uint8_t red` denotes intensity value of the red color channel, with values ranging from 0 (no red) to 255 (maximum red).

*   `uint8_t green` denotes intensity value of the green color channel, with values ranging from 0 (no green) to 255 (maximum green)

*   `uint8_t blue` denotes intensity value of the blue color channel, with values ranging from 0 (no green) to 255 (maximum green).

*   `uint8_t alpha` denotes the alpha value, which represents the transparency of the pixel. A value of 0 indicates the pixel is fully transparent, while a value of 255 indicates the pixel is fully opaque.

Make sure that all of the members of the class are `public`. Following convention, the class definition should be placed in a file called **rgbapixel.h**, and the member function implementations should be placed in a file called **rgbapixel.cpp**.

Additionally, you need to implement two constructors for the `RGBAPixel` class:

*   `RGBAPixel()` The default constructor which initializes all of the member variables to 255.
*   `RGBAPixel(uint8_t _r, uint8_t _g, uint8_t _b)` The constructor which initializes the `red`, `blue`, and `green` variables to `_r`, `_g`, and `_b`, and `alpha` is set to 255.

Writing the PNG Manipulation Functions[¶](#writing-the-png-manipulation-functions "Permalink to Writing the PNG Manipulation Functions")
----------------------------------------------------------------------------------------------------------------------------------------

In this lab you will be tasked with implementing two functions within the **main.cpp** file, namely `brighten` and `blendImages`.

*   The `brighten` function brightens the PNG by increasing the components (red, green, blue) of each pixel by the given amount. You must account for potential overflow issues (color components can only store numbers between 0 and 255). If you attempt to store a value greater than 255 into a color component, the result will wrap around (and you won't be able to check if it was greater than 255).

*   The `blendImages` function blends, or averages, two PNGs together. That is, each pixel in the returned image consists of the averaged components (red, green, blue) of the two input images.

To give you an idea of how to write your own function, here's a sample function, which makes the original image more green:

    void getGreenComponent(PNG & original)
    {
       for (int x = 0; x < original.width(); x++)
       {
          for (int y = 0; y < original.height(); y++)
          {
             original(x, y).red = 0;
             original(x, y).blue = 0;
          }
       }
    }
    

Common Mistakes[¶](#common-mistakes "Permalink to Common Mistakes")
-------------------------------------------------------------------

To ensure that your code compiles, keep the following tips in mind. Remember to apply these tips not only while working on the current lab, but also in the future labs.

### Read the Instructions Carefully[¶](#read-the-instructions-carefully "Permalink to Read the Instructions Carefully")

Make sure to pay close attention to the specifications we've provided. To avoid compilation errors, check that the file names, executable names, program output, and public member functions are exactly as we asked. A single typo can result in a compilation error. Don't worry though, testing your code with the provided output will help you catch and correct such mistakes.

### Make Sure You Include Relevant Libraries[¶](#make-sure-you-include-relevant-libraries "Permalink to Make Sure You Include Relevant Libraries")

Make sure you define `uint8_t` type before declaring variables of this type. For that, you will want to include the standard library header file which contains the `uint8_t` type. You can include the header by doing the following in **rgbapixel.h**:

    #include <cstdint>
    using std::uint8_t;
    

If you don't do this you will probably get a compilation error about `uint8_t` not referring to a valid type. In the future, always make sure you include all of the relevant libraries in your code.

### Install libpng Library[¶](#install-libpng-library "Permalink to Install libpng Library")

If your Linux installation is missing `libpng` library, the code won’t compile until you install it:

sudo apt install libpng-dev

### Use Double Inclusion Guards in All Headers[¶](#use-double-inclusion-guards-in-all-headers "Permalink to Use Double Inclusion Guards in All Headers")

To avoid compilation errors resulting from the inclusion of header files multiple times, it's essential to use double inclusion guards. In the past, students have forgotten to include these, which resulted in compilation failures. Therefore, make sure to use double inclusion guards consistently to prevent any such errors.

Here's an example of how to use double inclusion guards for a header file named **myfile.h**:

    #ifndef MYFILE_H
    #define MYFILE_H
    // ... code goes here
    #endif
    

The first line checks if the macro `MYFILE_H` has not been defined before, which is true if this is the first time **myfile.h** is being included in the compilation process. If it's true, then the rest of the code in the header file is compiled. If **myfile.h** is included multiple times, the macro will already be defined, and the code within the `#ifndef` and `#endif` statements will be ignored.

It is important that you remember to use double inclusion guards for all header files you create. For example, make sure you use them in your **rgbapixel.h** file (with `RGBAPIXEL_H` replacing `MYFILE_H` for clarity).

Other Provided Files[¶](#other-provided-files "Permalink to Other Provided Files")
----------------------------------------------------------------------------------

There are other helpful functions in the files we provided that you might want to look at or use in your code. These are the `public` member functions of the `PNG` class that are defined in **png.h** and **png.cpp** files.

*   `image.resize(1024, 768);` // Changes the size of the PNG named image to be 1024 (width) by 768 (height) pixels.
*   `image.height();` // Returns the height of the PNG named image.
*   `image.width();` // Returns the width of the PNG named image.
*   `image(i, j).red = 255;` // Sets the red channel at coordinates (i, j) of the PNG named image to be 255.
*   `int red = image(i, j).red;` // Gets the value stored in the red channel at coordinates (i, j) of the PNG named image and stores it into the int named red.

Compiling the Code[¶](#compiling-the-code "Permalink to Compiling the Code")
----------------------------------------------------------------------------

To compile your code, type the following command into your terminal:

make

If there are no error messages generated on the screen, then your code compiled correctly.

Running the Code[¶](#running-the-code "Permalink to Running the Code")
----------------------------------------------------------------------

After compiling your code, an executable named **lab\_intro** should have been created in your working directory. You can now execute this file and test your code. To run the executable file use the following command prompt:

./lab\_intro

This will result in a png file named **output.png** created in your working directory. The easiest way to view the image is to open it in Windows.

Testing Correctness of Your Code[¶](#testing-correctness-of-your-code "Permalink to Testing Correctness of Your Code")
----------------------------------------------------------------------------------------------------------------------

After running the executable, an output file named **output.png** will be generated. To test your program for correctness, we have provided a correct output file with the name **target\_output.png** in the same directory. You can compare the two PNG files using the following command:

diff target\_output.png output.png

If your output file is correct, there should be no differences reported between the two files. If it is incorrect, keep in mind that the images have to match exactly, so follow the assignment instructions exactly and do not change the main function in a way that affects the output. Once you have confirmed the correctness of the output file, you can submit your solution to us below.

![?](/static/courses/unanswered-96.c79a8ca8ae72.png "You haven’t answered this exercise yet")

0.00 / 5

* * *

[0 answers](/answers/azuhayr23@oulu.fi/c-programming/c-programming/cpp_intro/ "View your previous answers")

[Frequently Asked Questions](/faq/c-programming/c-programming/cpp_intro/ "Open the FAQ panel")

Submitting Your Work[¶](#submitting-your-work "Permalink to Submitting Your Work")
==================================================================================

You can now upload your **rgbapixel.h**, **rgbapixel.cpp**, and **main.cpp** in the box below. To complete this lab, it isn't necessary to edit any other file.

Double check that you implemented the class called `RGBAPixel`, with public member variables `red`, `green`, `blue`, `alpha`, and two constructors. In **main.cpp** file you should have two new functions, `brighten` and `blendImages`.

Hints

<<

Allowed filenames: main.cpp, rgbapixel.cpp, rgbapixel.h

Submit your files here: 

Messages

Acknowledgments[¶](#acknowledgments "Permalink to Acknowledgments")
===================================================================

We would like to express our gratitude to prof. Cinda Heeren and the student staff of the UIUC CS Data Structures course for creating and sharing the programming exercise materials that have served as the basis for the labs used in this course.

Revised by: Elmeri Uotila and Anna LaValle

Give feedback on this content
=============================

Comments about the task?