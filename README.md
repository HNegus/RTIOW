# RTIOW

```bash
mkdir build
cmake -B build -S .
cmake --build build
```

## Dependencies

Threading support requires [Intel Threading Building Blocks](https://www.intel.com/content/www/us/en/developer/articles/guide/get-started-with-tbb.html). To disable add cmake build flag `-DRTA_ENABLE_THREADS=0`
