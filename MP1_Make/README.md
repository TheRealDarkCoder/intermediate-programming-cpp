MP1\_MAKE: Makefile Tutorial[¶](#mp1_make-makefile-tutorial "Permalink to MP1_MAKE: Makefile Tutorial")
=======================================================================================================

Due date: **2025-03-17 23:59**.

Welcome to your first solo assignment! Unlike your lab assignments, you will work on and submit all MPs individually, without a partner. While you'll be working independently, remember that we are here to support you. Feel free to ask us questions about the MPs during labs or on Discord.

In this tutorial, you will:

*   Learn the basics of compiling C++.
*   Learn how to write a simple **Makefile**.

Introduction to Compilation[¶](#introduction-to-compilation "Permalink to Introduction to Compilation")
-------------------------------------------------------------------------------------------------------

Before proceeding with the tutorial, ensure that you have followed the setup instructions to install the proper work environment. Next, download and unzip the provided files for this tutorial from here: [mp1\_make.zip](https://drive.google.com/file/d/1L6pCMDmTNLhMmTgBgmYlJu69gJQVGWwk/view?usp=sharing).

In your **mp1\_make** directory you should have several directories: **animals**, **file\_meddling**, **functional\_fun**, **hello**, and **macro\_intro**. We will start with the directory **hello**:

cd mp1\_make/hello

This directory has a single file **hello\_world.cpp**. You can verify it by listing the contect of the directory with:

ls

Go ahead and open this file in your favorite text editor, and let’s walk through what it’s doing.

*   The first line includes the library `iostream`, the standard input/output (i/o) streams library. It’s not important that you understand it intimately, but you’ll use it a lot in the near future. More relevantly, it’s useful for the upcoming educational example on running the macro preprocessor.
*   Next, on line 3, we are defining a function called `main`. It is declared with empty parentheses, indicating that it takes no parameters. The function is specified to return an `int` value, which represents a return code indicating the success or failure of the program's execution. In the case of `main`, we have not explicitly written a `return` statement within the function. However, in C++, when the `main` function reaches the end without encountering a `return` statement, it is considered to have an implicit `return` statement with a return value of 0. This convention indicates a successful execution of the program.
*   On line 4, there’s a helpful and informative one-line comment.
*   Line 5 is the line that actually does the work. `std::cout` is a function from the library `iostream` that allows us to print something to the standard out stream. `<<` is the insertion operator (you’ll learn more about operators later; all you need to know now is that this is print statement syntax), and the string after, `"Hello, world!\n"`, is what we’re printing to standard out stream.

All in all, a very basic “_Hello, world_” implementation. Let’s try compiling it manually:

g++ hello\_world.cpp -o hello

The `-o` flag tells the compiler to give the executable an alternative name, **hello**. Otherwise, the default name of an executable is **a.out**.

Now you can run the executable with:

./hello

The **./** simply tells your shell to search the current directory for the executable **hello**, rather than its normal executable paths. If all goes well, you should see `Hello, world!` printed as output. But now let’s try to get a little more in-depth. You can delete the executable you just made by typing:

rm hello

And an

ls

should verify its disappearance.

### A Note on Modern Compilers[¶](#a-note-on-modern-compilers "Permalink to A Note on Modern Compilers")

Modern compilers (g++ 11 and higher) default to the C++17 standard, which we will teach in this course. You could explicitly instruct your compiler to use the C++17 standard by typing:

`g++ -std=c++17 hello_world.cpp -o hello`.

This command produces the same result as the default, assuming you have a modern C++ compiler and followed our [Laptop Setup Instructions](cpp-lab-setup-instructions/).

It is always good practice to explicitly specify the C++ standard your project is built with. For this reason, we will use the `-std=c++17` flag when creating a **Makefile** later in this document.

### Saving Temporary Files[¶](#saving-temporary-files "Permalink to Saving Temporary Files")

Run the following command:

g++ -save-temps hello\_world.cpp -o hello

The flag `-save-temps` tells the compiler to retain the temporary files it makes when we compile our program… so we can look at them! Listing the contents of your current directory should yield four new files: naturally the executable **hello**, but also **hello-hello\_world.ii**, **hello-hello\_world.s**, and **hello-hello\_world.o**, the temporary files we asked the compiler to save. These temporary files will be our guides into the slightly more technical aspects of basic compilation.

### Running the Macro Preprocessor: What Is ''hello-hello\_world.ii''?[¶](#running-the-macro-preprocessor-what-is-x27x27hello-hello_worldiix27x27 "Permalink to Running the Macro Preprocessor: What Is ''hello-hello_world.ii''?")

Run the following line:

g++ -E hello\_world.cpp -o preprocessed.ii

Then:

cat preprocessed.ii

If all goes well, your terminal will spit out a large amount of somewhat unintelligible code, but at the bottom, there’s the code for our “_Hello, world_” program (with the comment stripped out). So what did the preprocessor do?

All it really did for this program was replace our _include_ directive `#include <iostream>` with the actual text of the library we included (and, of course, strip the comment out).

What does that actually mean? Well, if you were capable of compiling this program at all, somewhere on the machine (be it virtual, remote, or physically present) that compiled it, there exists a file called **iostream**, which contains the C++ code that implements the i/o streams library. For gcc compilers, it’s in the directory where libstdc++ (libstdcxx) is installed. Don’t worry about the specific libraries, it doesn’t really matter, but if you were so inclined, you would be able to find the code on your own machine. There is no magic involved here.

Back to the preprocessed code. In this case, the only included library was **iostream**, but it would do exactly the same thing for any other included library. If you had a million include directives, it would go through those millions of lines, find each file you referenced, and tack it to your program, so that when you referenced a function or class defined in one of those standard library files, it would make sense to the compiler - like `std::cout` in this case, which is a function defined in **iostream**, that you wouldn’t have been able to use without including the code. Of course the preprocessor has plenty of other jobs as well, but we won’t cover them now.

Question: Why did we enclose the library name, **iostream**, in angle brackets? It’s not just so our code looks cooler - we could have said `#include "iostream"` too (feel free to try it out), so what’s the difference? The difference is that using angle brackets specifies that the preprocessor should look in the standard compiler include paths, and quotes tell it to search the current directory first, and via the standard paths only if that fails. Note that the true standard definition is a little more complicated than this: technically, both behave in an “implementation-defined manner” (any implementation could treat that differently if it so wished) but that’s not very important for us.

Now you can run:

cat hello-hello\_world.ii

Look familiar? That’s the output file the preprocessor dumped, and it is identical to the output you saw when you ran the preprocessor yourself. This is the file that the compiler really compiles - not your plain, unpreprocessed source file.

If you want to be sure, try running:

diff hello-hello\_world.ii preprocessed.ii

`diff` returns no output if the files it’s comparing are identical. Notice that if you produced the files **hello-hello\_world.ii** and **preprocessed.ii** using two different compilers, say, clang and gcc, they wouldn’t necessarily match!

### The Actual Compilation Step: What Is ''hello-hello\_world.s''?[¶](#the-actual-compilation-step-what-is-x27x27hello-hello_worldsx27x27 "Permalink to The Actual Compilation Step: What Is ''hello-hello_world.s''?")

Now let’s take a look at the next temporary file. Print the contents of **hello-hello\_world.s** by:

cat hello-hello\_world.s

For those of you who have seen assembly code before, the output should be recognisable. If you haven’t, assembly is the low-level intermediate between normal, higher-level programming languages like C++, and the machine code that your computer actually executes. In this case, the compiler (this is the step of compilation that’s actually called compilation) has translated the preprocessed source code from C++ to assembly, and dumped the output as **hello-hello\_world.s**. Let’s ask our compiler to directly compile the code that we preprocessed into assembly code:

g++ -S preprocessed.ii -o compiled.s

Use `diff` to verify that the files are the same:

diff hello-hello\_world.s compiled.s

There shouldn’t be any differences for gcc. With another popular compiler, clang, there would be a difference of one line in the files!

Question: Why don’t we just write everything in assembly language? Well, for one, it’s kind of annoying to write all the time, and higher level ideas are harder to keep abstract without our human-friendly programming languages. Perhaps more importantly, assembly isn’t portable in the slightest. Assembly languages are specific to a specific architecture, so what assembles and runs on my machine may not run without alteration on yours. That’s pretty annoying, and compilers work pretty well, so most people normally leave the assembly to them.

### Assembly: What Is ''hello-hello\_world.o''?[¶](#assembly-what-is-x27x27hello-hello_worldox27x27 "Permalink to Assembly: What Is ''hello-hello_world.o''?")

The next step is assembling the code - that just means translating the assembly code from **hello-hello\_world.s** into machine-readable code. That’s known as object code, and the standard suffix for object code is **.o**. Unlike **.s**, you’re likely to see quite a few **.o** files as you continue in this course. That doesn’t mean you have to read them, though. If you:

cat hello-hello\_world.o

you’ll quickly realize it would be a somewhat unrealistic expectation anyway.

If you want to ask your compiler to assemble your assembly code, you can do this:

g++ -c compiled.s -o assembled.o

Once again, you can use `diff` to verify that the assembled files are the same:

diff hello-hello\_world.o assembled.o

### Linking: Generating the Final Executable.[¶](#linking-generating-the-final-executable "Permalink to Linking: Generating the Final Executable.")

Linking is the final step, and arguably the most important and relevant to you. It’s the part you’ll interact with most, and besides perhaps flat out failure to compile at all, it’s the part of compiling you’ll be most confused by, particularly at the beginning of this class, when you’re responsible for all of your own compilation. Linking problems are some of the most notorious issues people have early on in this class… so pay attention to it, and perhaps you will be spared the “_undefined reference_” trauma.

Hint for the future: “_Undefined reference_” errors are pretty much always linking errors, and you will probably have them. Remember this.

All a linker does is take all the object files tossed out by the assembling step, and join them together into a single executable - in this case, the file **hello** which you ran earlier. We only have one object file in our “_Hello, world_” program, so this linking process is very uninteresting, but very soon (like, later in this tutorial), you’ll be dealing with multiple object files.

Run the following, to have the compiler link our object file and output our final executable, **hello\_manual**:

g++ assembled.o -o hello\_manual

Feel free to verify that it does exactly the same thing as our original executable, **hello**:

./hello\_manual
./hello

Congratulations, you’ve just compiled your own miniature program!

![?](/static/courses/unanswered-96.c79a8ca8ae72.png "You haven’t answered this exercise yet")

0.00 / 1

* * *



### Exercise 1[¶](#exercise-1 "Permalink to Exercise 1")

Copy and paste the result of running `diff hello hello_manual` on the two executable files:

Your Answer: 

Correct answer!  
1 / 1
That's right, these two methods result in the same executable, byte per byte! You now know the necessary steps for producing an executable program from c++ code.

  

Messages

Dealing with Multiple Object Files[¶](#dealing-with-multiple-object-files "Permalink to Dealing with Multiple Object Files")
----------------------------------------------------------------------------------------------------------------------------

Let’s visit the example directory **animals** now.

cd ../animals/
ls

The files you’ll see listed are **dog.hpp**, **dog.cpp**, and **main.cpp**. Feel free to check out the source code. **dog.hpp** is a C++ header file, what we’d call the definition of the `Dog` class, and **dog.cpp** is a source file, the implementation for said class. You’ll become more familiar with the details of that relationship as the class moves on, but right now, just know that together, they make the `Dog` class. **main.cpp** might look more familiar to you. It’s a lot like **hello\_world.cpp** from the last exercise, in that it has some `include`s and it has an executable `main` function. In that `main` function, it calls a constructor for the class `Dog`, and asks the object it creates to do a number of things. But including the `Dog` header file doesn’t actually make the source code available. First, compile the main object file:

g++ -c main.cpp -o main.o

Then, try compiling an executable **dog\_program**:

g++ main.o -o dog\_program

That’s what we did before for our “_Hello, world_” program, so what happened this time? You got a bunch of “_undefined reference_” errors, and if you remember what we said a few paragraphs up, “_undefined reference_” errors are pretty much always linking errors. The compiler’s telling us that it doesn’t know what the function `Dog::bark()` (or any `Dog` function) does, because it doesn’t have that information in **main.cpp**. The solution is to compile a separate object file for the `Dog` class. In general, you’ll have one object file per **.cpp** source file, compiled together with its header file (**.h** or **.hpp**) and other necessary dependencies. So let’s compile an object file for the `Dog` class.

g++ -c dog.cpp

And then:

ls

You’ll see that it added a new file called **dog.o** the object file for the `Dog` class (if you include the header in the compilation, you’ll also see a **.h.gch** or **.hpp.gch** file. The **.gch** file is a precompiled header; all that happens with that is in the future, for fulfilling an `#include "dog.hpp"` directive, the precompiled header is preferentially used). So now if we wanted to compile these together, we would do this:

g++ dog.o main.o -o dog\_program

And that should complete just fine. Try running it like so:

./dog\_program

But what happens if we start making changes to files? If we only change something in **main.cpp**, like the `Dog`’s name, we just have to run that final linking command again, and that’s easy. But if we change something in the `Dog` class itself, like adding a new function, or changing an implementation, we have to recompile the `Dog` object file, and then link it back to the main object file. That may not seem like a big deal now, but it gets annoying extremely fast when you have more than a single tiny class.

![?](/static/courses/unanswered-96.c79a8ca8ae72.png "You haven’t answered this exercise yet")

0.00 / 1


### Exercise 2[¶](#exercise-2 "Permalink to Exercise 2")

Copy and paste the _last line_ of the output after typing `./dog_program`:

Your Answer: `[Main] Location: (30, 10)`

Correct answer!  
1 / 1
  

Messages

Introducing the Program make[¶](#introducing-the-program-make "Permalink to Introducing the Program make")
----------------------------------------------------------------------------------------------------------

Those of you with some experience in compilation are probably aware of a common Unix utility called `make`. It’s a program extremely widely used on Unix based systems (Microsoft also has a Visual Studio spinoff called `nmake`), generally to build executable program files from source files. (Don’t let the “expected use” case fool you, though - `make` is not a program limited by the narrow realm of compilation, as you’ll see before this tutorial is over.)

The best instruction is by example, so let’s build a basic **Makefile** for our **dog\_program**. Create and open a new file called **Makefile** (make sure it’s with capital **M** - `make` will recognise the lowercase **makefile** as well, but our autograder won’t, so it’s good to get into the habit now) with your preferred text editor.

Makefile rules are written in the format:

    target : tgt_dependency1 tgt_dependency2 ...
    	command
    

So if our target is **dog.o**, what are the dependencies (the files needed to make the target)? They’re **dog.cpp** and **dog.hpp**, of course. And the command is the same as the one we used to compile the object file to begin with. So our rule for **dog.o**, the dog object file, will look like this:

    dog.o : dog.cpp dog.hpp
    	g++ -std=c++17 -c dog.cpp
    

Copy that into your new **Makefile**, and save it. Now let’s write a rule for **main.o**:

    main.o : main.cpp
    	g++ -std=c++17 -c main.cpp
    

Tabbing in Makefiles: Remember, the Tab is very important - if you don’t Tab the second line of a rule, you’ll get the error, `*** missing separator. Stop.` Don’t forget your Tabs!

Adhering to Best Practices: Notice we explicitly instruct the compiler to use the C++17 standard. This ensures consistency across environments and compilers, making it particularly valuable for collaboration and portability.

For the following demonstration of how your newly written **Makefile** works, you first have to clean up your directory and remove everything besides **dog.cpp**, **dog.hpp**, **main.cpp**, and **Makefile**, and then execute `make`.

rm \*.o dog\_program
make

If you `ls` now, you’ll see that it’s built the target **dog.o** (and left the precompiled header as well). But what is `make` doing?

### An Aside About the Order in Which Make Interprets Makefiles[¶](#an-aside-about-the-order-in-which-make-interprets-makefiles "Permalink to An Aside About the Order in Which Make Interprets Makefiles")

When called, `make` will search the current directory for a file called **Makefile** or **makefile** (again, for your sanity and grades, please only use **Makefile**, titlecase, with a capitalized **M**). If it finds one, it will execute the first rule in the file, and if one of the dependencies of the first target does not yet exist, it will search for a rule that creates it. So for example, if I have a **Makefile** like so:

    animal_assembly : moose goose cat
    	command
    moose : antlers hooves fur
    	command
    goose : beak wings webbed_feet interest_in_bread
    	command
    cat : whiskers evil_personality
    	command
    

then `make`, when called with no arguments, will attempt to build the target **animal\_assembly**. Assuming the dependencies **moose**, **goose**, and **cat** are already available in the directory, it will completely ignore the rules for them, and build **animal\_assembly** from what’s present. If **moose** and **cat** are available, but **goose** is not, it will note that **moose** is present, see that **goose** is not present, look for a rule to build **goose**, find the rule, build **goose**, and then note that **cat** is present and build **animal\_assembly**. If none of **moose**, **goose**, **cat** are present, it will have to build all of them using the rules available.

But what if you put the target for **moose** first?

    moose : antlers hooves fur
    	command
    animal_assembly : moose goose cat
    	command
    goose : beak wings webbed_feet interest_in_bread
    	command
    cat : whiskers evil_personality
    	command
    

Well, then if `make` is called with no arguments, it will make the target **moose** and stop. If you wanted it to make **animal\_assembly**, you would then have to call it like so:

make animal\_assembly

So a good rule of thumb is to put the final and most important command (for our purposes, the one that finally links the object files together into an executable) at the top.

Now back to our **dog** example. For our **dog** program, what the above means is that we should put the rule for the whole program at the top. How should we write it? Well, perhaps as you’d expect at this point:

    dog_program : dog.o main.o
    	g++ -std=c++17 dog.o main.o -o dog_program
    

Put that at the top of your **Makefile**, save it, and run `make` again.

make
ls

Now you should see the executable **dog\_program**, which should behave as it has in all previous post-compilation incarnations.

Now let’s do one final thing - in general, you should do this when writing your own **Makefile**s, but it’s especially useful for instructive purposes: we’ll write a `clean` rule.

    clean :
    	rm -f dog_program *.o
    

Add that to the bottom of your **Makefile** (as long as it’s not the top, it doesn’t really matter, but in long **Makefile**s, you want to separate the `clean` targets from real compilation-relevant targets for clarity), save it, and run `make` again, passing `clean` as an argument to invoke the `clean` rule:

make clean
ls

What happened? We’ve deleted all of the executables and compilation byproducts that we created, to clean up the directory. Note that, the flag `-f` flag in the `rm` command in the clean rule allows to ignore nonexistent files and arguments, preventing errors from stopping the clean process.

![?](/static/courses/unanswered-96.c79a8ca8ae72.png "You haven’t answered this exercise yet")

0.00 / 1

* * *


### Exercise 3[¶](#exercise-3 "Permalink to Exercise 3")

Copy and paste the _first line_ of the output after typing `make clean`:

Your Answer: `rm -f dog_program *.o`

Correct answer!  
1 / 1
  

Messages

The most notable thing about the above `clean` rule is that it (a) lacks a dependency list and (b) doesn’t perform any compilation-related tasks. Let’s discuss these two aspects in more detail.

### The Dependency List[¶](#the-dependency-list "Permalink to The Dependency List")

The dependency list you write for a target exists so that `make` knows what other targets to ensure you have before you run the command, but if the targets are guaranteed to be present and `make` isn’t responsible for updating them, `make` technically doesn’t need to check for anything. (It does not parse the actual command you give it, so it will not know what files to look for based on that.) Try deleting the dependency list of the target **dog.o**, and then running:

make clean
make dog.o

Since **dog.cpp** and **dog.hpp** are present in the directory, and `make` doesn’t have to rebuild them individually when they change (as it does for **dog.o**), `make` will have never have errors when compiling that line. But if you deleted the dependency list for the target `dog_program` and ran:

make clean
make

`make` will output an error that the `cannot find dog.o: No such file or directory`, because **dog.o** was not in the dependency list, and `make` therefore did not check to make sure it existed. As such, it didn’t bother to build it. As for including dependencies that `make` will never have to build (such as **.h**/**.hpp** and **.cpp** files), well, it’s simply good practice to document the dependencies of each target thoroughly. It’s cleaner for other people to read, and it’s a good way for you to confirm that you’re doing what you wanted to do, particularly late at night when the lines start to blur together. And now onto point (b).

### make Will Run Anything You Ask It To, Because It's Not as Smart as You Think It Is[¶](#make-will-run-anything-you-ask-it-to-because-itx27s-not-as-smart-as-you-think-it-is "Permalink to make Will Run Anything You Ask It To, Because It's Not as Smart as You Think It Is")

This is what we were referring to earlier, when we said `make` was not limited to compilation-related commands. Let’s move over to a different directory, for some `make`\-related messing about.

cd ../file\_meddling/
ls

As you can see, the **Makefile** is currently the only thing in this directory. It’s a very small and simple one, so open it up with your favorite text editor, and try guessing what it will do. It’s not compilation - it’s something altogether much sillier. When you have your prediction, execute `make`:

make
ls

And now there’s a new file in the directory. The command

cat silly\_file

will yield the somewhat accurate phrase “Hello, there is nothing important here” - I say somewhat because while the file and indeed the phrase itself are completely unimportant, the concept is, in fact, important. `make` is not a magical program that intuits the mysterious delicacies of compilation by parsing incomprehensible syntax and making anything more of it than what you yourself put there. `make` is simply executing the command you gave it, and it does so blindly, and without any particular personal interest in the results. Feel free to execute the following now:

make move\_file
ls

Now, when make executes the rule for the target `move_file`, it simply renames the file `silly_file` to something even more ungainly. And finally:

make delete\_file
ls

removes the file altogether. Usually a rule like this will be named `clean`, and it’s very acceptable to stick to that convention for the rest of your life. However, to illustrate that there is nothing magical about the target name `clean` (or indeed, any target name at all), in this **Makefile**, we are using the `clean` target to populate our directory with junk. Try it:

make clean
ls

Note that there are now multiple empty junk files (the directory is not cleaner), and feel free to remove them:

make really\_clean

(For the future, it is recommended that this educational example not be taken too deeply to heart. Conventions exist for a reason, and that reason is usually to make everybody’s lives easier. It is always worth knowing, though, that conventions are ultimately just that - conventions.)

Another important concept is understanding the control flow. In what order would the commands have to have gone in order to create a new file and fill it with text? Cheerfully, `make` will tell you what command it’s executing as it executes them, but don’t take that for granted. Walk through the **Makefile** yourself. In fact, let’s do it together.

The first rule you hit is the rule for the target `all`. `all` is a phony target, commonly used both in the real world and in our course, placed at the top of a **Makefile**, which, in its typical use case, will list all relevant targets which produce executables as dependencies. This ensures that `make` will compile all of the executables for which there are rules listed. In this case, we’ve just put it at the top because we can. It, of course, is not currently responsible for any executables. Test it by typing:

make all

When you read the rule for `all`, you see the dependency listed is `fill_file_with_nonsense`. Obviously **fill\_file\_with\_nonsense** doesn’t actually exist in the directory, so we skip down to the rule for `fill_file_with_nonsense`. The dependency listed is `create_file`, which also isn’t a real file, so we skip to the rule for `create_file`, which tells us it has no dependencies, and to `touch silly_file`. `touch` is a standard Unix program that can create, as we have done here, an empty file.

Once that’s done, we can finish up the rule to _build_ `fill_file_with_nonsense`, which pipes the string “_Hello, there is nothing important here_” into the newly created file **silly\_file**.

Then we can finish up _building_ the target `all`, for which the command is to print the string “_I have mostly created a lot of junk today!_” to standard out. And so it does. Take note that, of course, it _builds_ none of the targets that are not present in its direct control flow, so the unmentioned targets have to be explicitly passed as arguments to `make` in order for it to build them.

Just to be really clear, let’s add another rule to our **Makefile**. Open the **Makefile** in your text editor of choice, and write the rule `print_file`:

    print_file :
    	cat silly_file
    

Now run:

make print\_file

and it will print the contents of the silly\_file. Finally, we can clean things up:

make delete\_file

So hopefully now the basics are painfully clear. Let’s move on.

![?](/static/courses/unanswered-96.c79a8ca8ae72.png "You haven’t answered this exercise yet")

0.00 / 1


### Exercise 4[¶](#exercise-4 "Permalink to Exercise 4")

How many junk files (named **junk\***) were created in this exercise?

Your Answer: `7`

Correct answer!  
1 / 1

  

Messages

### Marvelous Macros[¶](#marvelous-macros "Permalink to Marvelous Macros")

Now let’s gloss over a basic component of makefile syntax that we’ve so far neglected to mention. Makefile syntax allows for a certain kind of variable called a macro. Macros are useful in a standard makefile essentially for the same reason that variables are useful in a normal program - they allow you to quickly define parts of your program which will appear repeatedly, and if you later to decide to change that part of the program, well, it’s a single change, rather than the countlessly many that are possible in large makefiles. In this class, you will never actually need macros to write an effective and mostly non repetitive makefile, but it’s not a bad habit to get into, so let’s see an example.

cd ../macro\_intro/

You may notice that our “_Hello, world_” example from ages ago has returned, and now we have a **Makefile** for it. Open up the **Makefile**. There’s some rather strange syntax in here, so let’s try to break it down.

First, we’ve defined a macro called `CXX`. Unfortunately, this is a _special_ macro, so we’re going to ignore it briefly and jump to `FLAGS`. `FLAGS` is a macro we defined to refer to the flags we’re passing our compiler; in this case, the flag is `-O`, an optimisation option that turns on a series of other flags which is not important for you to know right now (see the gcc compiler documentation for that information). `FLAGS` of course isn’t restricted in value to valid flags - we could have said `FLAGS = some moose have large antlers` and `make` would have been perfectly happy with that, until the call to the compiler failed later (you can try it out; `make` will actually try to execute `g++ some moose have large antlers hello_world.cpp -o hello`).

Now let’s talk about `CXX`. Not all macro names in the makefile language are entirely devoid of meaning - there is a certain set of names which do have a default meaning. In this case, we’ve defined `CXX = clang++`. This is a demonstration for you on how you could set up a different compiler (in this case, clang) in a Makefile. The `CXX` macro’s default value is usually `g++` on Linux systems, so if we never defined the macro `CXX`, when we used it in the command to compile the executable, it would have probably used `g++` instead. Try running `make` right now, and you should see the following output:

make
clang++ -O hello\_world.cpp -o hello

If you do not have clang compiler installed on your machine, you will probably get an error message `clang++: No such file or directory`. But if you delete the line that says `CXX = clang++`, what happens?

make
g++ -O hello\_world.cpp -o hello

Feel free to replace the line now back to the compiler you want to use.

Note: whenever you run `make`, do not forget to run `make clean` beforehand. Otherwise, you might get a message `make: 'hello' is up to date` or similar, as our Makefile is not added as a dependency to the build targets.

When you call a macro, enclose it like so: `$(MACRO)`. That’s simply makefile language syntax. (You may have noticed that my example macro’s name was all uppercase - as in fact, all of my macros thus far have been. This is not syntactically required, but it is conventional.)

So that explains most of what’s going on in this file, but the strange symbols `$?` and `$@` remain, perhaps, mysteries. As you might guess, those are also macros - they’re special predefined macros in the makefile language, with the respective meanings “_names of the dependencies (newer than the target)_” and “_name of the target_”, so in this case, `$?` refers to **hello\_world.cpp** (provided that you `make clean` before you `make`), and `$@` refers to `hello`, incidentally (purposefully) the name of the executable created as well. Using shorthand like this is a good motivation to name targets after the file the rule creates (this is, of course, also conventional, and increases the readability of your **Makefile**s drastically). Special predefined macros aren’t important for you to know - there are others we haven’t yet mentioned - but as you go about life in our course and the real world, you are bound to come across them.

Compiler and Linker Flags[¶](#compiler-and-linker-flags "Permalink to Compiler and Linker Flags")
-------------------------------------------------------------------------------------------------

For this class we are going to have a very standard set of flags to pass during compilation and linking. We are going to define these as macros in each assignment’s **Makefile**. Here is an example of what those look like (similar the Makefile in your **lab1\_intro**):

    # This defines our compiler and linker, as we've seen before.
    CXX = g++
    LD = g++
    
    # These are the options we pass to the compiler.
    # -std=c++17: This flag tells the compiler to use the C++17 standard. C++17 is a version of the C++ language standard, which includes several new features and improvements over the previous standards (like C++11 and C++14). Using this flag ensures that your code can use these features and that the compiler will enforce the rules of C++17.
    # -c specifies making an object file, as you saw before
    # -g specifies that we want to include "debugging symbols" which allows us to use a debugging program.
    # -O0 specifies to do no optimizations on our code.
    # -Wall, -Wextra, and -pedantic tell the compiler to look out for common problems with our code. -Werror makes it so that these warnings stop compilation.
    CXXFLAGS = -std=c++17 -c -g -O0 -Wall -Wextra -pedantic-errors -Werror
    
    # These are the options we pass to the linker.
    # -l<something>; tells the linker to go look in the system for pre-installed object files to link with.
    # Here we want to link with the object files from libpng (since we use it in our code).
    LDFLAGS = -lpng
    

A Final Diversion: The Makefile Language Is Turing Complete?[¶](#a-final-diversion-the-makefile-language-is-turing-complete "Permalink to A Final Diversion: The Makefile Language Is Turing Complete?")
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Limited the uses may be for such information, but particularly thanks to its support for lambda abstractions and combinators, the makefile language is actually a complete functional programming language. Will you ever need to write a Fibonacci number generator in the makefile language? Probably not, but you certainly can.

cd ../functional\_fun/
make

This will, of course, get quite slow as _n_ gets large (the naive solution takes exponential time), so I suggest you stop the process with a well timed Ctrl\-C as it begins to lag.

![?](/static/courses/unanswered-96.c79a8ca8ae72.png "You haven’t answered this exercise yet")

0.00 / 1

* * *


### Exercise 5[¶](#exercise-5 "Permalink to Exercise 5")

Copy and paste the _third line_ of the output after typing `make`:

Your answer: `1`

Correct answer!  
1 / 1
  
Messages

Acknowledgments[¶](#acknowledgments "Permalink to Acknowledgments")
===================================================================

We express our gratitude to prof. Cinda Heeren and the student staff of the UIUC CS Data Structures course for sharing the programming exercise materials that have served as the basis in this course.

Revised by: Elmeri Uotila and Anna LaValle

Give feedback on this content
=============================

Comments about this material