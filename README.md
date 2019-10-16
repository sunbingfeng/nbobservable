Welcome to nbobservable
============

**nbobservable** is a light-weight implemention of observer pattern in cpp. It only contains a single header file and it's easy to integrate to your project. 

"nb" can be pronounced as "NiuBi" in Chinese, and means strong and powerful. Hope it may be of some help.

Prerequisites
------------
1. Boost signals2

Usage
------------

We provided a simple demo to demonstrate how to use **observable** module in *main.cpp*. You can build&run to have a quick view of it.

```bash
# build
cd {nbobservable_dir}

mkdir build && cd build
cmake ..

# run
./nbobservable_app
```
- Define your custom class derived from **nbobservable::Observable**.

Observable is a template class, and T stands for function prototype of observer slot. Arguments passed to the slot are defined in your custom class, and observers should obey to it.

- Call **registerObserver** interface to add observer by each operation.

A handler responding to newly created slot connection is returned after this call, and you can pass it to **removeObserver** function to disconnect this slot.

- Call **removeObserver** to remove one observer, or **clearAllObservers** to disconnect all connections.

