# hello-c-extension

Showcase use and packaging of a C++ extension module.

```bash
$ python -m pip install hello-c-extension
```

Use:

```python
>>> from cmod import CONSTANT, pymod, _cmod
>>> CONSTANT
10
>>> pymod.hello()
Hello from Python!
>>> _cmod.foo()
5
>>> pymod
<module 'cmod.pymod' from '.../site-packages/cmod/pymod.py'>
>>> _cmod
<module 'cmod._cmod' from '.../site-packages/cmod/_cmod.cpython-37m-x86_64-linux-gnu.so'>
```
