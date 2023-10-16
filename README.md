# RTIOW

Toy raytracer based on the [Ray Tracing in One Weekend Series](https://raytracing.github.io/).

## Installation

Tested on Ubuntu 22.4

```bash
mkdir build
cmake -B build -S .
cmake --build build
```

## Dependencies

Threading support requires [Intel Threading Building Blocks](https://www.intel.com/content/www/us/en/developer/articles/guide/get-started-with-tbb.html). To disable add cmake build flag `-DRTA_ENABLE_THREADS=0`
