# xanadu-cctl
*C语言模拟C++的模板库*



## 说明
此项目使用C语言模拟C++的STL模板库



### 功能
~~~
deque		: 模拟std::deque
list		: 模拟std::list
map		: 模拟std::map
queue		: 模拟std::queue
set		: 模拟std::set
stack		: 模拟std::stack
vector		: 模拟std::vector
~~~



## 注意
如果要提交拉取请求，请按以下格式编写代码。

set encoding=utf-8 with BOM

set tabstop=8

set shiftwidth=8



## 安装

### Linux

首先安装所有必需的依赖项和构建工具:
```shell
sudo apt install git
sudo apt install autoconf
sudo apt install automake
sudo apt install libtool-bin
sudo apt install cmake
```

解决所有依赖项:

*[libxanadu/xanadu-posix](https://github.com/libxanadu/xanadu-posix)*


然后克隆实际的项目存储库:
```shell
git clone https://github.com/libxanadu/xanadu-cctl.git
svn checkout https://github.com/libxanadu/xanadu-cctl/trunk
cd xanadu-cctl
```

现在您可以构建和安装它:
```shell
cmake .
make
sudo make install
```



## License

这个库是根据 [GNU Lesser General Public License v2.1](https://www.gnu.org/licenses/lgpl-2.1.en.html) 获得的许可，
存储库中也包含“许可证”文件。
