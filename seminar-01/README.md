# Introduction:  Linux, terminal, Bash, C


Linux is a family of open-source Unix-like operating systems based on the Linux kernel.

You can get acquainted with Linux kernel's source code here:
[Linux kernel](https://github.com/torvalds/linux)


<table width=100%> <tr>
    <th width=70%> Linux itself is not an operating system. It is the lowest layer of the operating system, and it provides basic hardware services. Linux operating systems are called Linux distributions. They are mostly installed on server computers. They are not popular among PC users. Note, that most of professional programmers and software-engineers are using linux. So it is must-have if you are interested in IT.
    </th> <th> <img src="os_layer.png" width="170"  height="160" align="right"> </th>
 </table>

After completing caos course, you can surely add Linux to your CV.

You can read more in Russian in [Yakovlev's reading](https://github.com/victor-yacovlev/fpmi-caos/blob/master/practice/linux_basics/intro.md)

## <a name="terminal"></a> Terminal, common commands

---
    folder == directory == catalog

`pwd` __-__ Print current directory

`cd`  __-__ Change the current directory:

`mkdir` __-__ Create a new directory:

`touch` __-__ Create a new file

`cp` __-__ Copy file/directory

`mv` __-__ Move file/directory or rename

`rm` __-__ Delete file, `rm -r` __-__ Delete directory recursively

`ls` __-__ List files and catalog in directory

*Options*

    ls -l

<img src="lsl.png" width="450"  height="40" align="centre" alt="Видео с семинара"> 

-----
    ls -a

<img src="lsa.png" width="450"  height="20" align="centre" alt="Видео с семинара"> 

------
    ls -la

<img src="lsla.png" width="450"  height="80" align="centre" alt="Видео с семинара"> 

--------------------------------------

`cat` __-__ Print the contents of a file

`head` __-__ Print the first 10 lines of a file, `head -n $count$` for fixed lines count

`tail` __-__ Print the last 10 lines of a file, `tail -n $count$` for fixed lines count

`>` __-__ Redirecting output to a file, **the file will be overwritten**

`>>` __-__ Redirecting output to a file, **the output will be added to the existing content**

`chmod` __-__ Change the permissions of a file or directory, `chmod +x`, `chmod -r`




