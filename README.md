# qxLib
OpenGL header-only support library for making your own engine

Dependencies:
+ C++17
+ glew if you want to use gl module

## Directories

+ __containers__. Expansion of standard stl containers.
  + _iterator_. Lite and simple iterator implementation.
  + _object_pool_. Contains a collection of reusable objects. When the pool is initialized, it immediately creates the entire collection of objects (allocating one consecutive chunk of memory) and initializes them all with the “not used” state. When you need a new object, you request it from the pool. It searches for an accessible object, initializes it with the value "used" and returns. When the object is no longer needed, it returns to the "unused" state again. In this way, objects can be freely created and deleted without having to allocate memory or other resources.
  + _string_. Lite string with sizeof() == 1. Supports .format(), to(type()), split(), delete_line_breaks(), apply_case() and other useful methods.
  + _container_. Macro with common container methods. 
  + ...

+ __gl__. Class wrappers for OpenGL entities.
  + _buffer_base_
  + _ebo_
  + _fbo_
  + _rbo_
  + _ssbo_
  + _ssbo_arrayed_
  + _ubo_
  + _vao_
  + _texture_
  + _shader_
  + _shader_program_
  + ...
  
+ __other__. 
  + _asserter_. Multiplatform ASSERT() and ASSERT_MSG() macros.
  + _hashes_. Hashes implementations.
  + _logger_. Logging system. Provides console and file output, enabling and disabling logging for custom files and functions.
  + _noncopyble_. Base class for noncopyble objects.
  + _singleton_. Mayers singletone macro.
  + _smart_enum_. Smart enum macro. Provides ToString(), FromString(), increment operations.
  + _typedefs_. Types defines.
  + _useful_funcs_. 
  + _useful_macros_. 
  
## Todos:
  + tests
  + basic algorithms
  + basic data structures
  + renderer: interface, scene node, scene graph, cullings
  + Protected value: defence from cheat engine, artmoney etc
  + gl classes improvements
  
## License

qxLib is available under the GNU General Public License v3.0. See LICENSE.txt.


## Authors

qxLib was mainly written and is maintained by Nick Khrapov
(nick.khrapov@gmail.com). See the git commit log for other authors.
