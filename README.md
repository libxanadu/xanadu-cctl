# xanadu-cctl
*Use C language to simulate the template library of C++*



## Explain
This project uses pure C language to simulate some functions in the C++ standard template library, such as containers.



### Function
~~~
deque		: simulate std::deque
list		: simulate std::list
map		: simulate std::map
queue		: simulate std::queue
set		: simulate std::set
stack		: simulate std::stack
vector		: simulate std::vector
~~~



## Note
If you want to commit any changes, write the code in the following format.

set encoding=utf-8 with BOM

set tabstop=8

set shiftwidth=8




## Comment format

```shell
/// Function description
/// \param _Value : Parameter explanation
/// \return : Return value description
```



## Installation

### Linux

First install all required dependencies and build tools:
```shell
sudo apt install git
sudo apt install autoconf
sudo apt install automake
sudo apt install libtool-bin
sudo apt install cmake
```

Resolve all dependencies:

[xanadu-posix](https://github.com/libxanadu/xanadu-posix)

Then clone the actual project repository:
```shell
git clone https://github.com/libxanadu/xanadu-cctl.git
svn checkout https://github.com/libxanadu/xanadu-cctl/trunk
cd xanadu-cctl
```

Now you can build and install it:
```shell
cmake .
make
sudo make install
```



## License

This library is licensed under the [GNU Lesser General Public License v2.1](https://www.gnu.org/licenses/lgpl-2.1.en.html),
also included in the repository in the `LICENSE` file.
